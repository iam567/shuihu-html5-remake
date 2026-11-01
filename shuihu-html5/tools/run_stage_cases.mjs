// Evaluates generated stage handlers on raw RAM images for md-game-analysis/logic/stage_events/verify_stage_rules.py.
import fs from 'node:fs';
import {StageCpu,stageHandlers} from '../dist/js/stage-rules.js';
const cases=JSON.parse(fs.readFileSync(process.argv[2]));
const out=cases.map(({stage,ram,ram6000})=>{
  const mem=new Uint8Array(65536);mem.set(Buffer.from(ram,'hex'),0xe000);mem.set(Buffer.from(ram6000,'hex'),0x6000);
  let event=null;
  const m={r:(size,a)=>{let v=0;for(let i=0;i<size;i++)v=v*256+mem[(a+i)&0xffff];return v>>>0;},w:(size,a,v)=>{for(let i=size-1;i>=0;i--){mem[(a+i)&0xffff]=v&255;v=Math.floor(v/256);}},event:id=>{event=id;}};
  stageHandlers[stage](m,new StageCpu());
  const r=(a,s)=>m.r(s,a);
  return {event,e1f5:r(0xffe1f5,1),e1d0:r(0xffe1d0,1),e1fc:r(0xffe1fc,4),'6019':r(0xff6019,1)};
});
process.stdout.write(JSON.stringify(out));
