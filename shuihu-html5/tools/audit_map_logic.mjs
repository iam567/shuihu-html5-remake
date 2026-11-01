import fs from 'node:fs';
import path from 'node:path';
import {fileURLToPath} from 'node:url';
import {createHash} from 'node:crypto';
import {StoryVM} from '../dist/js/story.js';

const root=fileURLToPath(new URL('../',import.meta.url));
const read=p=>JSON.parse(fs.readFileSync(p,'utf8'));
const hash=v=>createHash('sha256').update(v).digest('hex');
const hex=v=>v.toString(16).padStart(4,'0');
export function decodeLayer(rom,start){
  let p=start,mode=0,out=[];
  while(p<rom.length&&out.length<65536){
    const x=rom[p++];if(x===0xf0){mode=0;continue;}if(x===0xf1){mode=1;continue;}
    if(x<=0xef){out.push(x);continue;}
    let count=x&15;if(x===255){count=rom[p++];if(count===0)return {bytes:out,next:p};}
    if(p+mode>=rom.length)throw Error('Truncated compressed map');
    const unit=[...rom.subarray(p,p+mode+1)];p+=mode+1;
    for(let i=0;i<count;i++)out.push(...unit);
  }
  throw Error('Unterminated compressed map');
}
export const category=v=>v===0?'walk':v<80?'step':v===80?'block':v<128?'contact':v<=175?'investigate':'unknown';
const same=(a,b)=>JSON.stringify(a)===JSON.stringify(b);

// Stop before user decisions/battles. No invented battle outcome or world-map selection.
export async function traceEvent(data,mapId,eventId){
  const stop=Symbol('stop'),result={eventId,mode:category(eventId),scope:'fresh-state-first-transition',status:'no-map-transition',transitions:[]};
  const vm=new StoryVM({data,hooks:{
    changeMap:(id,spawn)=>{result.transitions.push({mapId:hex(id),spawnId:hex(spawn)});result.status='transition';throw stop;},
    choice:()=>{result.status='unresolved-choice';throw stop;},
    battle:()=>{result.status='unresolved-battle';throw stop;},
    prepareBattle:ctx=>{result.status='unresolved-battle';result.battleMapId=hex(ctx.mapId);throw stop;}
  }});
  // StoryVM annotates thrown Errors, so use an Error marker instead of throwing the symbol directly.
  const marker=new Error('Audit stopped at external boundary');marker.auditStop=stop;
  for(const [k,fn] of Object.entries(vm.hooks))vm.hooks[k]=(...args)=>{try{return fn(...args);}catch(e){if(e===stop)throw marker;throw e;}};
  vm.state.mapId=parseInt(mapId,16);vm.setEntities([{slot:0,active:true,x:0,y:0}]);
  try{await vm.start(parseInt(mapId.slice(0,2),16),eventId);}catch(e){if(e!==marker){result.status='unresolved-error';result.error=e.message;}}
  result.instructionCount=vm.trace.length;
  return result;
}

export async function buildAudit(){
  const source=path.resolve(root,'../md-game-analysis'),assets=read(path.join(root,'dist/data/assets.json')),data=read(path.join(root,'dist/data/story.json')),registry=read(path.join(root,'dist/data/hidden-items.json'));
  const romPath=path.join(source,'baseline',fs.readdirSync(path.join(source,'baseline')).find(f=>f.endsWith('.md'))),rom=fs.readFileSync(romPath),u16=p=>rom.readUInt16BE(p),u32=p=>rom.readUInt32BE(p);
  const tileRules=read(path.resolve(root,'../shuihu-assets/dist/data/tile-rules.json'));
  const maps=[],issues=[],byId=new Map(assets.maps.map(m=>[m.id,m]));
  const issue=(kind,mapId,detail)=>issues.push({kind,mapId,...detail});
  for(const map of assets.maps){
    const g=parseInt(map.id.slice(0,2),16),index=parseInt(map.id.slice(2),16),address=u32(u32(0x293ea+g*4)+index*4),layers=[];let cursor=address;
    for(let k=0;k<3;k++){const d=decodeLayer(rom,cursor);layers.push(d.bytes);cursor=d.next;}
    const n=map.widthTiles*map.heightTiles,graphicsMatch=same(layers[1],map.graphicLayer),logicMatch=same(layers[2],map.collision),catalogMatch=same(tileRules.maps[map.id]?.logic,map.collision)&&same(tileRules.maps[map.id]?.graphics,map.graphicLayer);
    if(!graphicsMatch||!logicMatch||!catalogMatch||n!==layers[2].length)issue('source-mismatch',map.id,{graphicsMatch,logicMatch,catalogMatch,expectedCells:n,actualCells:layers[2].length});
    const counts={walk:0,step:0,block:0,contact:0,investigate:0,unknown:0},cells=[],events=[];
    for(let i=0;i<n;i++){const v=map.collision[i],kind=category(v);counts[kind]++;cells.push({index:i,x:i%map.widthTiles,y:Math.floor(i/map.widthTiles),graphicId:map.graphicLayer[i],logic:v,kind});}
    for(const eventId of [...new Set(map.collision.filter(v=>v>0&&v!==80&&v<=175))].sort((a,b)=>a-b)){
      const event=await traceEvent(data,map.id,eventId);event.cellIndices=cells.filter(c=>c.logic===eventId).map(c=>c.index);
      for(const t of event.transitions){const dest=byId.get(t.mapId),spawn=data.spawns.find(s=>s.id===t.spawnId);t.destinationExists=!!dest;t.spawnExists=!!spawn;
        if(dest&&spawn){t.x=spawn.player_x/32;t.y=spawn.player_y/32;t.inBounds=t.x>=0&&t.y>=0&&t.x<dest.widthTiles&&t.y<dest.heightTiles;t.baseLogic=t.inBounds?dest.collision[Math.floor(t.y)*dest.widthTiles+Math.floor(t.x)]:null;t.dimensionsMatch=spawn.width===dest.widthTiles&&spawn.height===dest.heightTiles;}
        if(!dest||!spawn||!t.inBounds||!t.dimensionsMatch)issue('transition-needs-review',map.id,{eventId,transition:t});
      }events.push(event);
    }
    const patches=new Map();
    // Exercise each single story flag plus all bits; this is a bounded implementation check, not proof of reachable states.
    for(const flags of [0,...Array.from({length:16},(_,i)=>1<<i),65535]){const vm=new StoryVM({data});vm.state.flags[g]=flags;for(const p of vm.collisionPatches(parseInt(map.id,16))){const key=`${p.index}:${p.value}`;if(!patches.has(key))patches.set(key,{...p,exampleFlags:flags,inBounds:p.index>=0&&p.index<n});}}
    for(const p of patches.values())if(!p.inBounds)issue('original-buffer-write-outside-map',map.id,{...p,evidence:'ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7',impact:'Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification'});
    maps.push({id:map.id,width:map.widthTiles,height:map.heightTiles,bankId:tileRules.maps[map.id]?.bankId,dimensionEvidence:map.dimensionEvidence,romStart:address,graphicsSha256:hash(Buffer.from(layers[1])),logicSha256:hash(Buffer.from(layers[2])),graphicsMatch,logicMatch,catalogMatch,counts,cells,events,dynamicPatchCandidates:[...patches.values()],hiddenItems:registry.items.filter(i=>i.mapId===map.id).map(i=>({cellIndex:i.cellIndex,eventId:i.eventId,reward:i.reward}))});
  }
  const rawHidden=[];
  for(let group=0;group<13;group++){let p=u32(0xdc84a+group*4),bit=0;while(u16(p)){rawHidden.push({group,mapId:hex(u16(p)),cellIndex:u16(p+2),bit,address:p});p+=8;bit++;if(bit>32)throw Error('Hidden registry exceeds flag width');}}
  const hidden=[];
  for(const raw of rawHidden){const item=registry.items.find(i=>i.mapId===raw.mapId&&i.cellIndex===raw.cellIndex),map=byId.get(raw.mapId),checks={registry:!!item&&item.group===raw.group&&item.pickupFlag.bit===raw.bit};
    if(item&&map){const x=raw.cellIndex%map.widthTiles,y=Math.floor(raw.cellIndex/map.widthTiles);checks.coordinates=item.x===x&&item.y===y;checks.event=map.collision[raw.cellIndex]===item.eventId;checks.adjacentWalkable=[[0,1],[0,-1],[1,0],[-1,0]].some(([dx,dy])=>x+dx>=0&&y+dy>=0&&x+dx<map.widthTiles&&y+dy<map.heightTiles&&map.collision[(y+dy)*map.widthTiles+x+dx]<80);
      const pc=data.base+data.banks[item.group].entries[item.eventId],reward=u16(pc+2);checks.script=u16(pc)===22&&u16(pc+4)===65535;checks.reward=reward<=255?item.reward.kind==='item'&&item.reward.id===reward:item.reward.kind==='gold'&&item.reward.amount===u32(0x1aab2+(reward&255)*4);
      const rewards=[],vm=new StoryVM({data,hooks:{reward:r=>rewards.push(r)}});vm.state.mapId=parseInt(item.mapId,16);await vm.start(item.group,item.eventId);const first=vm.save();await vm.start(item.group,item.eventId);checks.once=rewards.length===1&&same(vm.save(),first);const restored=new StoryVM({data});restored.load(first);await restored.start(item.group,item.eventId);checks.saveLoad=same(restored.save(),first);checks.blockAfterPickup=restored.collisionPatches().some(p=>p.index===item.cellIndex&&p.value===80);
    }
    const passed=Object.values(checks).every(Boolean);if(!passed)issue('hidden-mismatch',raw.mapId,{cellIndex:raw.cellIndex,checks});hidden.push({...raw,checks,passed});
  }
  const runtime=read(path.join(source,'logic/runtime_map_validation.json')),allEvents=maps.flatMap(m=>m.events),summary={maps:maps.length,cells:maps.reduce((n,m)=>n+m.cells.length,0),graphicsMatched:maps.filter(m=>m.graphicsMatch).length,logicMatched:maps.filter(m=>m.logicMatch).length,hiddenLocations:rawHidden.length,hiddenPassed:hidden.filter(h=>h.passed).length,eventBindings:allEvents.length,stepBindings:allEvents.filter(e=>e.mode==='step').length,transitionBindings:allEvents.filter(e=>e.status==='transition').length,unresolvedBindings:allEvents.filter(e=>e.status.startsWith('unresolved')).length,issues:issues.length};
  return {formatVersion:1,scope:'Static ROM byte comparison and isolated HTML5 StoryVM checks. Not complete original-runtime or campaign validation.',source:{chapter6BroadPatchMatchesRom:rom.subarray(0x1c7ae,0x1c7ba).toString('hex')==='0c79060000ffe10066000032'&&rom.subarray(0x1c7ea,0x1c7f2).toString('hex')==='080100026700001a',romSha256:hash(rom),mapPointerTable:'0x293ea',hiddenPointerTable:'0xdc84a',storyBytesMatch:Buffer.from(data.bytes).equals(rom.subarray(data.base,data.base+data.bytes.length))},summary,limitations:['The same graphic ID can have different per-location logic; never derive collision from artwork.','Transitions trace fresh state only and stop at the first map load, player choice or battle; later state-dependent branches are not proven.','Active NPC footprints and story patches alter static collision. Dynamic patch candidates are not proof of reachable flag states.','Battle terrain, water access by unit class, later battle deployments and stage dispatch remain unverified.','Only the recorded opening-room runtime capture is cited here; other maps have no claimed full original-runtime traversal.','Visual geometry/door alignment of generated art requires separate review.'],originalRuntimeEvidence:runtime,maps,hidden,issues};
}

export function report(a){
  return `# 地图、入口与隐藏物品核验\n\n本报告区分原 ROM 字节核验、隔离脚本执行和原版运行证据。不能据此宣称整部游戏逻辑已与原版完全一致。\n\n- 地图 ${a.summary.maps} 张，地图格 ${a.summary.cells} 个；图块编号匹配 ${a.summary.graphicsMatched} 张，通行事件字节匹配 ${a.summary.logicMatched} 张。\n- 隐藏地点 ${a.summary.hiddenLocations} 处，奖励、一次领取、存档恢复检查通过 ${a.summary.hiddenPassed} 处。\n- 地图/事件绑定 ${a.summary.eventBindings} 个，其中踏入事件 ${a.summary.stepBindings} 个；隔离执行解析首个换图 ${a.summary.transitionBindings} 个，遇到战斗/选择/异常未解 ${a.summary.unresolvedBindings} 个。\n- 兼容性观察 ${a.summary.issues} 项：第6章标志位 bit2 会对小地图有效范围外写入3个位置；原ROM 0x1C7AE..0x1C80A 确实如此，目前保留原逻辑。这些位置不应出现在有效通行网格里。\n\n原 ROM SHA-256：${a.source.romSha256}。故事字节与 ROM 完全相同：${a.source.storyBytesMatch}。\n\n## 图块逻辑约束\n\n0 可走；1–79 可走且触发踏入事件；80 阻挡；81–127 阻挡并接触触发；128–175 阻挡并主动调查。美术替换保持每格原始编号和逻辑，不根据颜色或水面外观重推逻辑。战斗地形不能直接用这些探索代码推断。\n\n## 完整地图清单\n\n|地图|尺寸|通行/踏入|阻挡/接触/调查|隐藏|事件未解|\n|---|---|---|---|---|---|\n${a.maps.map(m=>`|${m.id}|${m.width}×${m.height}|${m.counts.walk}/${m.counts.step}|${m.counts.block}/${m.counts.contact}/${m.counts.investigate}|${m.hiddenItems.length}|${m.events.filter(e=>e.status.startsWith('unresolved')).length}|`).join('\n')}\n\n## 原版兼容性观察\n\n${a.issues.map(i=>`- ${i.kind}：地图 ${i.mapId}，${JSON.stringify(i)}`).join('\n')||'没有发现静态数据不一致。'}\n\n## 验证边界\n\n${a.limitations.map(l=>`- ${l}`).join('\n')}\n\n已留存的原版运行对照是开场 0106：图像层一致，逻辑格 84、85 在运行时从 0 改成 0x42，与开场阻止直接出门的剧情状态相符。其余地图未逐间完成原版运行对照。每格坐标、源图块号、原始逻辑、入口目的地图与出生点、39 隐藏点检查和动态改格候选均见 dist/data/map-logic-audit.json。\n\n复现：在项目目录运行 node tools/audit_map_logic.mjs；测试 node --test tests/map-logic.test.mjs。审计需要同级 md-game-analysis 中的基准 ROM，以及 shuihu-assets 中的 tile-rules.json。\n`;
}

if(process.argv[1]&&path.resolve(process.argv[1])===fileURLToPath(import.meta.url)){const audit=await buildAudit();fs.writeFileSync(path.join(root,'dist/data/map-logic-audit.json'),JSON.stringify(audit,null,2)+'\n');fs.writeFileSync(path.join(root,'MAP-LOGIC-AUDIT.md'),report(audit));console.log(JSON.stringify(audit.summary));}
