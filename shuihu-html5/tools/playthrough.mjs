// Automatic story playthrough: searches the original game from the opening event onwards, the way a player would push it.
// From each exploration state it tries everything the player can trigger on the current map (step-on event cells 01-4F,
// touch/investigate cells 51-AF next to a reachable cell, talking to NPCs whose dialogue starts a script), with the
// game's own StoryVM. World-map choices branch over every allowed destination. Battles (opcode 25) run headless with the
// original stage scheduler (as simulate_battles.mjs) and are won by force after a few turns. States are deduplicated on
// story state (flags, counters, variables, party, stage, NPC masks, map, player area); search is best-first by battles
// won. Reports the furthest point reached, every script error, and the route there.
// Usage: node tools/playthrough.mjs [maxStates]   -> dist/data/playthrough.json
import fs from 'node:fs';
import {StoryVM} from '../dist/js/story.js';
import {BattleSession} from '../dist/js/battle-session.js';
const read=p=>JSON.parse(fs.readFileSync(new URL(`../dist/data/${p}`,import.meta.url)));
const story=read('story.json'),battleData=read('battle.json'),tables=read('battle-stages.json'),assets=read('assets.json'),npcs=read('npc-dialogues.json'),initial=read('initial-world.json');
const MAX=Number(process.argv[2]??4000),TURNS=6,hex=n=>Number(n).toString(16).padStart(4,'0');
const mapOf=id=>assets.maps.find(m=>m.id===hex(id));
// Position goals compared by the stage handlers (unit word +2 = x*32, +4 = y*32), as simulate_battles.mjs: escape-type stages.
const rules=fs.readFileSync(new URL('../dist/js/stage-rules.js',import.meta.url),'utf8').split('// Stage ').slice(1);
const goals=rules.map(body=>[...body.matchAll(/c\.cmp\(4,m\.r\(4,\(c\.a\[2\]\+2\)\),0x([0-9a-f]+)\)/g)].map(m=>{const v=parseInt(m[1],16);return {x:(v>>>16)>>5,y:(v&0xffff)>>5};}));

class Halt extends Error{}
// Run fn against a VM restored from `state`; hooks reproduce app.js (changeMap, prepareBattle, choice ...).
async function run(state,fn,plan=[]){
  const log={choices:[],battles:[],maps:[],errors:[],texts:[],walls:[]};let pending=null,choiceIndex=0,steps=0;const vm=new StoryVM({data:story});
  vm.load(state);
  const changeMap=(id,spawnId,ctx={})=>{const m=mapOf(id);if(!m)throw Error('missing map '+hex(id));const ents=ctx.entities??vm.state.entities;const sp=story.spawns.find(s=>s.id===hex(spawnId)),p=ents.find(e=>e.slot===0);
    if(spawnId!=null&&sp&&p)Object.assign(p,{x:sp.player_x,y:sp.player_y,active:true});vm.state.mapId=Number(id);vm.state.entities=ents;log.maps.push(hex(id));};
  vm.hooks={changeMap,setEntities:a=>{vm.state.entities=a;},moveEntity:(id,u)=>{const e=vm.entity(id);if(u.x==null||!e.active)return;const m=mapOf(vm.state.mapId);const col=[...m.collision];for(const q of vm.collisionPatches())col[q.index]=q.value;
      // Cells crossed on the way, x first then y (as the ROM's scripted walk 0x3D6E); cells outside the map are fine (walking off).
      const W=m.widthTiles,H=m.heightTiles,cells=[];let x=Math.round(e.x/32),y=Math.round(e.y/32);const tx=Math.round(u.x/32),ty=Math.round(u.y/32),xf=u.pathOrder!=='y-then-x';
      for(let k=0;k<200&&(x!==tx||y!==ty);k++){if(xf?x!==tx:y===ty)x+=Math.sign(tx-x);else y+=Math.sign(ty-y);if(x>=0&&y>=0&&x<W&&y<H&&col[y*W+x]>=0x50)cells.push(`${x},${y}:${col[y*W+x].toString(16)}`);}
      if(cells.length)log.walls.push(`${hex(vm.state.mapId)} ev ${vm.current?.group}:${vm.current?.id.toString(16)} slot ${id} (${Math.round(e.x/32)},${Math.round(e.y/32)})->(${tx},${ty}) through ${cells.join(' ')}`);},dialogue:d=>{log.texts.push(d);},
    prepareBattle:c=>{changeMap(c.mapId,null);pending={...c,stage:vm.state.stage};},
    choice:c=>{const allowed=[...Array(8).keys()].filter(i=>c.allowed&(1<<i));log.choices.push({at:choiceIndex,region:c.region,current:c.current,allowed,event:vm.event?`${vm.event.group}:${vm.event.id.toString(16)}`:null});const v=plan[choiceIndex++];return v==null?(c.canCancel?{cancelled:true}:allowed[0]):v;},
    error:e=>log.errors.push(e.message)};
  const start=async(g,id)=>{if(++steps>200)throw new Halt('event loop');await vm.start(g,id);};
  try{
    await fn(vm,start);
    while(pending){const p=pending;pending=null;log.battles.push(p.stage);await battle(vm,p,start,log);}
  }catch(e){log.errors.push(e instanceof Halt?e.message:`${e.message} @${e.event?`${e.event.group}:${e.event.id.toString(16)}`:'?'} pc ${e.pc?.toString(16)}`);}
  return {state:vm.running?null:vm.save(),log};
}
async function battle(vm,p,start,log){
  const map=mapOf(p.mapId);let session;
  session=new BattleSession({vm,battleData,tables,stage:p.stage,battleMap:{mapId:p.mapId,width:p.width??map.widthTiles,height:p.height??map.heightTiles},passable:(x,y)=>map.collision[y*map.widthTiles+x]<0x50,
    ui:{chooseDeployment:async o=>[...o.mandatory,...o.optional].slice(0,o.limit),runEvent:(g,id)=>start(g,id),changed:()=>{},ended:async()=>{}}});
  vm.hooks.battleReset=c=>session.onReset(c);vm.hooks.battleEnd=()=>session.onEnd();
  await session.start();let forced=false;
  for(let turn=0;turn<TURNS*3&&!session.ended;turn++){
    const e=session.engine;
    if(turn>=TURNS){forced=true;await session.act(en=>{for(const u of en.alive('enemy'))u.hp=0;return {ok:true};});if(session.ended)break;}
    for(const id of e.aiOrder('player')){if(session.ended||session.engine!==e)break;await session.act(en=>{en.aiAct(id);return {ok:true};});}
    if(!session.ended&&session.engine===e)await session.endPlayerPhase();
    if(forced&&!session.ended)for(const goal of goals[p.stage]??[]){if(session.ended)break;const u=session.engine.alive('player').find(u=>!u.acted)??session.engine.alive('player')[0];if(u)await session.act(en=>{Object.assign(u,goal);return {ok:true};});}
  }
  log.battleResults=(log.battleResults??[]).concat([{stage:p.stage,ended:session.ended,forced}]);
  if(!session.ended)throw Error(`battle ${p.stage} did not end`);
}

// Exploration: what the player can trigger from the current state.
function actions(state){
  const m=mapOf(state.mapId),W=m.widthTiles,H=m.heightTiles,vm=new StoryVM({data:story});vm.load(state);
  const col=[...m.collision];for(const q of vm.collisionPatches())col[q.index]=q.value;
  const npcAt=new Map(state.entities.filter(e=>e.active&&e.slot>=8&&e.slot<=15).map(e=>[`${Math.round(e.x/32)},${Math.round(e.y/32)}`,e]));
  const p=state.entities.find(e=>e.slot===0);if(!p)return {list:[],area:'?'};const s={x:Math.round(p.x/32),y:Math.round(p.y/32)};
  const seen=new Set([`${s.x},${s.y}`]),queue=[s],out=[];
  for(let i=0;i<queue.length;i++){const c=queue[i];
    for(const [dx,dy] of [[0,1],[1,0],[0,-1],[-1,0]]){const x=c.x+dx,y=c.y+dy,k=`${x},${y}`;if(x<0||y<0||x>=W||y>=H||seen.has(k))continue;const v=col[y*W+x];
      if(npcAt.has(k)){out.push({type:'talk',slot:npcAt.get(k).slot,from:c});continue;}
      if(v>=0x51&&v<=0xaf){out.push({type:'touch',ev:v,cell:{x,y},from:c});continue;}
      if(v>=0x50)continue;seen.add(k);if(v>0){out.push({type:'step',ev:v,cell:{x,y}});continue;}queue.push({x,y});}}
  const area=[...seen].sort()[0];
  const uniq=new Map();for(const a of out)uniq.set(`${a.type}:${a.ev??a.slot}`,a);
  return {list:[...uniq.values()],area};
}
function perform(a){return async(vm,start)=>{const p=vm.state.entities.find(e=>e.slot===0);const g=vm.state.mapId>>8;
  if(a.type==='step'){Object.assign(p,{x:a.cell.x*32,y:a.cell.y*32});await start(g,a.ev);}
  else if(a.type==='touch'){Object.assign(p,{x:a.from.x*32,y:a.from.y*32});await start(g,a.ev);}
  else{Object.assign(p,{x:a.from.x*32,y:a.from.y*32});const actor=vm.state.entities.find(e=>e.slot===a.slot);const vars=npcs.identities.find(i=>i.identity===actor.byte7)?.variants??[];
    const key=vars[vm.state.counters[actor.byte7]??0]??vars[0],d=npcs.dialogues.find(d=>d.id===key);if(d?.scriptId!=null)await start(g,d.scriptId);}};}
const keyOf=(s,area)=>JSON.stringify([s.flags,s.counters,s.variables,s.party,s.stage,s.npcMasks,s.mapId,s.region,s.destination,area]);
const label=a=>a.type==='talk'?`talk slot ${a.slot}`:`${a.type} ${a.ev.toString(16)}`;

// Opening, as app.js newGame.
const init=new StoryVM({data:story});init.setEntities(initial.actors);init.state.mapId=0x106;
const first=await run(init.save(),async(vm,start)=>{await start(1,0x41);});
const walls=new Set(),seen=new Set(),errors=[],frontier=[{state:first.state,won:0,route:['opening'],battles:first.log.battles}];let best=frontier[0],explored=0;
while(frontier.length&&explored<MAX){
  frontier.sort((a,b)=>b.won-a.won||a.route.length-b.route.length);const node=frontier.shift();explored++;
  const {list,area}=actions(node.state);const k=keyOf(node.state,area);if(seen.has(k))continue;seen.add(k);
  if(node.won>best.won||(node.won===best.won&&node.state.stage>best.state.stage))best=node;
  for(const a of list){
    for(let plans=[[]],i=0;i<plans.length&&i<10;i++){
      const r=await run(node.state,perform(a),plans[i]);
      for(const c of r.log.choices)if(c.at===plans[i].length)for(const v of c.allowed)plans.push([...plans[i],v]);
      const step=`${hex(node.state.mapId)} ${label(a)}${plans[i].length?' choose '+plans[i].join(','):''}${r.log.battles.length?' BATTLE '+r.log.battles.join(','):''}`;
      for(const w of r.log.walls)walls.add(w);if(r.log.errors.length)errors.push({route:[...node.route,step],errors:r.log.errors,choices:r.log.choices});
      if(r.state)frontier.push({state:r.state,won:node.won+(r.log.battleResults??[]).filter(b=>b.ended).length,route:[...node.route,step],battles:[...node.battles,...r.log.battles],texts:r.log.texts.slice(-6)});
    }
  }
}
const report={wallCrossings:[...walls],finalState:best.state,finalTexts:best.texts,finalActions:actions(best.state).list.map(label),explored,uniqueStates:seen.size,furthest:{battlesWon:best.won,stage:best.state.stage,map:hex(best.state.mapId),party:best.state.party,route:best.route},
  errors:[...new Map(errors.map(e=>[e.errors.join('|'),e])).values()].slice(0,40)};
fs.writeFileSync(new URL('../dist/data/playthrough.json',import.meta.url),JSON.stringify(report,null,1));
console.log(JSON.stringify({explored,unique:seen.size,battlesWon:best.won,stage:best.state.stage,map:hex(best.state.mapId),party:best.state.party,errors:report.errors.length}));
for(const e of report.errors.slice(0,12))console.log('ERR',e.errors.join(' | '),' <- ',e.route.slice(-3).join(' > '));
console.log('WALL CROSSINGS',walls.size);for(const w of [...walls].slice(0,60))console.log('  ',w);console.log('ROUTE TAIL',best.route.slice(-12).join('\n  '));
