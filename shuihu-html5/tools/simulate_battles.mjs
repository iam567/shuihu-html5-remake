// Headless run of all 36 battles with the original stage scheduler and event scripts.
// Player units use the same reconstructed AI as enemies; after `turns` player turns any remaining enemies are
// removed to exercise the victory path. Writes dist/data/battle-simulation.json. Usage: node tools/simulate_battles.mjs [turns]
import fs from 'node:fs';
import {StoryVM} from '../dist/js/story.js';
import {BattleSession} from '../dist/js/battle-session.js';
const read=p=>JSON.parse(fs.readFileSync(new URL(`../dist/data/${p}`,import.meta.url)));
const story=read('story.json'),battleData=read('battle.json'),tables=read('battle-stages.json'),assets=read('assets.json');
// Battle map per stage, from dry-running every event with world-map selectors 0..15 (prepareBattle after opcode 0x32).
const STAGE_MAPS=[0x100,0x207,0x200,0x206,0x200,0x307,0x309,0x408,0x300,0x409,0x600,0x609,0x500,0x507,0x508,0x707,0x708,0x709,0x808,0x809,0x906,0x907,0x908,0xa06,0xa08,0xb05,0xb06,0xb07,0xb08,0xb09,0xb0a,0xc05,0xc06,0xc07,0xc08,0xc04];
const TURNS=Number(process.argv[2]??30);
// Position goals compared by the stage handlers (unit word +2 = x*32, +4 = y*32), used to walk a unit onto them.
const rules=fs.readFileSync(new URL('../dist/js/stage-rules.js',import.meta.url),'utf8').split('// Stage ').slice(1);
const goals=rules.map(body=>[...body.matchAll(/c\.cmp\(4,m\.r\(4,\(c\.a\[2\]\+2\)\),0x([0-9a-f]+)\)/g)].map(m=>{const v=parseInt(m[1],16);return {x:(v>>>16)>>5,y:(v&0xffff)>>5};}));
const results=[];
for(let stage=0;stage<36;stage++){
  const mapId=STAGE_MAPS[stage],map=assets.maps.find(m=>m.id===mapId.toString(16).padStart(4,'0'));
  const events=[];let session,error=null,forced=false,peakEnemies=0;
  const vm=new StoryVM({data:story,hooks:{battleReset:c=>session.onReset(c),battleEnd:()=>session.onEnd(),choice:()=>0}});
  vm.state.party=Array.from({length:20},(_,i)=>i+1);vm.state.mapId=mapId;vm.state.stage=stage;
  try{
    session=new BattleSession({vm,battleData,tables,stage,battleMap:{mapId,width:map.widthTiles,height:map.heightTiles},passable:(x,y)=>map.collision[y*map.widthTiles+x]<0x50,
      ui:{chooseDeployment:async o=>[...o.mandatory,...o.optional].slice(0,o.limit),runEvent:async(g,id)=>{events.push(id);if(events.length>400)throw Error('too many events');await vm.start(g,id);},changed:()=>{},ended:async()=>{}}});
    await session.start();
    for(let turn=0;turn<TURNS*2&&!session.ended;turn++){
      const e=session.engine;peakEnemies=Math.max(peakEnemies,e.alive('enemy').length);
      if(turn>=TURNS&&!forced){forced=true;await session.act(engine=>{for(const u of engine.alive('enemy'))u.hp=0;return {ok:true};});continue;}
      for(const id of e.aiOrder('player')){if(session.ended||session.engine!==e)break;await session.act(engine=>{engine.aiAct(id);return {ok:true};});}
      if(!session.ended&&session.engine===e)await session.endPlayerPhase();
      if(forced&&!session.ended)await session.act(engine=>{for(const u of engine.alive('enemy'))u.hp=0;return {ok:true};});
      if(forced&&!session.ended)for(const goal of goals[stage]){
        if(session.ended)break;const u=session.engine.alive('player').find(u=>!u.acted)??session.engine.alive('player')[0];
        if(u)await session.act(engine=>{Object.assign(u,goal);return {ok:true};});
      }
    }
  }catch(e){error=e.message;}
  const e=session?.engine;
  results.push({stage,goals:goals[stage],map:mapId.toString(16),ended:!!session?.ended,forcedVictory:forced,turn:session?.scheduler?.state.turn,retries:events.filter(id=>id===0x44).length,
    deployed:session?.selected?.length,scenarioUnits:tables.stages[stage].units.length,peakEnemies,events:events.map(x=>x.toString(16)),error});
}
fs.writeFileSync(new URL('../dist/data/battle-simulation.json',import.meta.url),JSON.stringify({description:'Headless simulation with reconstructed AI on both sides; checks scheduler/event integration, not original AI balance.',turnsBeforeForcedVictory:TURNS,results},null,1));
for(const r of results)console.log(`${String(r.stage).padStart(2)} map ${r.map} ${r.ended?'END':'---'} ${r.forcedVictory?'forced':'      '} turn ${r.turn} retries ${r.retries} events ${r.events.join(',')}${r.error?' ERROR '+r.error:''}`);
