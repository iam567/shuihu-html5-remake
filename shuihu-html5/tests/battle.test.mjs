import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {BattleEngine,unitFromRecord,baseDamage,growthStats,OriginalRNG,hitSuccess} from '../dist/js/battle.js';
const data=JSON.parse(await readFile(new URL('../dist/data/battle.json',import.meta.url)));
const probes=JSON.parse(await readFile('/Users/taoo/Documents/ChatGPT/日常/md-game-analysis/logic/combat_probe_results.json'));
for(const p of probes){let a=unitFromRecord({attack:[p.attack,p.attack],classId:p.attacker_class,status:[0,0,p.halve_attack,0]});let t=unitFromRecord({defense:[p.defense,p.defense],classId:p.target_class,status:[0,0,0,p.halve_defense]});assert.equal(baseDamage(a,t,data.skills[p.skill-1],data.matrix,p.mode),p.observed_d2);}
for(const r of data.initialUnits.filter(u=>u.sprite_type&&u.level&&u.max_hp)){const u=unitFromRecord(r),g=growthStats(data,u.classId,u.level,u.passive);assert.equal(g.maxHp,u.maxHp);assert.deepEqual(g.attack,u.attack);assert.deepEqual(g.defense,u.defense);assert.equal(g.critical,u.critical);assert.equal(g.hit,u.hit);assert.equal(g.resist,u.resist);}
const rng=new OriginalRNG(1);assert.equal(rng.next(),28); // state 32722, low six bits 18.
let calls=0;const fixed={next(){calls++;return 0;}};assert.equal(hitSuccess({hit:200},{status:[0],resist:100},{hit_bonus:100},fixed),false);assert.equal(calls,0);assert.equal(hitSuccess({hit:0},{status:[1],resist:255},{hit_bonus:0},fixed),true);assert.equal(calls,0);
const a={id:'p',team:'player',name:'测试我军',x:1,y:1,attack:[80,80],hp:100,maxHp:100,hit:1,resist:0,movement:3};
const e={id:'e',team:'enemy',x:4,y:1,hp:100,maxHp:100,attack:[10,10],hit:1,resist:0};
let engine=new BattleEngine({data,width:7,height:5,units:[a,e],passable:(x,y)=>!(x===2&&y===1)});
assert.equal(engine.move('p',2,1).ok,false);assert.equal(engine.move('e',3,1).ok,false);assert.equal(engine.move('p',3,1).ok,false);assert.equal(engine.move('p',2,2).ok,true);assert.equal(engine.move('p',3,2).ok,false);assert.equal(engine.attack('p','e').ok,false);
const saved=engine.serialize();const restored=BattleEngine.restore(saved,{data,passable:engine.passable});assert.deepEqual(restored.serialize(),saved);restored.endTurn();assert.equal(restored.turn,2);assert.equal(restored.activeTeam,'player');assert(restored.unit('e').x<4||restored.unit('e').y!==1);
let victories=0;engine=new BattleEngine({data,width:4,height:4,units:[{...a,x:0,y:0},{...e,x:1,y:0,hp:1}],onVictory:()=>victories++});assert.equal(engine.attack('p','e').ok,true);assert.equal(engine.result,'victory');assert.equal(victories,1);assert.equal(engine.attack('p','e').ok,false);
console.log('PASS: 7 ROM damage probes; growth table/unit comparisons; inclusive hit and byte overflow; blocked movement, turns, AI, save/restore and victory.');
