import test from 'node:test';
import assert from 'node:assert/strict';
import fs from 'node:fs';
import {buildAudit,decodeLayer,traceEvent} from '../tools/audit_map_logic.mjs';
import {StoryVM} from '../dist/js/story.js';

const audit=await buildAudit();
test('all 116 maps retain original ROM graphic indices and collision bytes',()=>{
  assert.equal(audit.summary.maps,116);
  assert.equal(audit.summary.graphicsMatched,116);
  assert.equal(audit.summary.logicMatched,116);
  assert.equal(audit.source.storyBytesMatch,true);
  assert(audit.maps.every(m=>m.catalogMatch&&m.cells.length===m.width*m.height));
  assert.equal(audit.issues.filter(i=>i.kind==='source-mismatch').length,0);
});
test('all original hidden registry entries retain reward and one-time save behavior',()=>{
  assert.equal(audit.summary.hiddenLocations,39);
  assert.equal(audit.summary.hiddenPassed,39);
  assert.equal(audit.maps.flatMap(m=>m.hiddenItems).length,39);
  assert(audit.hidden.every(h=>h.checks.reward&&h.checks.once&&h.checks.saveLoad&&h.checks.blockAfterPickup));
});
test('parsed map transitions point to known maps with valid matching spawn records',()=>{
  const transitions=audit.maps.flatMap(m=>m.events.flatMap(e=>e.transitions));
  assert(transitions.length>100);
  assert(transitions.every(t=>t.destinationExists&&t.spawnExists&&t.inBounds&&t.dimensionsMatch));
  const room=audit.maps.find(m=>m.id==='0106');
  assert(room.events.some(e=>e.transitions.some(t=>t.mapId==='0100')));
});
test('audit stops at external decisions instead of inventing a branch',async()=>{
  const data=JSON.parse(fs.readFileSync(new URL('../dist/data/story.json',import.meta.url)));
  const synthetic=structuredClone(data);synthetic.bytes=[0,0x29,255,255];synthetic.banks[1].entries[1]=0;
  const result=await traceEvent(synthetic,'0106',1);
  assert.equal(result.status,'unresolved-choice');
  assert.deepEqual(result.transitions,[]);
});
test('map decoder preserves byte and word repeats and rejects truncated streams',()=>{
  assert.deepEqual(decodeLayer(Buffer.from([1,0xf3,2,0xf1,0xf2,3,4,255,0]),0).bytes,[1,2,2,2,3,4,3,4]);
  assert.throws(()=>decodeLayer(Buffer.from([0xf1,0xf3,4]),0),/Truncated/);
});
test('chapter-six out-of-grid writes preserve original broad flag condition',()=>{
  assert.equal(audit.source.chapter6BroadPatchMatchesRom,true);
  const data=JSON.parse(fs.readFileSync(new URL('../dist/data/story.json',import.meta.url)));
  const vm=new StoryVM({data});vm.state.flags[6]=4;
  const expected=[{index:167,value:13},{index:191,value:13},{index:215,value:13}];
  assert.deepEqual(vm.collisionPatches(0x600),expected);
  assert.deepEqual(vm.collisionPatches(0x601),expected);
  const small=audit.maps.find(m=>m.id==='0601');
  assert(small.cells.every(c=>c.index<small.width*small.height));
  assert(audit.issues.every(i=>i.kind==='original-buffer-write-outside-map'));
});
