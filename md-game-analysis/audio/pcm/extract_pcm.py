from pathlib import Path
import struct,json,hashlib,wave,csv
P=Path(__file__).resolve().parents[2];OUT=P/'audio/pcm';ROM=next((P/'baseline').glob('*.md')).read_bytes();DRIVER=ROM[0x1e3b02:]
M={False:{x['sample_id']:x for x in json.loads((OUT/'measured-timing.json').read_text())},True:{x['sample_id']:x for x in json.loads((OUT/'measured-timing-normal.json').read_text())}}
(OUT/'raw').mkdir(exist_ok=True);(OUT/'wav_priority').mkdir(exist_ok=True);(OUT/'wav_normal').mkdir(exist_ok=True)
routes={}
for i in range(177):
 r=ROM[0x1d84b6+i*4:0x1d84b6+i*4+4]
 if r[0]&128:routes.setdefault(r[1]&127,[]).append({'sfx_id':i,'command':r[1],'volume_level':r[2]})
rows=[];unique={};timingchecks=[]
for sid in range(2,128):
 desc=0x1e3b02+0x1ad+(sid-1)*8
 a,n,b0,b1,delay,nxt=struct.unpack_from('<HHBBBB',ROM,desc)
 assert a>=0x8000 and a+n<=0x10000
 off=b1*65536+(b0&1)*32768+(a&32767);raw=ROM[off:off+n];assert len(raw)==n
 rawfile=f'raw/rom_{off:06X}_{n:04X}.u8';(OUT/rawfile).write_bytes(raw);unique[rawfile]=n
 row={'sample_id':sid,'descriptor_rom':hex(desc),'z80_source':hex(a),'rom_start':hex(off),'length':n,'bank_bits':[b0,b1],'delay':delay,'next_command':nxt,'format':'unsigned 8-bit mono PCM, midpoint 128','raw_file':rawfile,'raw_sha256':hashlib.sha256(raw).hexdigest(),'sfx_routes':routes.get(sid,[]),'playback':{}}
 for normal in [False,True]:
  m=M[normal][sid];v=bytes(m['first_64_values']);assert v==raw[:len(v)]
  intervals=m['interval_master_cycles'];mode='normal' if normal else 'priority'
  info={'captured_DAC_samples':m['dac_event_count'],'verified_prefix_bytes':len(v),'interval_histogram_master_cycles':intervals,'measurement':'NTSC-J Genesis Plus GX; CPU 68000 frozen; unmodified game Z80 driver; command volume 0 (no attenuation)'}
  if intervals:
   assert len(intervals)==1
   cycles=int(next(iter(intervals)));assert cycles==(217+14*delay+(0 if normal else 20))*15
   hz=53693175/cycles;rate=round(hz);dest=f'wav_{mode}/sample_{sid:03d}_delay_{delay:02d}_{rate}Hz.wav'
   with wave.open(str(OUT/dest),'wb') as f:f.setnchannels(1);f.setsampwidth(1);f.setframerate(rate);f.writeframes(raw)
   info.update({'nominal_ntsc_rate_numerator':53693175,'nominal_ntsc_rate_denominator':cycles,'nominal_ntsc_rate_hz':hz,'wav_rate_hz':rate,'wav_rate_rounding':'nearest integer; WAV header cannot encode the exact rational frequency','wav_file':dest})
  else: info['limitation']='Single-byte sample: no inter-write interval observed. Raw exported; no assumed-rate WAV generated.'
  row['playback'][mode]=info
 rows.append(row)
manifest={'rom_sha256':hashlib.sha256(ROM).hexdigest(),'descriptor_table_rom':'0x1e3caf','descriptor_width':8,'sample_id_scope':[2,127],'sample_id_1':'special one-byte source at Z80 RAM 0x0010, not ROM; no ROM PCM export','descriptor_count':len(rows),'unique_rom_spans':len(unique),'unique_raw_bytes':sum(unique.values()),'wav_count':sum('wav_file' in v for r in rows for v in r['playback'].values()),'timing_model':'priority cycles=(237+14*delay)*15; normal cycles=(217+14*delay)*15; all multi-byte descriptors validated against observed DAC write intervals. Frequency uses nominal NTSC master clock 53693175 Hz. Bus contention and PAL timing differ.','original_sample_recording_rate':'unknown; exported WAV rates reproduce observed driver playback, not original recording metadata','rows':rows}
(OUT/'pcm-index.json').write_text(json.dumps(manifest,ensure_ascii=False,indent=2));print({k:v for k,v in manifest.items() if k!='rows'})
