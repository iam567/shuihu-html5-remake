/** Event-level reimplementation. No emulator, ROM loading, or native CPU execution. */
export class StoryVM {
  constructor({data,hooks={}}){this.data=data;this.hooks=hooks;this.running=false;this.state={flags:{},pickupFlags:{},counters:{},variables:{0:1},inventory:{},party:[1],gold:150,mapId:0x106,spawnId:0x100,entities:[],battleUnits:[],region:0,destination:0,selector:0,animationSpeed:1,spriteMask:0x243,npcMasks:structuredClone(data.npcMasks??{}),stage:0};this.trace=[];}
  async call(name,...args){return await this.hooks[name]?.(...args);}
  save(){if(this.running)throw Error('剧情进行中，请等待剧情结束后保存');return structuredClone(this.state);}
  load(state){if(this.running)throw Error('Cannot load during an event');this.state=structuredClone(state);}
  setEntities(entities){this.state.entities=structuredClone(entities);}
  entity(id){let e=this.state.entities.find(e=>e.slot===id);if(!e){e={slot:id,active:false,x:0,y:0};this.state.entities.push(e);}return e;}
  byte(){if(this.pc>=this.data.bytes.length||this.pc<0)throw Error('Script boundary exceeded');return this.data.bytes[this.pc++];}
  word(){return this.byte()*256+this.byte();}
  async move(id,update){await this.call('moveEntity',id,update);Object.assign(this.entity(id),update);}
  scan(label,back=false){let limit=20000;if(back)this.pc-=6;while(limit--){if(back)this.pc-=2;const p=this.pc,v=this.data.bytes[p]*256+this.data.bytes[p+1];if(!back)this.pc+=2;if(v===label){if(back)this.pc+=2;return;}if(p<0||p>=this.data.bytes.length)break;}throw Error(`Missing script label ${label.toString(16)}`);}
  collisionPatches(mapId=this.state.mapId){const f=this.state.flags[mapId>>8]??0,p=[];const add=(indices,value)=>indices.forEach(index=>p.push({index,value}));
    if(mapId===0x106)add([84,85],f&1?0:0x42);if(mapId===0x102)add([54],f&2?0:0x43);
    if(mapId===0x202){if(f&1)add([0x3b,0x45],9);if(f&2)add([0x5e,0x5f],0x71);}if(mapId===0x203&&(f&2))add([0x1a],0x72);
    if(mapId===0x306&&(f&1))add([0x5e,0x5f],11);if(mapId===0x303&&(f&2))add([0x32],12);
    if(mapId===0x400){add([0x166,0x167],f&1?16:0);if(f&2)add([0xcd],0x6a);}
    if(mapId===0x500){if(f&1)add([0x1a3,0x1a4],9);if(f&2)add([0x1a3,0x1a4],10);}
    if(mapId===0x600){if(f&1)add([0x11b],0x68);if(f&2)add([0xa7,0xbf,0xd7],12);}if((mapId>>8)===6&&(f&4))add([0xa7,0xbf,0xd7],13);
    if(mapId===0x800&&(f&1))add([0x117],0x6a);if(mapId===0x900&&(f&1))add([0x47],0x67);if(mapId===0xa00&&(f&1))add([0x52],0x72);if(mapId===0xc00&&(f&1))add([0xc7,0xc8],5);for(const item of this.data.hiddenItems??[]){if(parseInt(item.mapId,16)===mapId&&((this.state.pickupFlags?.[item.group]??0)&(1<<item.pickupFlag.bit)))add([item.cellIndex],0x50);}return p;}
  hiddenPickup(group,id){return (this.data.hiddenItems??[]).find(item=>item.group===group&&item.eventId===id&&parseInt(item.mapId,16)===this.state.mapId);}
  async claimHidden(){const item=this.current?.hidden;if(!item)return;this.state.pickupFlags??={};this.state.pickupFlags[item.group]=((this.state.pickupFlags[item.group]??0)|(1<<item.pickupFlag.bit))>>>0;await this.call('collision',[{index:item.cellIndex,value:0x50}]);}
  transact({kind,item,count=1}){count=Math.floor(count);if(count<1||count>99)return false;const s=this.state,price=this.data.prices[item];if(price==null)return false;if(kind==='buy'){if(s.gold<price*count)return false;s.gold-=price*count;s.inventory[item]=(s.inventory[item]??0)+count;return true;}if(kind==='sell'){if((s.inventory[item]??0)<count)return false;s.inventory[item]-=count;s.gold+=Math.floor(price/2)*count;return true;}return false;}
  async start(group,id){if(this.running)throw Error('Story already running');group=Number(group);id=Number(id);const hidden=this.hiddenPickup(group,id);if(hidden&&((this.state.pickupFlags?.[group]??0)&(1<<hidden.pickupFlag.bit))){await this.call('notify','这里的物品已经取走了');return;}const pc=this.data.banks[group]?.entries[id];if(pc==null)throw Error(`Unavailable event ${group}:${id}`);this.pc=pc;this.running=true;this.current={group,id,hidden};let steps=0;try{while(steps++<20000){const address=this.pc+this.data.base,op=this.word();if(op===0xffff)break;if(op>0xfff)continue;if(op>=80)throw Error(`Unknown opcode ${op.toString(16)} at ${address.toString(16)}`);this.trace.push({address,op});if(this.trace.length>256)this.trace.shift();await this.execute(op);}if(steps>=20000)throw Error('Event exceeded instruction limit');this.running=false;await this.call('complete',this.current);}catch(error){error.event=this.current;error.pc=this.pc+this.data.base;await this.call('error',error);throw error;}finally{this.running=false;}}
  async execute(op){const s=this.state,w=()=>this.word(),b=()=>this.byte();let a,c,n,v,ids;
    switch(op){
      case 0:case 0x1d:case 0x36:await this.call('dialogue',w(),{fullscreen:op===0x36});break;
      case 1:case 0x42:a=b();c=b();await this.call('camera',{unitIdentity:a,speed:c});break;
      case 2:await this.call('battleReset',{retry:true});break;
      case 3:for(const unit of s.battleUnits){if(unit?.raw){unit.raw[1]=unit.slot<12?16:17;unit.raw[6]=1;}}await this.call('battleReset',{phase:2,units:s.battleUnits});break;
      case 4:await this.call('battle',{mapId:s.mapId,stage:s.stage,units:structuredClone(s.battleUnits),party:s.party});break;
      case 5:case 0x43:a=w();if(op===0x43)s.battleAllyStart=a;v=Array.from({length:64},b);while(s.battleUnits[a]?.active)a++;s.lastSpawn=a;s.battleUnits[a]={slot:a,raw:v,type:v[0],active:false,faction:op===5?2:1};break;
      case 6:await this.call('camera',{unit:s.lastSpawn});break;
      case 7:a=w();Object.assign(s.battleUnits[s.lastSpawn]??{}, {type:a,active:true});await this.call('spawnUnit',s.lastSpawn);break;   // 0x101EE: the unit appears now, mid-script
      case 8:await this.call('camera',{unit:s.selectedUnit});break;
      case 9:case 10:case 11:case 0xf:await this.call('battleEffect',{opcode:op,unit:s.selectedUnit});break;
      case 0xc:a=s.battleUnits.find(x=>x.raw?.[47]);s.selector=a?1:0;if(a){s.selectedUnit=a.slot;a.raw[47]=0;}break;
      case 0xd:this.pc+=s.selector*2;a=w();this.scan(a);break;
      case 0xe:a=w();c=w();this.scan(a,c!==0);break;
      case 0x10:case 0x11:await this.call('effect',{kind:op===0x10?'fadeOut':'fadeIn'});break;
      case 0x12:s.mapId=w();s.spawnId=w();break;
      case 0x13:{const key=s.mapId.toString(16).padStart(4,'0');const actors=structuredClone(this.data.npcs[key]??[]);const mask=s.npcMasks[s.mapId]??0xffff;for(let i=0;i<actors.length;i++)actors[i].active=!!(mask&(1<<i));s.entities=[...s.entities.filter(x=>x.slot<8),...actors];await this.call('changeMap',s.mapId,s.spawnId,{entities:s.entities,patches:this.collisionPatches()});await this.call('setEntities',s.entities);break;}
      case 0x14:case 0x17:case 0x34:case 0x37:case 0x39:case 0x41:case 0x44:case 0x46:case 0x47:case 0x48:case 0x49:case 0x4a:await this.call('effect',{opcode:op});break;
      case 0x15:await this.call('wait',w());break;
      case 0x16:a=w();if(a>255){v=this.data.moneyRewards[a&255];if(v==null)throw Error('Unknown gold reward');s.gold+=v;await this.claimHidden();await this.call('reward',{gold:v});}else{s.inventory[a]=(s.inventory[a]??0)+1;await this.claimHidden();await this.call('reward',{item:a,count:1});}break;
      case 0x18:a=w();await this.call('shop',{shopId:a,canCancel:true,items:(this.data.shops[a]??[]).map(id=>({id,price:this.data.prices[id]})),inventory:s.inventory,gold:s.gold,party:s.party,transact:action=>this.transact(action)});break;
      case 0x19:a=b();n=b();ids=Array.from({length:n},()=>({x:w()<<16>>16,y:w()<<16>>16}));v=Array.from({length:n+(n%2)},b);await Promise.all(ids.map((p,i)=>this.move(a+i,{...p,animationState:v[i],movementByte:255})));break;
      case 0x1a:a=b();n=b();ids=Array.from({length:n},w);v=Array.from({length:n+(n%2)},b);await Promise.all(ids.map((xy,i)=>xy?this.move(a+i,{x:((xy>>8)<<24>>24)*32,y:((xy&255)<<24>>24)*32,animationState:v[i],movementByte:255,pathOrder:'x-then-y'}):Promise.resolve()));break;
      case 0x1b:a=b();c=b();await this.move(0,{x:a*32,y:c*32,movementByte:255,pathOrder:'y-then-x',follow:true});break;
      case 0x1c:s.movement={x:b(),y:b(),speed:b(),flags:b()};await this.call('movement',s.movement);break;
      case 0x1e:s.animationSpeed=w();break;
      case 0x1f:a=b();await this.move(a,{animationState:b(),movementByte:255});break;
      case 0x20:a=w();c=this.entity(0);await this.move(0,{x:c.x+([0,0,-32,32][a]??0),y:c.y+([-32,32,0,0][a]??0),movementByte:a,animationState:[0,4,8,12][a],follow:true});break;
      case 0x21:case 0x22:a=b();c=b();s.flags[a]=op===0x21?(s.flags[a]??0)|(1<<c):(s.flags[a]??0)&~(1<<c);await this.call('collision',this.collisionPatches());break;
      case 0x23:while((a=w())<=15){const characterId=b(),animationState=b(),x=w()<<16>>16,y=w()<<16>>16,movementByte=b(),byte7=b();Object.assign(this.entity(a),{characterId,animationState,x,y,movementByte,byte7,active:characterId!==0});}await this.call('setEntities',s.entities);break;
      case 0x24:this.entity(w()).active=false;await this.call('setEntities',s.entities);break;
      case 0x25:s.mapId=w();s.battleMap={mapId:s.mapId,width:b(),height:b(),cameraX:b(),cameraY:b()};{// the battle map's own people replace the old map's (as 0x13 does), so villagers are not carried onto the battlefield
        const key=s.mapId.toString(16).padStart(4,'0'),list=structuredClone(this.data.npcs[key]??[]),mask=s.npcMasks[s.mapId]??0xffff;for(let i=0;i<list.length;i++)list[i].active=!!(mask&(1<<i));s.entities=[...s.entities.filter(x=>x.slot<8),...list];await this.call('setEntities',s.entities);}
        await this.call('prepareBattle',s.battleMap);break;
      case 0x26:s.party.push(w());break;
      case 0x27:await this.call('battleEnd',s);break;
      case 0x28:s.displayFlags=[b(),b()];break;
      case 0x29:v=await this.call('choice',{kind:'destination',region:s.region,current:s.destination,allowed:s.variables[s.region]??0,canCancel:!!((s.variables[s.region]??0)&(1<<s.destination))});if(v!=null&&!v.cancelled)s.destination=typeof v==='number'?v:v.value;s.selector=s.destination;break;
      case 0x2a:a=w();Object.assign(this.entity(a),{x:w()<<16>>16,y:w()<<16>>16});await this.call('setEntities',s.entities);break;   // 0x114DA: placed at once, no walk
      case 0x2b:a=b();c=b();await this.call('effect',{opcode:op,entity:a,value:c});break;
      case 0x2c:a=w();s.counters[a]=((s.counters[a]??0)+1)&255;break;
      case 0x2d:a=b();s.variables[a]=b();break;
      case 0x2e:case 0x2f:case 0x30:case 0x35:n=w();ids=Array.from({length:n},w);await this.call('effect',{opcode:op,entities:ids});break;
      case 0x31:s.region=b();s.destination=b();break;
      case 0x32:s.stage=w();break;
      case 0x33:a=w();c=w();n=w();await this.call('camera',{tileX:a,tileY:c,speed:n});break;   // camera to a cell (ROM 0x11702: FF6052/54 + FF605A, the shared camera request), e.g. showing 麻沸草
      case 0x38:v=this.data.battleGold[s.stage];if(v==null)throw Error('Unknown battle reward stage');s.gold+=v;await this.call('battleRewards',{stage:s.stage,gold:v});break;
      case 0x3a:s.displayFlag=w();break;
      case 0x3b:case 0x3c:await this.call('effect',{opcode:op,entity:w()});break;
      case 0x3d:s.spriteMask=((s.spriteMask??0x243)^(1<<w()))>>>0;break;   // FFE11C starts 0x243 (map props, 0x25F02)
      case 0x3e:a=w();c=w();if(Object.hasOwn(this.data.npcMasks??{},String(a))){s.npcMasks[a]=c;   // 0x11D64: only maps in table 0x18232; the current map's people are rebuilt at once (0x18198)
        if(a===s.mapId){const actors=structuredClone(this.data.npcs[s.mapId.toString(16).padStart(4,'0')]??[]);for(let i=0;i<actors.length;i++)actors[i].active=!!(c&(1<<i));s.entities=[...s.entities.filter(x=>x.slot<8),...actors];await this.call('setEntities',s.entities);}}break;
      case 0x3f:s.marker=w();break;
      case 0x40:await this.call('effect',{opcode:op,x:w(),y:w()});break;
      case 0x45:s.firstPartyIdentity=0x1515;if(s.roster?.[0]){s.roster[0][0]=0x15;s.roster[0][1]=0x15;}break;   // 0x11ED6: character 1's record becomes 宋江 (sprite and identity 0x15)
      case 0x4b:s.music=w();await this.call('music',s.music);break;
      case 0x4c:s.specialFlag=true;await this.call('mapMusic',s.mapId);break;   // back to this place's own music (ROM 0x11FF2 -> 0x27DC6)
      case 0x4d:await this.call('sound',w());break;
      case 0x4e:case 0x4f:break;
      default:throw Error(`Unsupported opcode ${op}`);
    }
  }
}
