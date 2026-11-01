"""Generate the 13 game music tracks with the sunoapi.org API (instrumental, traditional Chinese instruments, loopable).

Track roles follow where the cartridge uses them: the per-map table at ROM 0xDC72E gives 0 interiors (101 maps), 1 towns,
2 open country, 5 one special map; script opcode 0x4B switches to 3 (tense scenes), 4 (villains), 6 (lairs) and 10 (the
ending); the others serve battles, the world map and the title. Writes production/music-1/<n>-<k>.mp3 (two takes per
track) and status.json. The key is read from ~/.config/shuihu/suno.env (SUNO_API_KEY) and never printed.
Usage: python3 tools/generate_music.py [TRACK ...]
"""
import json,os,sys,time,urllib.request
from pathlib import Path

ROOT=Path(__file__).resolve().parents[1];OUT=ROOT/'production/music-1';OUT.mkdir(parents=True,exist_ok=True)
HOSTS=['https://api.sunoapi.org','https://apibox.erweima.ai']
COMMON=('instrumental game soundtrack for a Chinese historical strategy RPG (Water Margin, Song dynasty), real acoustic '
  'traditional Chinese instruments, warm natural recording, cinematic, seamless loop, no vocals, no chiptune, no 8-bit, no synth bass')
TRACKS={
 0:('居所','calm intimate indoor theme, guzheng and xiao flute, soft pipa, gentle and homely, slow'),
 1:('市镇','lively bustling market town theme, dizi flute and pipa, light percussion, cheerful folk melody, medium tempo'),
 2:('江湖行','open countryside travelling theme, erhu melody over guzheng arpeggios and soft strings, hopeful, wide landscape, medium tempo'),
 3:('暗流','tense suspenseful scene, low strings, sparse guqin, tanggu drum pulses, uneasy, slow build'),
 4:('奸佞','sinister villain theme, low erhu and suona, dark brass, menacing, slow and heavy'),
 5:('宫阙','grand imperial palace theme, bianzhong bells, sheng and guzheng, stately and majestic, slow'),
 6:('贼巢','ominous bandit lair theme, deep drums, low dizi, dissonant strings, dangerous, medium tempo'),
 7:('战鼓','heroic battle theme, big war drums, suona and erhu lead, driving strings, fast and energetic'),
 8:('敌军压境','enemy turn battle theme, darker heavy taiko and tanggu, low brass and strings, pressing, fast'),
 9:('决战','climactic boss battle theme, full orchestra with Chinese percussion and suona, epic and intense, fast'),
 10:('替天行道','ending theme, sweeping orchestra with erhu and guzheng, triumphant yet nostalgic, emotional, slow to medium'),
 11:('山河图','world map theme, adventurous and expansive, dizi melody with strings and light drums, medium tempo'),
 12:('梁山泊','main title theme, majestic and heroic, erhu and dizi melody, guzheng, war drums swelling, epic opening'),
 # Extra battle tunes (not on the cartridge): the battles rotate through more than its three so long campaigns vary.
 13:('血战','fierce battle theme, rapid pipa tremolo and pounding war drums, sharp suona stabs, urgent driving rhythm, fast'),
 14:('水泊鏖兵','marsh and river battle theme, rowing-beat drums, bold dizi and suona melody over surging strings, heroic, medium-fast'),
 15:('铁骑','cavalry charge battle theme, galloping percussion, soaring erhu lead with low brass, gongs on the accents, relentless, fast'),
}
def key():
  for line in (Path.home()/'.config/shuihu/suno.env').read_text().splitlines():
    if line.startswith('SUNO_API_KEY='):return line.split('=',1)[1].strip()
  raise SystemExit('no SUNO_API_KEY')
KEY=key()
def call(method,path,body=None):
  last=None
  for h in HOSTS:
    try:
      req=urllib.request.Request(h+path,data=json.dumps(body).encode() if body else None,method=method,
        headers={'Authorization':f'Bearer {KEY}','Content-Type':'application/json','Accept':'application/json','User-Agent':'curl/8.7.1'})
      with urllib.request.urlopen(req,timeout=60) as r:return json.loads(r.read())
    except Exception as e:last=e
  raise last
status_path=OUT/'status.json';status=json.loads(status_path.read_text()) if status_path.exists() else {}
def save():status_path.write_text(json.dumps(status,ensure_ascii=False,indent=1))
want=[int(a) for a in sys.argv[1:]] or list(TRACKS)
for n in want:
  if status.get(str(n),{}).get('taskId'):continue
  title,style=TRACKS[n]
  r=call('POST','/api/v1/generate',{'customMode':True,'instrumental':True,'model':'V6','title':title,'style':f'{style}, {COMMON}'[:1000],
    'negativeTags':'chiptune, 8-bit, retro game, synthwave, EDM, vocals, singing','duration':150,'callBackUrl':'https://example.invalid/none'})
  if r.get('code')!=200:print(n,'submit failed',r.get('code'),r.get('msg'));continue
  status[str(n)]={'title':title,'taskId':r['data']['taskId'],'state':'PENDING'};save();print(n,title,'submitted');time.sleep(1)
deadline=time.time()+1800
while time.time()<deadline:
  pending=[n for n in want if status.get(str(n),{}).get('taskId') and status[str(n)]['state'] not in ('SUCCESS','FAILED')]
  if not pending:break
  for n in pending:
    s=status[str(n)];r=call('GET',f"/api/v1/generate/record-info?taskId={s['taskId']}").get('data') or {}
    st=r.get('status','PENDING');s['state']=st
    if st=='SUCCESS':
      for k,item in enumerate((r.get('response') or {}).get('sunoData') or []):
        url=item.get('audio_url') or item.get('audioUrl')
        if url:open(OUT/f'{n:02d}-{k}.mp3','wb').write(urllib.request.urlopen(urllib.request.Request(url,headers={'User-Agent':'curl/8.7.1'}),timeout=120).read());s.setdefault('files',[]).append(f'{n:02d}-{k}.mp3');s.setdefault('durations',[]).append(item.get('duration'))
      print(n,s['title'],'done',s.get('durations'))
    elif 'FAIL' in st or 'ERROR' in st:s['state']='FAILED';print(n,'failed',st)
    save()
  time.sleep(15)
print(json.dumps({k:v['state'] for k,v in status.items()},ensure_ascii=False))
