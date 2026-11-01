import test from 'node:test';
import assert from 'node:assert/strict';
import {findPath,adjacentPath} from '../dist/js/pathfinding.js';
test('tap path routes around a solid wall without cutting diagonally',()=>{const wall=new Set(['2,0','2,1','2,2','2,3']);const path=findPath({x:0,y:0},{x:4,y:0},5,5,(x,y)=>!wall.has(`${x},${y}`));assert.equal(path.length,12);let p={x:0,y:0};for(const q of path){assert.equal(Math.abs(q.x-p.x)+Math.abs(q.y-p.y),1);assert(!wall.has(`${q.x},${q.y}`));p=q;}});
test('tap NPC stops adjacent and an enclosed NPC is unreachable',()=>{const pass=(x,y)=>!(x===2&&y===2);const path=adjacentPath({x:0,y:0},{x:2,y:2},5,5,pass);const end=path.at(-1);assert.equal(Math.abs(end.x-2)+Math.abs(end.y-2),1);assert.equal(adjacentPath({x:0,y:0},{x:2,y:2},5,5,(x,y)=>Math.abs(x-2)+Math.abs(y-2)>1),null);});
