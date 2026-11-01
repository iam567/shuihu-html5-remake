// Native JavaScript tactical battle. Formulas, reach shapes, counters and the AI follow the ROM (addresses at each rule).
import {runAI} from './battle-ai.js';
const clone = value => JSON.parse(JSON.stringify(value));
const distance = (a,b) => Math.abs(a.x-b.x)+Math.abs(a.y-b.y);
const cardinal = [[0,-1],[-1,0],[0,1],[1,0]];   // up, left, down, right: the ROM flood's order (0x6986), which settles AI ties
// Terrain a unit may enter (ROM table 0x6C68 by subtype, applied at 0x69B0): a cell's logic byte must be below the limit.
// Most units stop at 0x4F (plain ground); subtypes 13-14 (漁人 / 水鬼) reach 0x5F (the 0x50 cells: water), subtype 12
// reaches 0x6F. Accessory 119 (passive 0x77) sets 0x6F and 120 (0x78) sets 0x5F in place of the subtype's (0x69C2).
export function terrainLimit(u) {if(!u)return 0x50;if(u.passive===119)return 0x6f;if(u.passive===120)return 0x5f;return u.subtype===12?0x6f:u.subtype===13||u.subtype===14?0x5f:0x4f;}
export class OriginalRNG {
  constructor(seed=1) { this.state=Number(seed)&65535; }
  next() { this.state=(this.state*32719+3)%32749; return Math.floor((this.state&63)*100/64); }
}
export function baseDamage(attacker,target,skill,matrix,mode=skill.effect_type===0?0:1) {
  let attack=attacker.attack[mode===0?0:1];
  if(attacker.status[2]) attack>>=1;
  attack+=skill.power_or_quantity;
  const mult=matrix[attacker.classId]?.[target.classId]??0;
  if(mult) attack=Math.floor(attack*mult/10);
  let defense=target.defense[mode===0?0:1];
  if(target.status[3]) defense>>=1;
  return Math.max(1,attack-defense);
}
export function hitSuccess(attacker,target,skill,rng) {
  const threshold=(attacker.hit+skill.hit_bonus)&255;
  if(target.status[0]) return true;
  if(threshold<target.resist) return false;
  return rng.next()<=threshold-target.resist;
}
export function growthStats(data,classId,level,passive=0) {
  const row=data.growth.find(r=>r.class_index===classId)??data.growth[0];
  const v=row.stats.map(s=>Math.min(s.cap,s.base+Math.floor((Math.max(1,level)-1)*s.numerator/s.denominator)));
  const field={112:1,113:3,114:2,115:4,116:6,117:7,118:0}[passive];
  if(field!==undefined) v[field]=Math.floor(v[field]*11/10);
  return {maxHp:v[0],attack:v.slice(1,3),defense:v.slice(3,5),critical:v[5],hit:v[6],resist:v[7]};
}
export function unitFromRecord(record,index=0,overrides={}) {
  if(Array.isArray(record)||record instanceof Uint8Array||typeof record==='string') record={raw:record};
  // A unit object that already carries computed stats keeps them; its raw bytes are only kept for the RAM view.
  const raw=record.maxHp===undefined?record.raw:null;
  let b=typeof raw==='string'?Uint8Array.from(raw.match(/../g)??[],v=>parseInt(v,16)):raw?Uint8Array.from(raw):null;
  if(b&&b.length!==64) throw new Error('战斗记录必须为 64 字节');
  const word=n=>(b[n]<<8)|b[n+1];
  const r=b?{spriteType:b[0],animation:b[1],x:word(2)>>5,y:word(4)>>5,direction:b[6],identity:b[7],skillIds:[...b.slice(8,12)],status:[...b.slice(12,16)],level:b[16],experience:b[17],hp:word(18),attack:[b[20],b[21]],defense:[b[22],b[23]],critical:b[24],hit:b[25],resist:b[26],movement:b[27],maxHp:word(30),classId:b[33],subtype:b[36],equipment:[...b.slice(38,42)],passive:b[42],uses:[...b.slice(43,47)]}:record;
  const unit={id:record.id??`unit-${index}`,slot:record.slot??index,raw:b?[...b]:record.raw??null,removed:false,team:record.team??((record.slot??index)<12?'player':'enemy'),name:record.name??`人物 ${r.identity??index}`,spriteType:r.spriteType??record.sprite_type??1,identity:r.identity??record.portrait_or_identity??index,x:r.x??0,y:r.y??0,direction:r.direction??1,level:r.level??1,experience:r.experience??0,hp:r.hp??30,maxHp:r.maxHp??r.max_hp??30,classId:r.classId??r.class??0,subtype:r.subtype??1,attack:r.attack??[13,13],defense:r.defense??[10,9],critical:r.critical??2,hit:r.hit??12,resist:r.resist??15,movement:r.movement??5,status:r.status??[0,0,0,0],skillIds:r.skillIds??[],equipment:r.equipment??[1,0,0,0],uses:r.uses??[99,0,0,0],passive:r.passive??0,moved:r.moved??false,moveFrom:r.moveFrom??null,acted:r.acted??false,...overrides};
  return clone(unit);
}
export class BattleEngine {
  // autoResult=false leaves victory/defeat to the original stage scheduler (stage-scheduler.js) instead of team wipe-out.
  constructor({data,width=16,height=12,units=[],passable=()=>true,onChange=()=>{},onVictory=()=>{},onDefeat=()=>{},seed=1,autoResult=true}={}) {
    if(!data) throw new Error('缺少战斗数值表');
    this.data=data;this.width=width;this.height=height;this.passable=passable;this.autoResult=autoResult;
    this.onChange=onChange;this.onVictory=onVictory;this.onDefeat=onDefeat;
    this.units=units.map((u,i)=>unitFromRecord(u,i)).filter(u=>u.spriteType!==0);
    this.rng=new OriginalRNG(seed);this.turn=1;this.activeTeam='player';this.selectedId=null;this.result=null;this.log=[];
    const ids=this.units.map(u=>u.id);if(new Set(ids).size!==ids.length)throw new Error('单位 ID 重复');
  }
  unit(id) { return this.units.find(u=>u.id===id); }
  alive(team) { return this.units.filter(u=>u.hp>0&&!u.removed&&(!team||u.team===team)); }
  // Original slots 0..29 (FFE780 + slot*0x40); a unit at 0 HP stays in its slot until removeFallen(), like the ROM's death fade.
  slotUnit(slot) { return this.units.find(u=>u.slot===slot&&!u.removed); }
  fallen() { return this.units.filter(u=>u.hp<=0&&!u.removed); }
  removeFallen() { const list=this.fallen();for(const u of list)u.removed=true;if(list.length)this._emit(list.map(u=>({type:'removed',unitId:u.id})));return list; }
  addUnit(record) { if(this.slotUnit(record.slot))return this._fail(`槽位 ${record.slot} 已有人物`);const u=unitFromRecord(record,record.slot);if(this.units.some(v=>v.id===u.id))u.id=`${u.id}-${this.units.length}`;this.units.push(u);return this._emit([{type:'spawn',unitId:u.id,slot:u.slot}]); }
  side(u) { return u.team==='enemy'?'enemy':'player'; }
  phaseComplete(team) { return this.alive(team).every(u=>u.acted); }
  select(id) { const u=this.unit(id);if(!u||u.hp<=0)return this._fail('单位不可选择');this.selectedId=id;return this._emit([{type:'select',unitId:id}]); }
  _fail(error) { return {ok:false,error,events:[]}; }
  _emit(events) { this.log.push(...events);this.log=this.log.slice(-300);this.onChange(this,events);return {ok:true,events}; }
  _ready(u) {return u&&u.hp>0&&u.team===this.activeTeam&&!u.acted&&!this.result;}
  _canStand(x,y,u) {return Number.isInteger(x)&&Number.isInteger(y)&&x>=0&&y>=0&&x<this.width&&y<this.height&&this.passable(x,y,u)&&!this.alive().some(v=>v.id!==u.id&&v.x===x&&v.y===y);}
  reachable(id) {
    const u=this.unit(id);if(!this._ready(u)||u.moved||u.status[0])return [];
    return this._flood(u);
  }
  // Cells any unit could reach from where it stands this turn (for looking at enemies/allies; ignores turn order).
  moveRange(id) {const u=this.unit(id);if(!u||u.hp<=0)return [];const queue=[{x:u.x,y:u.y,cost:0}],seen=new Set([`${u.x},${u.y}`]);
    return this._flood(u);}
  // Movement flood (ROM 0x6986): 1 per cell over terrain the unit may enter; the other side's units are walls (0x6F0E /
  // 0x8D48 mark them 0x7F) while its own side, allies included, can be passed through. A move still cannot end on an
  // occupied cell (0x5196), so those are walked over but not offered.
  _flood(u) {const queue=[{x:u.x,y:u.y,cost:0}],seen=new Set([`${u.x},${u.y}`]),others=this.alive().filter(v=>v.id!==u.id),at=(x,y)=>others.find(v=>v.x===x&&v.y===y);
    for(let i=0;i<queue.length;i++){const p=queue[i];if(p.cost>=u.movement)continue;for(const [dx,dy]of cardinal){const x=p.x+dx,y=p.y+dy,key=`${x},${y}`;if(seen.has(key)||!(x>=0&&y>=0&&x<this.width&&y<this.height&&this.passable(x,y,u)))continue;const v=at(x,y);if(v&&this.side(v)!==this.side(u))continue;seen.add(key);queue.push({x,y,cost:p.cost+1,through:!!v});}}
    return queue.filter(p=>!p.through).map(({through,...p})=>p);}
  skill(id) {return this.data.skills.find(s=>s.id===Number(id)&&!s.all_zero);}
  // Carried consumables (128+) follow their own switch (ROM 0x15BAA; targets chosen at 0x156DE: code <= 5 friends,
  // above 5 foes): 0 heal (0xA5FE: 25/50/75/100 by item, otherwise to full), 1-4 clear status 0-3 (混乱, 中毒, 虚弱,
  // 破甲), 6 / 7 inflict 虚弱 / 破甲 for 3 turns, 8 a fixed blow of 50 minus the target's 计防 (0x15F46, at least 1).
  _kind(skill) {
    if(!skill)return 'unsupported';
    if(skill.id>=128){const e=skill.effect_type;return e===0?'heal':e>=1&&e<=4?'cleanse':e===6||e===7?'status':e===8?'damage':'unsupported';}
    if(skill.effect_type===11)return 'refresh';if(skill.effect_type===14)return 'areaheal';
    if(Object.hasOwn(this.data.healingAmounts??{},skill.id)||skill.effect_type===2)return 'heal';
    if(skill.effect_type<=1&&skill.id<112)return 'damage';
    if(skill.effect_type>=3&&skill.effect_type<=6)return 'status';
    if(skill.effect_type>=7&&skill.effect_type<=10||skill.effect_type===13)return 'cleanse';
    return 'unsupported';
  }
  skillOptions(id) {
    const u=this.unit(id);if(!u)return [];
    const seen=new Set();return [...u.equipment,...u.skillIds].filter(v=>v&&!seen.has(v)&&seen.add(v)).map(skillId=>{
      const s=this.skill(skillId),slot=u.equipment.indexOf(skillId),uses=slot>=0?u.uses[slot]:null,kind=this._kind(s);
      return {skillId,label:`${kind==='heal'||kind==='areaheal'?'恢复':kind==='damage'?'攻击':kind==='status'?'状态':kind==='cleanse'?'解除':kind==='refresh'?'再动':'待还原'} · ${skillId}`,kind,uses,range:Math.max(1,s?.range_candidate??1),enabled:kind!=='unsupported'&&(uses===null||uses>0)};
    });
  }
  primarySkill(id) {return this.skillOptions(id).find(s=>s.kind==='damage'&&s.enabled)?.skillId??null;}
  // Attack reach is the unit's own shape, chosen by its subtype (ROM 0xAEB2, data rangePatterns: offsets attacker minus
  // target): spears reach two cells in a line, archers only the ring beyond arm's length, and so on.
  inReach(u,t){const pat=this.data.rangePatterns?.[(u.subtype||1)-1];if(!pat)return distance(u,t)<=1&&distance(u,t)>0;return pat.some(([dx,dy])=>t.x+dx===u.x&&t.y+dy===u.y);}
  reachCells(id){const u=this.unit(id),pat=this.data.rangePatterns?.[(u?.subtype||1)-1]??[[0,1],[0,-1],[1,0],[-1,0]];return pat.map(([dx,dy])=>({x:u.x-dx,y:u.y-dy})).filter(c=>c.x>=0&&c.y>=0&&c.x<this.width&&c.y<this.height);}
  // Heals, cures and 遁甲 reach by the support shapes (ROM 0x1509E, offsets from the caster, own cell included), curses by
  // the curse shapes (0xD148); carried items reach the user and the 4 cells around it, hostile ones only those 4 (0x1581C).
  supportPattern(u){const p=this.data.supportPatterns;if(!p)return null;return [0x12,0x17,0x1a].includes(u.subtype)?p.small:[0x13,0x18,0x1b].includes(u.subtype)?p.medium:p.large;}
  cursePattern(u){const p=this.data.cursePatterns;if(!p)return null;return u.subtype===0x1a?p.small:u.subtype===0x1b?p.medium:p.large;}
  covers(pattern,from,t){return pattern.some(([dx,dy])=>from.x+dx===t.x&&from.y+dy===t.y);}
  targets(id,skillId=this.primarySkill(id)) {
    const u=this.unit(id),s=this.skill(skillId),kind=this._kind(s);if(!this._ready(u)||!s||kind==='unsupported'||u.status[0])return [];
    if(s.id>=128){const friendly=s.effect_type<=5,d=t=>Math.abs(t.x-u.x)+Math.abs(t.y-u.y);return this.alive().filter(t=>(friendly?this.side(t)===this.side(u)&&d(t)<=1:this.side(t)!==this.side(u)&&d(t)===1));}
    if(kind==='areaheal')return [u];
    const support=['heal','cleanse','refresh'].includes(kind),pat=support?this.supportPattern(u):kind==='status'?this.cursePattern(u):null;
    if(support)return this.alive().filter(t=>this.side(t)===this.side(u)&&(pat?this.covers(pat,u,t):this.inReach(u,t)||t.id===u.id)&&(kind!=='heal'||t.hp<t.maxHp)&&(kind!=='refresh'||t.acted&&t.team==='player'&&t.id!==u.id));
    return this.alive().filter(t=>this.side(t)!==this.side(u)&&(pat?this.covers(pat,u,t):this.inReach(u,t)));
  }
  actions(id) {const u=this.unit(id),ready=this._ready(u)&&!u.status[0];if(ready&&u.repositionOnly)return [{id:'move',label:'移动',enabled:true},{id:'wait',label:'待机',enabled:true}];return [{id:'move',label:'移动',enabled:!!ready&&!u.moved},{id:'attack',label:'攻击',skillId:this.primarySkill(id),enabled:!!ready&&this.primarySkill(id)!==null},...this.skillOptions(id).map(s=>({...s,id:'skill',enabled:!!ready&&s.enabled})),{id:'wait',label:'待机',enabled:this._ready(u)}];}
  move(id,x,y) {const u=this.unit(id);if(!this.reachable(id).some(p=>p.x===x&&p.y===y))return this._fail('此格无法到达');const from={x:u.x,y:u.y};u.moveFrom=u.moveFrom??from;u.x=x;u.y=y;u.moved=true;if(u.repositionOnly){u.repositionOnly=false;u.acted=true;u.moveFrom=null;}return this._emit([{type:'move',unitId:id,from,to:{x,y}}]);}
  // Undo a move that has not been followed by an action (the unit has not acted yet): back to where it started.
  undoMove(id) {const u=this.unit(id);if(!u||!u.moved||u.acted||!u.moveFrom)return this._fail('无法撤销移动');const from={x:u.x,y:u.y};u.x=u.moveFrom.x;u.y=u.moveFrom.y;u.moved=false;u.moveFrom=null;return this._emit([{type:'move',unitId:id,from,to:{x:u.x,y:u.y}}]);}
  // 待机 without having moved this turn rests: max HP / 8 back, up to max (ROM 0x4C3C, checked through the menu's 移动 bit).
  wait(id) {const u=this.unit(id);if(!this._ready(u))return this._fail('单位已行动');const events=[{type:'wait',unitId:id}];
    if(u.repositionOnly){u.repositionOnly=false;u.acted=true;u.moved=true;return this._emit(events);}
    if(!u.moved&&u.hp>0&&u.hp<u.maxHp){const before=u.hp;u.hp=Math.min(u.maxHp,u.hp+Math.floor(u.maxHp/8));events.push({type:'heal',unitId:id,targetId:id,amount:u.hp-before,targetHp:u.hp,rest:true});}
    u.acted=true;u.moved=true;return this._emit(events);}
  attack(id,targetId) {const s=this.primarySkill(id);return s===null?this._fail('没有可用武器'):this.useSkill(id,s,targetId);}
  _experience(u,t,underflow=false,status=false) {
    const index=(status?t.level:((t.level+5)&255))-u.level;
    const table=underflow?this.data.experienceUnderflow:this.data.experienceHit;
    return this._gain(u,index<0?1:table[Math.min(index,status?8:13)]);
  }
  _gain(u,gained) {
    u.experience=(u.experience+gained)&255;let leveled=false;
    if(u.experience>99){u.experience-=100;u.level=(u.level+1)&255;Object.assign(u,growthStats(this.data,u.classId,u.level,u.passive));u.hp=Math.min(u.hp,u.maxHp);leveled=true;const chain=this.data.progression.find(c=>c.class===u.classId);const step=chain?.pairs.find(p=>p.subtype===u.subtype&&p.transition_at_level===u.level);if(step?.next_subtype){u.subtype=step.next_subtype;u.movement=this.data.movementBySubtype?.[u.subtype]??u.movement;}}   // 0x14D72 rewrites +0x1B on level-up
    return {type:'experience',unitId:u.id,gained,level:u.level,leveled};
  }
  // A unit carrying 散體符 (passive 123) bursts when it falls (ROM 0x4570 -> script 0x170D8, op 0A at 0x164C8/0x163EE):
  // every other unit within 3 cells (Manhattan), friend or foe, loses max(1, its attack - their defence); units brought
  // to 0 fall too, but do not burst again (the ROM's death loop does not re-check the item).
  _scatter(u,events){if(u.passive!==123)return;events.push({type:'burst',unitId:u.id,x:u.x,y:u.y});
    for(const v of this.units){if(v===u||v.removed||v.hp<=0||Math.abs(v.x-u.x)+Math.abs(v.y-u.y)>3)continue;const damage=Math.max(1,(u.attack[0]??0)-(v.defense[0]??0));v.hp=Math.max(0,v.hp-damage);
      events.push({type:'burst-hit',unitId:u.id,targetId:v.id,damage,targetHp:v.hp});if(v.hp===0)events.push({type:'defeated',unitId:v.id});}}
  // Counterattack (ROM 0x49E4 -> 0x4AB4 -> mode 9 at 0xB4A8): after a weapon attack (and any second strike) a target that
  // survives, is not confused and whose own reach shape covers the attacker's cell strikes back once. It lands on the same
  // roll as the attack itself (0xA318 reuses the attacker's 命中 against the target's 闪避), deals max(1, its attack − the
  // attacker's defence) by its weapon's kind, halved by 虚弱 / 破甲 as usual (0xB58C: no weapon power, no class multiplier),
  // with the attacker's 会心 chance (0x5F9C reads the acting unit), gives no experience and is not answered again (mode 0xA).
  _counter(u,t,s,events){if(t.status[0]||!this.inReach(t,u))return;const w=this.skill(t.equipment[0]);if(!w)return;
    const hit=hitSuccess(u,t,this.skill(u.equipment[0])??s,this.rng);let damage=0,critical=false,gain=null;   // 0xA318 / 0x8940: the attacker's +0x26 hit bonus, whatever it struck with
    if(hit){const mode=w.effect_type===0?0:1;let a=t.attack[mode];if(t.status[2])a>>=1;let d=u.defense[mode];if(u.status[3])d>>=1;damage=Math.max(1,a-d);critical=this.rng.next()<=u.critical;if(critical)damage+=Math.floor(damage/2);const underflow=damage>u.hp;u.hp=Math.max(0,u.hp-damage);
      if(t.team==='player')gain=this._experience(t,u,underflow);}   // one of ours countering in the enemy phase learns from it (0x8882); allies do not
    events.push({type:'attack',unitId:t.id,targetId:u.id,skillId:w.id,hit,critical,damage,targetHp:u.hp,counter:true});if(gain)events.push(gain);
    if(u.hp===0){events.push({type:'defeated',unitId:u.id});this._scatter(u,events);}}
  // ai: the enemy / ally routines strike with their +0x26 weapon, spend no uses and earn no experience (0xA1D2 / 0xE966).
  useSkill(id,skillId,targetId,{ai=false}={}) {
    const u=this.unit(id),t=this.unit(targetId),s=this.skill(skillId),option=this.skillOptions(id).find(v=>v.skillId===Number(skillId));
    if(!this._ready(u)||u.status[0])return this._fail('单位现在不能行动');
    if(!s||!(option?.enabled||ai&&option&&option.kind!=='unsupported'))return this._fail('技能未持有、次数不足或效果尚未还原');
    if(!t||!this.targets(id,skillId).some(v=>v.id===t.id))return this._fail('目标不在范围内');
    const kind=this._kind(s),events=[],learns=u.team==='player'&&!ai,xp=(...a)=>learns?[this._experience(...a)]:[];const slot=u.equipment.indexOf(Number(skillId));if(slot>=0&&!ai)u.uses[slot]=Math.max(0,u.uses[slot]-1);
    else if(Number(skillId)>=128){const k=u.skillIds.indexOf(Number(skillId));if(k>=0)u.skillIds[k]=0;}   // an item from the unit's own 4 item slots is used up
    if(kind==='damage'){
      // Byte 2 of the weapon (range_candidate) minus one is the number of extra hits (ROM 0x49E4 / 0xEAFA).
      if(s.id>=128){const damage=Math.max(1,50-(t.defense[1]??0));t.hp=Math.max(0,t.hp-damage);events.push({type:'attack',unitId:id,targetId,skillId:s.id,hit:true,critical:false,damage,targetHp:t.hp},...xp(u,t,false));}
      else{
      const hits=Math.max(1,s.range_candidate||1),attacks=[];
      for(let n=0;n<hits&&t.hp>0;n++){const hit=hitSuccess(u,t,s,this.rng);let damage=0,critical=false;
        if(hit){damage=baseDamage(u,t,s,this.data.matrix);critical=this.rng.next()<=u.critical;if(critical)damage+=Math.floor(damage/2);const underflow=damage>t.hp;t.hp=Math.max(0,t.hp-damage);events.push(...xp(u,t,underflow));
          if(s.id===17&&t.hp>0&&!t.status[1]){t.status[1]=1;events.push({type:'status',unitId:id,targetId,skillId:s.id,field:1,duration:0,hit:true});}}   // 毒爪 poisons what it strikes (0x5DC8 / 0xA286)
        attacks.push({type:'attack',unitId:id,targetId,skillId:s.id,hit,critical,damage,targetHp:t.hp,strike:n+1});}
      events.unshift(...attacks);}
      if(t.hp===0){events.push({type:'defeated',unitId:targetId});this._scatter(t,events);}
      else if(u.hp>0)this._counter(u,t,s,events);   // weapons, stratagems and item blows alike (0x4976 follows every strike)
    }else if(kind==='heal'){
      const before=t.hp,amount=this.data.healingAmounts?.[s.id]??t.maxHp;t.hp=Math.min(t.maxHp,t.hp+amount);
      events.push({type:'heal',unitId:id,targetId,skillId:s.id,amount:t.hp-before,targetHp:t.hp},this._experience(u,t,false,true));
    }else if(kind==='areaheal'){
      // 102 (effect 0xE, 0x154F0 / 0x15462): every one of ours inside the support shape and below full gains 100; the caster
      // gets a flat 1 experience.
      const pat=this.supportPattern(u);for(const v of this.alive()){if(this.side(v)!==this.side(u)||v.hp>=v.maxHp||!(pat?this.covers(pat,u,v):v.id===u.id))continue;const before=v.hp;v.hp=Math.min(v.maxHp,v.hp+100);events.push({type:'heal',unitId:id,targetId:v.id,skillId:s.id,amount:v.hp-before,targetHp:v.hp});}
      events.push(this._gain(u,1));
    }else if(kind==='refresh'){
      // 遁甲天書 (effect 0xB, 0x5B32): one of ours who has already acted may act again this turn.
      Object.assign(t,{acted:false,moved:false,moveFrom:null});events.push({type:'refresh',unitId:id,targetId,skillId:s.id},this._experience(u,t,false,true));
    }else if(kind==='status'){
      const hit=s.id>=128?true:hitSuccess(u,t,s,this.rng),field=s.id>=128?s.effect_type-4:s.effect_type-3;if(hit)t.status[field]=3;
      events.push({type:'status',unitId:id,targetId,skillId:s.id,field,duration:3,hit});if(hit)events.push(this._experience(u,t,false,true));
    }else if(kind==='cleanse'){
      if(s.id>=128)t.status[s.effect_type-1]=0;else if(s.effect_type===13)t.status=[0,0,0,0];else t.status[s.effect_type-7]=0;
      events.push({type:'cleanse',unitId:id,targetId,skillId:s.id},this._experience(u,t,false,true));
    }
    // 一苇渡江鞋 (passive 0x7A, item 122; 0x4A12 -> mode 0x14 at 0x16C68): after a blow, one of ours who carries it may
    // still step to another cell (a full move from where it stands, nothing else) before its turn ends.
    if(kind==='damage'&&u.passive===122&&u.team==='player'&&u.hp>0){u.acted=false;u.moved=false;u.moveFrom=null;u.repositionOnly=true;events.push({type:'reposition',unitId:id});}
    else{u.acted=true;u.moved=true;}this._checkResult(events);return this._emit(events);
  }
  _checkResult(events=[]) {
    if(this.result||!this.autoResult)return;
    if(!this.alive('player').length){this.result='defeat';events.push({type:'defeat'});this.onDefeat(this);}
    else if(!this.alive('enemy').length){this.result='victory';events.push({type:'victory'});this.onVictory(this);}
  }
  // Phase start (ROM 0xC74C / 0xDB02 / 0xC98C): 混乱, 虚弱 and 破甲 count down by one; 中毒 does not wear off (only cures
  // end it) and takes floor(maxHP/6) from each poisoned unit of the side about to move, never below 1 (0xC574).
  _beginTeam(team) {this.activeTeam=team;const events=[];for(const u of this.alive(team)){u.moved=false;u.moveFrom=null;u.acted=false;u.repositionOnly=false;u.status=u.status.map((s,i)=>i===1?s:Math.max(0,s-1));
      if(u.status[1]&&u.hp>1){const damage=Math.min(u.hp-1,Math.floor(u.maxHp/6));if(damage>0){u.hp-=damage;events.push({type:'poison',unitId:u.id,damage,targetHp:u.hp});}}}
    return events;}
  beginPhase(team) {const ticks=this._beginTeam(team);this.selectedId=null;return this._emit([{type:'turn',team,turn:this.turn},...ticks]);}
  // 结束回合 (system menu, 0x258CC): each of ours who has not acted yet rests for floor(maxHP/8) before the phase ends.
  restIdle(team) {const events=[];for(const u of this.alive(team)){if(u.acted||u.hp>=u.maxHp)continue;const before=u.hp;u.hp=Math.min(u.maxHp,u.hp+Math.floor(u.maxHp/8));events.push({type:'heal',unitId:u.id,targetId:u.id,amount:u.hp-before,targetHp:u.hp,rest:true});}
    return events.length?this._emit(events):{ok:true,events};}
  aiOrder(team) {return this.alive(team).sort((a,b)=>a.slot-b.slot).map(u=>u.id);}
  // AI after the cartridge's modes, kept in battle-ai.js.
  aiAct(id) {runAI(this,id,{baseDamage,hitSuccess});}
  _enemyAI() {for(const id of this.aiOrder('enemy')){if(this.result)break;this.aiAct(id);}}
  endTurn() {
    if(this.result)return this._fail('战斗已结束');if(this.activeTeam!=='player')return this._fail('请等待敌方行动');
    const start=this.log.length;
    if(this.alive('ally').length){this.beginPhase('ally');for(const id of this.aiOrder('ally')){if(this.result)break;this.aiAct(id);}}
    this.beginPhase('enemy');this._enemyAI();this._checkResult();
    if(!this.result){this.turn++;this.beginPhase('player');}
    return {ok:true,events:this.log.slice(start)};
  }
  serialize() {return clone({version:1,width:this.width,height:this.height,units:this.units,seed:this.rng.state,turn:this.turn,activeTeam:this.activeTeam,selectedId:this.selectedId,result:this.result,log:this.log});}
  static restore(saved,options) {if(saved.version!==1)throw new Error('战斗存档版本不支持');const b=new BattleEngine({...options,...saved});b.turn=saved.turn;b.activeTeam=saved.activeTeam;b.selectedId=saved.selectedId;b.result=saved.result;b.log=clone(saved.log??[]);return b;}
}
