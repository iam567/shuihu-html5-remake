// Battle-stage scheduler: native version of ROM 0x12074 around the generated handlers in stage-rules.js.
// The handlers read battle state through original RAM addresses; this module maps those addresses to BattleEngine
// units and to the scheduler's own bytes. Nothing here loads the ROM.
import {StageCpu,stageHandlers} from './stage-rules.js';

export const UNIT_BASE=0xffe780,UNIT_SLOTS=30;
const RAM={turn:0xffe1f5,counter:0xffe1d0,flags:0xffe1fc,phase:0xffe1f7,phaseDone:0xff6102};
// Animation / pending-work bytes the handlers wait on. The native battle only calls tick() when all of them are idle.
const IDLE=new Set([0xff6310,0xff614f,0xff6085,0xff609a,0xff6019,0xff603d]);

// 64-byte unit record as the ROM keeps it at FFE780 + slot*0x40 (inverse of battle.js unitFromRecord).
export function unitBytes(u) {
  const b=new Uint8Array(64);if(u.raw)b.set(u.raw.slice(0,64));
  const word=(n,v)=>{b[n]=(v>>8)&255;b[n+1]=v&255;};
  b[0]=u.spriteType;word(2,u.x<<5);word(4,u.y<<5);b[6]=u.direction;b[7]=u.identity;
  b.set(u.skillIds.slice(0,4),8);b.set(u.status.slice(0,4),12);b[16]=u.level;b[17]=u.experience;word(18,Math.max(0,u.hp));
  b[20]=u.attack[0];b[21]=u.attack[1];b[22]=u.defense[0];b[23]=u.defense[1];b[24]=u.critical;b[25]=u.hit;b[26]=u.resist;b[27]=u.movement;
  word(30,u.maxHp);b[33]=u.classId;b[36]=u.subtype;b.set(u.equipment.slice(0,4),38);b[42]=u.passive;b.set(u.uses.slice(0,4),43);
  return b;
}

export class StageScheduler {
  constructor({stage,battle,state}) {
    if(!stageHandlers[stage])throw Error(`没有第 ${stage} 场战斗的原版触发规则`);
    this.stage=stage;this.battle=battle;
    // turn=FFE1F5 (0xFF until the opening event), counter=FFE1D0, flags=FFE1FC (32 one-shot bits),
    // phase=FFE1F7 (0 player, 1 ally, 2 enemy), phaseDone=FF6102 (current phase finished).
    this.state={turn:0xff,counter:0,flags:0,phase:0,phaseDone:0,...state};
  }
  read8(address) {
    address&=0xffffff;
    if(address>=UNIT_BASE&&address<UNIT_BASE+UNIT_SLOTS*64){
      const slot=(address-UNIT_BASE)>>6,u=this.battle.slotUnit(slot);
      if(!u)return 0;
      this.cache??=new Map();if(!this.cache.has(slot))this.cache.set(slot,unitBytes(u));
      return this.cache.get(slot)[address&63];
    }
    const s=this.state;
    if(address===RAM.turn)return s.turn;if(address===RAM.counter)return s.counter;
    if(address>=RAM.flags&&address<RAM.flags+4)return (s.flags>>>(8*(3-(address-RAM.flags))))&255;
    if(address===RAM.phase)return s.phase;if(address===RAM.phaseDone)return s.phaseDone;
    if(IDLE.has(address))return 0;
    // Stage 5 (loop at 0x1250A) scans 24 slots from slot 12, i.e. 6 "slots" past the table into FFEF00-FFF07F
    // (FFEF80 is the palette buffer). Those bytes never form a battle position, so they read as no unit.
    if(address>=UNIT_BASE+UNIT_SLOTS*64&&address<UNIT_BASE+36*64)return 0;
    throw Error(`战场规则读取了未映射的内存 ${address.toString(16)}`);
  }
  write8(address,value) {
    address&=0xffffff;value&=255;const s=this.state;
    if(address===RAM.turn)s.turn=value;else if(address===RAM.counter)s.counter=value;
    else if(address>=RAM.flags&&address<RAM.flags+4){const shift=8*(3-(address-RAM.flags));s.flags=((s.flags&~(255<<shift))|(value<<shift))>>>0;}
    else if(address!==0xff6019)throw Error(`战场规则写入了未映射的内存 ${address.toString(16)}`);
    // FF6019 bit 2 is the defeated unit's palette fade; clearing it only shortens an effect the native battle does not have.
  }
  // One frame of 0x12074 when no script is running: run this stage's handler, return the event id it starts or null.
  tick() {
    let fired=null;this.cache=null;
    const m={r:(size,a)=>{let v=0;for(let i=0;i<size;i++)v=v*256+this.read8(a+i);return v>>>0;},
      w:(size,a,v)=>{for(let i=size-1;i>=0;i--){this.write8(a+i,v&255);v=Math.floor(v/256);}},
      event:id=>{fired=id;}};
    stageHandlers[this.stage](m,new StageCpu());this.cache=null;
    return fired;
  }
  serialize() {return {stage:this.stage,state:{...this.state}};}
}
