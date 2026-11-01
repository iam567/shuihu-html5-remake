import test from 'node:test';import assert from 'node:assert/strict';import fs from 'node:fs';
import {StoryVM} from '../dist/js/story.js';
import {BattleSession} from '../dist/js/battle-session.js';
import {StageScheduler,unitBytes} from '../dist/js/stage-scheduler.js';
import {BattleEngine} from '../dist/js/battle.js';
const read=p=>JSON.parse(fs.readFileSync(new URL(`../dist/data/${p}`,import.meta.url)));
const story=read('story.json'),battleData=read('battle.json'),tables=read('battle-stages.json'),assets=read('assets.json');

function setup({stage,mapId,party,pick=o=>[...o.mandatory,...o.optional].slice(0,o.limit)}) {
  const map=assets.maps.find(m=>m.id===mapId.toString(16).padStart(4,'0'));
  const log=[];let session;
  const vm=new StoryVM({data:story,hooks:{battleReset:c=>session.onReset(c),battleEnd:()=>session.onEnd(),dialogue:id=>log.push(['dialogue',id])}});
  vm.state.party=[...party];vm.state.mapId=mapId;vm.state.stage=stage;
  session=new BattleSession({vm,battleData,tables,stage,battleMap:{mapId,width:map.widthTiles,height:map.heightTiles},passable:(x,y)=>map.collision[y*map.widthTiles+x]<0x50,
    ui:{chooseDeployment:async o=>{log.push(['deploy',o]);return pick(o);},runEvent:async(g,id)=>{log.push(['event',g,id]);await vm.start(g,id);},changed:()=>{},ended:async()=>log.push(['ended'])}});
  return {vm,session,log,events:()=>log.filter(l=>l[0]==='event').map(l=>l[2])};
}

test('unit RAM view keeps slot byte 0, 1/32-tile position words and HP word',()=>{
  const e=new BattleEngine({data:battleData,units:[{slot:12,raw:tables.stages[2].units[0].raw}]});
  const u=e.units[0];u.hp=7;const b=unitBytes(u);
  assert.equal(b[0],u.spriteType);assert.equal((b[2]<<8)|b[3],u.x*32);assert.equal((b[4]<<8)|b[5],u.y*32);assert.equal((b[18]<<8)|b[19],7);
});

test('stage 0: deployment, opening, victory event and party persistence follow the original scheduler',async()=>{
  const {vm,session,log,events}=setup({stage:0,mapId:0x100,party:[1,2,3]});
  await session.start();
  const deploy=log.find(l=>l[0]==='deploy')[1];
  assert.deepEqual(deploy,{mandatory:[1,3],optional:[2],limit:3});
  const e=session.engine,player=e.alive('player');
  assert.deepEqual(player.map(u=>[u.slot,u.identity]),[[0,1],[1,2],[2,3]]);
  assert.deepEqual([e.slotUnit(0).x,e.slotUnit(0).y],[10,10]);assert.deepEqual([e.slotUnit(2).x,e.slotUnit(2).y],[13,8]);
  assert.equal(e.alive('enemy').length,4);
  assert.deepEqual(events(),[0x45]);
  assert.equal(session.scheduler.state.turn,1);assert.equal(session.scheduler.state.phase,0);assert.equal(e.turn,1);
  e.slotUnit(0).experience=42;
  await session.act(engine=>{for(const u of engine.alive('enemy'))u.hp=0;return {ok:true};});
  assert.deepEqual(events(),[0x45,0x46]);assert.ok(session.ended);assert.ok(log.some(l=>l[0]==='ended'));
  assert.equal(vm.state.roster[0][7],42,'battle end (0x10ACE) writes experience back');
  assert.equal(vm.state.gold,150+story.battleGold[0],'new games start with 150 (ROM 0x730) plus the stage 0 reward');
});

test('stage 0: losing character 1 runs the retry event and redeploys',async()=>{
  const {session,events}=setup({stage:0,mapId:0x100,party:[1,2,3]});
  await session.start();const first=session.generation;
  await session.act(engine=>{engine.slotUnit(0).hp=0;return {ok:true};});
  assert.deepEqual(events(),[0x45,0x44,0x45]);
  assert.ok(session.generation>first);assert.equal(session.engine.alive('player').length,3);assert.equal(session.engine.alive('enemy').length,4);
  assert.equal(session.scheduler.state.turn,1);
});

test('stage 1: no scenario enemies; reinforcements arrive at the end of enemy phases while fewer than 7 remain',async()=>{
  const {session,events}=setup({stage:1,mapId:0x207,party:[1]});
  await session.start();
  assert.equal(session.engine.alive('enemy').length,0);
  const counts=[];
  for(let turn=0;turn<4&&!session.ended;turn++){await session.endPlayerPhase();counts.push(session.engine.alive('enemy').length);}
  const fired=events();
  assert.equal(fired[0],0x25);
  assert.ok(fired.some(id=>id>=0x27&&id<=0x2d),`reinforcement events fired: ${fired.map(x=>x.toString(16))}`);
  assert.ok(counts.at(-1)>0,`enemies on field per turn: ${counts}`);
});

test('every stage handler runs on an empty battle without touching unmapped RAM',()=>{
  for(let stage=0;stage<36;stage++){
    const e=new BattleEngine({data:battleData,units:[]});const s=new StageScheduler({stage,battle:e});
    for(const state of [{turn:0xff},{turn:3,phase:2,phaseDone:1}]){Object.assign(s.state,state);s.tick();}
  }
});
