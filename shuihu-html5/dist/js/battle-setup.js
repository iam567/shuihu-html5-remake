// Original battle deployment (ROM 0x248E2, 0x184F4, 0x24B60, 0x1C898) and party persistence (0x10ACE, 0xFFC2).
// Persistent character records are 16 bytes (FFE630 + (id-1)*16): 0 sprite, 1 identity, 2-5 skills, 6 level,
// 7 experience, 8 subtype, 9 passive, 10-13 equipment, 14 class.

export function initialRoster(tables) {return tables.roster.map(r=>[...r]);}
const rosterIndex=identity=>(identity===0x15?1:identity)-1;

// Who must deploy, who may, and the size limit for this stage (0x248E2).
export function deploymentOptions(stageData,party) {
  const mandatory=party.filter(id=>stageData.mandatory.includes(id));
  return {mandatory,optional:party.filter(id=>!mandatory.includes(id)),limit:Math.min(stageData.maxDeploy,party.length)};
}

// 64-byte player unit record from a persistent record (same layout tools/export_story.py used for stage 0).
export function playerRaw(record,tables) {
  const v=new Array(64).fill(0);
  v[0]=record[0];v[1]=4;v[6]=1;v[7]=record[1];v.splice(8,4,...record.slice(2,6));v[16]=record[6];v[17]=record[7];
  v[36]=record[8];v[42]=record[9];v.splice(38,4,...record.slice(10,14));v[33]=record[14];
  for(let j=0;j<4;j++)v[43+j]=v[38+j]?tables.itemUses[v[38+j]]??0:0;
  v[27]=tables.movementBySubtype[v[36]]??0;
  return v;
}

const word=(raw,n)=>(raw[n]<<8)|raw[n+1];
const setWord=(raw,n,v)=>{raw[n]=(v>>8)&255;raw[n+1]=v&255;};

// First free cell in the 41-offset search order (0x24C1A for deployment, 0x14184 for script spawns).
export function freeCell({tables,origin,occupied,width,height,passable}) {
  for(const [dx,dy] of tables.placementOffsets){
    const x=origin.x+dx,y=origin.y+dy;
    if(x>=0&&y>=0&&x<width&&y<height&&!occupied.has(`${x},${y}`)&&passable(x,y))return {x,y};
  }
  return null;
}

// Unit records for the stage: chosen party members in slots 0.., scenario allies/enemies from firstSlot (0x1C898).
// `selected` is in party order. Team follows the original phase masks: player < firstSlot <= ally < 12 <= enemy.
export function deployBattle({stageData,tables,roster,selected,width,height,passable}) {
  const units=[];
  selected.forEach((id,slot)=>units.push({slot,raw:playerRaw(roster[rosterIndex(id)],tables),recalculate:true}));
  for(const u of stageData.units)units.push({slot:u.slot,raw:[...u.raw],recalculate:true});
  for(const u of units){u.team=u.slot<stageData.firstSlot?'player':u.slot<12?'ally':'enemy';u.raw[27]=tables.movementBySubtype[u.raw[36]]??u.raw[27];}
  // 0x24B60: mandatory members take their fixed coordinates; byte0 0x15 counts as character 1.
  for(const u of units.filter(u=>u.slot<selected.length)){
    const index=stageData.mandatory.indexOf(u.raw[0]===0x15?1:u.raw[0]);
    if(index>=0){setWord(u.raw,2,stageData.coordinates[index].x);setWord(u.raw,4,stageData.coordinates[index].y);}
  }
  // Slots 0..11 still at (0,0) are placed around slot 0, stopping at the first empty slot like the ROM loop; every
  // present unit, including those still at (0,0), blocks a cell.
  const slot0=units.find(u=>u.slot===0);
  for(let slot=0;slot<12;slot++){
    const u=units.find(v=>v.slot===slot);if(!u)break;
    if(word(u.raw,2)||word(u.raw,4))continue;
    const occupied=new Set(units.map(v=>`${word(v.raw,2)>>5},${word(v.raw,4)>>5}`));
    const cell=freeCell({tables,origin:{x:word(slot0.raw,2)>>5,y:word(slot0.raw,4)>>5},occupied,width,height,passable});
    if(cell){setWord(u.raw,2,cell.x<<5);setWord(u.raw,4,cell.y<<5);}
  }
  return units.sort((a,b)=>a.slot-b.slot);
}

// 0x10ACE (battle end) copies skills, level/experience and subtype of the deployed members back; 0xFFC2 (retry)
// copies level/experience and subtype only.
export function persistParty(roster,units,{skills=true}={}) {
  for(const u of units){
    const record=roster[rosterIndex(u.identity)];if(!record)continue;
    if(skills)record.splice(2,4,...u.skillIds.slice(0,4));
    record[6]=u.level;record[7]=u.experience;record[8]=u.subtype;
  }
  return roster;
}
