// One battle from deployment to the battle-end script, driven by the original stage scheduler.
// Order per frame in the ROM: stage handler (0x12074) may start an event; with no event running, phase advance
// (0x7D40) consumes FF6102. Here the same checks run after every action instead of every frame.
import {BattleEngine,unitFromRecord,growthStats} from './battle.js';
import {StageScheduler,unitBytes} from './stage-scheduler.js';
import {deployBattle,deploymentOptions,persistParty,initialRoster,freeCell} from './battle-setup.js';

export class BattleSession {
  // ui: chooseDeployment(options)->Promise<ids>, runEvent(group,id)->Promise, changed(session), ended(session)
  constructor({vm,battleData,tables,battleMap,stage,ui,passable}) {
    const stageData=tables.stages[stage];if(!stageData)throw Error(`没有第 ${stage} 场战斗的部署表`);
    Object.assign(this,{vm,battleData,tables,battleMap,stage,stageData,ui,passable});
    this.group=battleMap.mapId>>8;this.ended=false;this.busy=false;this.generation=0;
    vm.state.roster??=initialRoster(tables);
    if(vm.state.firstPartyIdentity===0x1515){vm.state.roster[0][0]=0x15;vm.state.roster[0][1]=0x15;}   // opcode 0x45 (0x11ED6): FFE630 = 0x1515
  }
  get engine() {return this._engine;}
  async start() {await this._deploy();this._build();await this.settle();}
  // A battle saved mid-way (app.js battleSnapshot, taken only on the player's turn with nothing running) picks up where it
  // was: same units, turn, random seed and stage-scheduler bytes; the deployment is kept for a later retry (opcode 2).
  resume(snap) {Object.assign(this,{selected:snap.selected,firstSlot:snap.firstSlot,records:snap.records,generation:snap.generation,restart:false});
    this._engine=BattleEngine.restore(snap.engine,{data:this.battleData,passable:(x,y,u)=>this.passable(x,y,u),autoResult:false,onChange:(e,events)=>this.ui.changed(this,events)});this._engine.selectedId=null;
    this.scheduler=new StageScheduler({stage:this.stage,battle:this._engine,state:snap.scheduler});this.ui.changed(this);}
  // 鳴金收兵 (battle menu): the battle counts as lost and starts again from deployment, keeping the experience and levels
  // earned so far (checked on the cartridge), as the defeat retry (opcode 2) does.
  async retreat() {if(this.busy||this.ended||this.scheduler.state.phase!==0)return false;this.busy=true;
    try{persistParty(this.vm.state.roster,this.deployed(),{skills:false});this.keepSeed();await this.ui.lost?.();await this._deploy();this._build();}finally{this.busy=false;}
    await this.settle();return true;}
  // The cartridge seeds its random numbers once at power-on (0x73A) and never again: each battle and each retry carries on
  // from where the last one left the sequence.
  keepSeed() {if(this._engine)this.vm.state.rngState=this._engine.rng.state;}
  snapshot() {return {stage:this.stage,battleMap:this.battleMap,selected:this.selected,firstSlot:this.firstSlot,records:this.records,generation:this.generation,engine:this._engine.serialize(),scheduler:{...this.scheduler.state}};}

  async _deploy() {
    const options=deploymentOptions(this.stageData,this.vm.state.party);
    let chosen=options.mandatory;
    if(options.optional.length&&options.limit>options.mandatory.length)chosen=await this.ui.chooseDeployment(options);
    this.selected=this.vm.state.party.filter(id=>chosen.includes(id)).slice(0,options.limit);
    this.firstSlot=this.stageData.firstSlot;
    this.records=deployBattle({stageData:this.stageData,tables:this.tables,roster:this.vm.state.roster,selected:this.selected,width:this.battleMap.width,height:this.battleMap.height,passable:this.passable});
  }
  _unit(record) {
    const u=unitFromRecord({id:`slot-${record.slot}-${this.generation}-${record.serial??0}`,slot:record.slot,raw:record.raw,team:record.team},record.slot);
    if(record.recalculate){Object.assign(u,growthStats(this.battleData,u.classId,u.level,u.passive));u.hp=u.maxHp;}
    u.name=u.team==='player'?`同伴 ${u.identity}`:u.team==='ally'?`友军 ${u.identity}`:`敌方 ${u.identity}`;
    return u;
  }
  _build() {
    this.generation++;this.restart=false;
    const units=this.records.map(r=>this._unit(r)).filter(u=>u.spriteType!==0);
    this._engine=new BattleEngine({data:this.battleData,seed:this.vm.state.rngState??1,width:this.battleMap.width,height:this.battleMap.height,units,passable:(x,y,u)=>this.passable(x,y,u),autoResult:false,onChange:(e,events)=>this.ui.changed(this,events)});
    this.scheduler=new StageScheduler({stage:this.stage,battle:this._engine});this._engine.turn=1;
  }
  _team(slot) {return slot<this.firstSlot?'player':slot<12?'ally':'enemy';}
  deployed() {return this._engine.units.filter(u=>u.slot<this.selected.length);}

  // Run handler events and remove fallen units until nothing changes (no phase advance).
  async _drain(generation) {
    for(let guard=0;guard<100;guard++){
      if(this.ended||generation!==this.generation)return false;
      const id=this.scheduler.tick();
      if(id!=null){await this._event(id);if(this.restart){await this._deploy();this._build();}continue;}
      if(this._engine.fallen().length){this._engine.removeFallen();continue;}
      return true;
    }
    throw Error('战场触发规则连续触发超过 100 次，已停止');
  }
  async settle() {
    if(this.busy)return;this.busy=true;
    try{
      for(let guard=0;guard<50;guard++){
        const generation=this.generation;
        if(!await this._drain(generation)){if(this.ended)break;continue;}
        const s=this.scheduler.state;
        if(s.phaseDone){await this._advance(generation);continue;}
        // 0x12074 tail: player phase ends by itself once no deployed player unit can act.
        if(s.phase===0&&s.turn!==0xff&&this._engine.phaseComplete('player')){s.phaseDone=1;continue;}
        return;
      }
      if(!this.ended)throw Error('战斗阶段推进未收敛');
    }finally{this.busy=false;this.ui.changed(this);}
    if(this.ended&&!this.notifiedEnd){this.notifiedEnd=true;await this.ui.ended(this);}
  }
  // 0x7D40: player -> ally (only when ally slots exist) -> enemy -> next turn.
  async _advance(generation) {
    // Let the last action's animations (and level-ups) finish before the next side starts moving the camera.
    await this.ui.pace?.();
    const s=this.scheduler.state,e=this._engine;s.phaseDone=0;s.phase++;
    if(s.phase>=3){s.phase=0;s.turn=(s.turn+1)&255;e.turn=s.turn;e.beginPhase('player');return;}
    if(s.phase===1&&this.firstSlot>=12)s.phase=2;
    const team=s.phase===1?'ally':'enemy';e.beginPhase(team);this.ui.changed(this);await this.ui.pause?.(900);   // the turn banner reads first
    for(const id of e.aiOrder(team)){
      e.aiAct(id);this.ui.changed(this);await this.ui.pace?.();
      if(!await this._drain(generation))return;
    }
    s.phaseDone=1;
  }
  async act(action) {
    if(this.busy||this.ended)return {ok:false,error:'请等待战场事件结束'};
    const result=action(this._engine);if(result?.ok)await this.settle();return result;
  }
  async endPlayerPhase() {
    if(this.busy||this.ended||this.scheduler.state.phase!==0)return;
    this._engine.restIdle('player');for(const u of this._engine.alive('player'))u.acted=true;
    await this.settle();
  }

  // A spawned unit enters the field (0x101EE, opcode 07 writes its byte 0): mid-script, as soon as the script shows it,
  // and again after the event for any not yet placed.
  spawnNow(slot) {const vm=this.vm,entry=vm.state.battleUnits?.[slot];
    if(!this._engine||!entry?.active||this._engine.slotUnit(entry.slot))return;if(vm.state.battleAllyStart!=null)this.firstSlot=vm.state.battleAllyStart;
      const raw=[...entry.raw];raw[0]=entry.type;
      const occupied=new Set(this._engine.units.filter(u=>!u.removed).map(u=>`${u.x},${u.y}`));
      const cell=freeCell({tables:this.tables,origin:{x:((raw[2]<<8)|raw[3])>>5,y:((raw[4]<<8)|raw[5])>>5},occupied,width:this.battleMap.width,height:this.battleMap.height,passable:this.passable});
      if(cell){raw[2]=(cell.x<<5)>>8;raw[3]=(cell.x<<5)&255;raw[4]=(cell.y<<5)>>8;raw[5]=(cell.y<<5)&255;}
      const result=this._engine.addUnit(this._unit({slot:entry.slot,raw,team:this._team(entry.slot),serial:this._engine.units.length}));
      if(!result.ok)throw Error(result.error);
  }
  async _event(id) {
    const vm=this.vm;
    vm.state.battleUnits=[];
    for(const u of this._engine.units)if(!u.removed)vm.state.battleUnits[u.slot]={slot:u.slot,raw:[...unitBytes(u)],type:u.spriteType,active:true};
    vm.state.battleAllyStart=null;
    this.activeEvent=id;
    try{await this.ui.runEvent(this.group,id);}finally{this.activeEvent=null;}
    if(this.ended||this.restart)return;
    if(vm.state.battleAllyStart!=null)this.firstSlot=vm.state.battleAllyStart;
    // Script spawns (0x1011E enemy / 0x11E2A ally) become visible when 0x101EE writes byte 0; a taken cell moves to
    // the first free one in the 0x14184 search order.
    for(const entry of vm.state.battleUnits??[])this.spawnNow(entry?.slot);
  }
  // Story VM hooks while this battle is active.
  onReset(context) {
    if(context.retry){persistParty(this.vm.state.roster,this.deployed(),{skills:false});this.keepSeed();this.restart=true;return;}
    // Opcode 3 (0x1009E): enemy phase finished, so the next phase advance starts a new player turn.
    const s=this.scheduler.state;s.phase=2;s.phaseDone=1;
  }
  onEnd() {
    if(this.ended)return;
    persistParty(this.vm.state.roster,this.deployed(),{skills:true});this.keepSeed();
    this.ended=true;this.generation++;
  }
}
