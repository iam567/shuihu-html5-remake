import {ArtSelection,ART_STYLES,resolveArt} from './art-style.js';
import {bindJoystick} from './joystick.js';
import {StoryVM} from './story.js';
import {BattleSession} from './battle-session.js'; import {growthStats,terrainLimit} from './battle.js'; import {initialRoster} from './battle-setup.js';
import {findPath,adjacentPath} from './pathfinding.js';
import {playIntro} from './title-intro.js';
import {OriginalForeground} from './foreground.js';
const $=id=>document.getElementById(id),canvas=$('game'),ctx=canvas.getContext('2d');
const hex=n=>Number(n).toString(16).padStart(4,'0');
let unicode={glyphs:{},overrides:{}},assets,storyData,npcs,battleData,battleStages,initial,vm,map,actors=[],collision=[],camera={x:0,y:0},route=[],walking=false,busy=false,dialogue=null,battle=null,session=null,pendingBattle=null,selectedSkill=null,modalStack=[],music=new Audio(),soundEnabled=false,currentMusic=12;   // 12 = title theme until a script picks the scene music
const images=new Map();
let artManifest={},art,foreground,itemText={},worldMapData=null,musicData=null,propData=null,musicStamp=0,objectives=null,sceneMusic=null,bagSelection=null,statusSelection=null,hdSprites={},attackMenuOpen=false,itemMenuOpen=false,moveMode=false,inspectId=null;const view={width:320,height:320,scale:1};
function img(path){if(!path)return null;if(!images.has(path)){const i=new Image();i.src=path;images.set(path,i);}return images.get(path);}
async function ready(path){const i=img(path);if(i&&!i.complete)await i.decode();return i;}
function toast(t){$('toast').textContent=t;$('toast').classList.add('show');clearTimeout(toast.timer);toast.timer=setTimeout(()=>$('toast').classList.remove('show'),2000);}
function button(label,fn,cls=''){const b=document.createElement('button');b.textContent=label;b.className=cls;b.onclick=fn;return b;}
function closeModal(all=false){const m=modalStack.pop();m?.cancel?.();if(all){while(modalStack.length)modalStack.pop()?.cancel?.();}$('modalHost').hidden=!modalStack.length;if(modalStack.length)renderModal();}
function modal(title,build,actions=[],cancel){modalStack.push({title,build,actions,cancel});renderModal();}
function renderModal(){const m=modalStack.at(-1);$('modalHost').hidden=false;$('modalTitle').textContent=m.title;$('modalBody').replaceChildren();m.build($('modalBody'));$('modalFooter').replaceChildren(...(m.actions.length?[footerButton(modalStack.length>1?'取消 / 返回':'关闭',()=>closeModal()),...m.actions.map(a=>footerButton(a.label,a.fn,a.primary))]:[]));$('modalFooter').hidden=!m.actions.length;$('modalBack').replaceChildren(Object.assign(document.createElement('img'),{src:'assets/ui/buttons/btn-back.webp',alt:'返回'}));$('modalBack').style.visibility='hidden';   // the bottom bar is always there, so dialogs only need 关闭
$('modalClose').replaceChildren(Object.assign(document.createElement('img'),{src:'assets/ui/buttons/btn-close.webp',alt:'关闭'}));$('modalClose').focus();}
$('modalClose').onclick=()=>closeModal(true);$('modalBack').onclick=()=>closeModal();document.querySelector('.scrim').onclick=()=>closeModal(true);
/* Esc and the other keys: see inputCancel / the direction-key handlers further down. */
function para(host,text){const p=document.createElement('p');p.textContent=text;host.append(p);return p;}
// Section title on a plaque (from the UI boards), with an optional one-line note under it.
// Character status, from the persistent record (FFE630 layout: 6 level, 7 experience, 8 subtype, 9 passive, 10-13
// equipment, 14 class) and battle.js growthStats; movement by subtype as battle-setup.js uses it.
// The 15 battle classes (record byte 14, matrix index) named after the job line they cover; job titles come from the
// subtype byte (8): job_names[subtype-1], e.g. subtype 11 = 神行者 (戴宗), 17 = 鐵砲手 (呼延灼).
const CLASS_NAMES=['刀客','風水師','策士','郎中','刺客','拳師','漁人','弓箭手','槍術師','鐵砲手','殭屍','金力士','神兵','駕蔚人','隱士'];
function jobName(subtype){return tokensText(assets.job_names.find(j=>j.id===(subtype||1)-1));}
// Test cheat (hidden): tap 燕青's portrait on the status page 20 times to be asked to enable it; then each tap on a
// person's 经验 adds 500 experience (levels and job steps follow as in battle.js) and each tap on the bag's silver adds
// 1000. Remembered in this browser only.
let cheatOn=false,cheatTaps=0;try{cheatOn=localStorage.getItem('shuihu.cheat')==='1';}catch{}
function cheatExp(id){const r=editableRecord(id);let exp=(r[7]??0)+500,level=r[6]||1;
  while(exp>99&&level<99){exp-=100;level++;const chain=battleData.progression.find(c=>c.class===(r[14]??0)),step=chain?.pairs.find(p=>p.subtype===r[8]&&p.transition_at_level===level);if(step?.next_subtype)r[8]=step.next_subtype;}
  r[6]=level;r[7]=Math.min(99,exp);save();renderModal();toast(`经验 +500 · Lv ${level}`);}
function rosterRecord(id){const roster=vm.state.roster??initialRoster(battleStages);return roster[(id===0x15?1:id)-1];}
// Equipment. Slots 10-13 of the persistent record carry weapons/books (with uses in battle); byte 9 is the passive slot
// (兵法/飾品 112-123, x1.1 bonuses in battle.js). Which item kinds a class carries is taken from the original's own
// unit data: across all 505 roster/stage units each class only ever holds these kinds.
const ITEM_KINDS=[[1,13,'刀劍'],[14,21,'爪'],[22,30,'弓'],[31,42,'槍戟'],[43,48,'火器'],[64,75,'兵書'],[76,77,'毒針'],[80,85,'咒'],[86,89,'降神'],[90,90,'桃木劍'],[96,104,'醫書'],[112,123,'飾品']];
const CLASS_KINDS=[['刀劍'],['兵書','咒','降神','桃木劍'],['兵書'],['毒針','醫書','兵書'],['刀劍'],['爪'],['槍戟'],['弓'],['槍戟'],['火器'],['爪'],['爪'],['槍戟'],['刀劍'],['兵書','醫書']];
function itemKind(item){return ITEM_KINDS.find(([lo,hi])=>item>=lo&&item<=hi)?.[2];}
// Who may use an item is by job step, not class (ROM 0x1A130: a mask per item, bit = subtype-1; tested at 0x1A0DC against
// the record's subtype +8): stronger blades wait for 刀神, bows are 神射手's, 刺客之書 only goes with a 神行者, and so on.
function canUse(subtype,item){const m=battleData?.equipMasks?.[Number(item)];return m!=null&&((m>>>(((subtype||1)-1)&31))&1)===1;}
function canEquip(record,slot,item){const kind=itemKind(Number(item));return slot==='passive'?kind==='飾品':!!kind&&kind!=='飾品'&&Number(item)<128&&canUse(record[8],item);}
function editableRecord(id){vm.state.roster??=initialRoster(battleStages);return vm.state.roster[(id===0x15?1:id)-1];}
function setEquip(id,slot,item){if(equipLocked())return;const r=editableRecord(id),at=slot==='passive'?9:10+slot,old=r[at],inv=vm.state.inventory;if(old)inv[old]=(inv[old]??0)+1;if(item){inv[item]-=1;if(inv[item]<=0)delete inv[item];}r[at]=item?Number(item):0;save();}
function chooseEquip(id,slot){const r=rosterRecord(id),list=Object.entries(vm.state.inventory).filter(([item,n])=>n>0&&canEquip(r,slot,item));
  if(!list.length)return toast(slot==='passive'?'行囊里没有饰品':`行囊里没有${unitName(id)}能用的装备`);
  pickItem(slot==='passive'?'选择饰品':'选择装备',list,'确定',item=>{setEquip(id,slot,item);closeModal();renderModal();toast(`装上 ${itemName(item)}`);});}
// The battle menu has no equipment screen (0x25538): what is worn and carried is fixed once the battle starts (and the
// battle's units write their items back afterwards, so a change made now would be lost or doubled).
const equipLocked=()=>{if(session&&!session.ended){toast('战斗中不能更换装备和道具');return true;}return false;};
function equipSlot(id,slot,item){if(equipLocked())return;if(!item)return chooseEquip(id,slot);modal(itemName(item),h=>{const box=document.createElement('div');box.className='item-detail';box.append(itemIcon(item));const t=document.createElement('p');t.textContent=itemText[Number(item)]??'';box.append(t,statChips(item));h.append(box);},
  [{label:'更换',primary:true,fn:()=>chooseEquip(id,slot)},{label:'卸下',fn:()=>{setEquip(id,slot,0);closeModal();renderModal();toast(`卸下 ${itemName(item)}`);}}]);}
function tokensText(e){return (e?.tokens??[]).filter(t=>t.type==='glyph').map(t=>unicode.glyphs[`${t.bank}:${t.code}`]??'').join('').replace(/\s+/g,'');}
function portraitImage(id,hd=true){id=shownIdentity(id);const p=assets.portraits.find(x=>x.id===id);if(!p)return '';const key=p.image.split('/').pop().replace('.png','');return hd?`assets/portraits-hd/${key}.webp`:p.image;}
function statusCard(id){const r=rosterRecord(id)??[],level=r[6]||1,st=growthStats(battleData,r[14]??0,level,r[9]??0),move=battleStages.movementBySubtype?.[r[8]]??0;
  const el=(tag,cls,text)=>{const e=document.createElement(tag);if(cls)e.className=cls;if(text!=null)e.textContent=text;return e;};
  const card=el('div','rs-card'),left=el('div','rs-left'),frame=el('div','rs-portrait'),face=el('img');face.src=portraitImage(id);face.alt=unitName(id);face.onerror=()=>{face.src=portraitImage(id,false);face.classList.add('pixel');};frame.append(face);left.append(frame);if(id===3)face.onclick=()=>{if(cheatOn)return;if(++cheatTaps>=20){cheatTaps=0;modal('测试作弊',h=>para(h,'要开启作弊吗？开启后点人物的经验每次加 500，点行囊里的银两每次加 1000。'),[{label:'确定',primary:true,fn:()=>{cheatOn=true;try{localStorage.setItem('shuihu.cheat','1');}catch{}closeModal();toast('作弊已开启');}}]);}};
  const eq=el('div','rs-equip');for(const [slotId,item] of [0,1,2,3,'passive'].map(k=>[k,k==='passive'?r[9]:r[10+k]])){const slot=el('button','rs-slot'+(slotId==='passive'?' rs-passive':''));if(item){const i=el('img');i.src=`assets/items/${item}.webp`;i.alt=itemName(item);slot.append(i,el('span','rs-slot-name',itemName(item)));}else slot.append(el('span','rs-slot-hint',slotId==='passive'?'饰品':'空'));slot.setAttribute('aria-label',item?itemName(item):slotId==='passive'?'饰品栏':'空装备栏');slot.onclick=()=>equipSlot(id,slotId,item);eq.append(slot);}
  const right=el('div','rs-right'),name=el('div','rs-name');name.append(el('strong',null,unitName(id)),el('small',null,jobName(r[8])));frame.append(name);   // dark strip inside the frame, like the item slots' name labels
  // Same numbers as the original status screen (attack/strategy attack, defense/strategy defense, hit, evade, critical, move).
  const rows=el('div','rs-rows');for(const [key,label,value] of [['rl-level','等级',level],['rl-hp','体力',`${st.maxHp} / ${st.maxHp}`],['rl-atk','攻击',st.attack[0]],['rl-satk','计攻',st.attack[1]],['rl-def','防御',st.defense[0]],['rl-sdef','计防',st.defense[1]],['rl-hit','命中',st.hit],['rl-eva','闪避',st.resist],['rl-crit','会心',st.critical],['rl-move','移动',move],['rl-exp','经验',`${r[7]??0} / 100`]]){
    const row=el('div','rs-row'),l=el('img');l.src=`assets/ui/buttons/${key}.webp`;l.alt=label;row.append(l,el('b',null,value));if(key==='rl-exp'){row.classList.add('rs-exp');row.style.setProperty('--exp',`${Math.min(100,r[7]??0)}%`);}if(key==='rl-exp'&&cheatOn){row.classList.add('cheat');row.onclick=()=>cheatExp(id);}rows.append(row);}
  // Class matchups from the damage matrix (ROM 0x611E, battle.js baseDamage): 12 = x1.2, 15 = x1.5, 20 = x2.0, 0 = unchanged.
  const cls=r[14]??0,m=battleData.matrix??[];
  // Group by multiplier, strongest first, each class by its first character: "刺×1.5｜風策郎弓槍隱×1.2".
  const group=pairs=>{const by={};for(const [c,v] of pairs)(by[v]??=[]).push(CLASS_NAMES[c]);return Object.keys(by).map(Number).sort((x,y)=>y-x).map(v=>`${by[v].map(n=>n[0]).join('')}×${(v/10).toFixed(1).replace(/\.0$/,'')}`).join('｜')||'无';};
  const strong=group((m[cls]??[]).map((v,j)=>[j,v]).filter(([,v])=>v>10)),weak=group(m.map((row,i)=>[i,row[cls]]).filter(([,v])=>v>10));
  const match=el('div','rs-match');const line=(tag,text)=>{const d=el('div','rs-match-line');d.append(el('span','rs-seal',tag),el('span',null,text));return d;};match.append(line('克制',strong),line('被克',weak));left.append(match);requestAnimationFrame(()=>{for(const sp of match.querySelectorAll('.rs-match-line span:last-child')){let f=9.5;while(sp.scrollWidth>sp.clientWidth+1&&f>7){f-=.5;sp.style.fontSize=f+'px';}}});   // shrink a long line to fit rather than wrap
  const items=el('div','rs-equip rs-items');for(let k=0;k<4;k++){const item=r[2+k],slot=el('button','rs-slot rs-item');if(item){const i=el('img');i.src=`assets/items/${item}.webp`;i.alt=itemName(item);slot.append(i,el('span','rs-slot-name',itemName(item)));}else slot.append(el('span','rs-slot-hint','道具'));slot.setAttribute('aria-label',item?itemName(item):'空道具栏');slot.onclick=()=>itemSlot(id,k,item);items.append(slot);}
  right.append(rows,eq,items);card.append(left,right);return card;}
// Items carried on the person (persistent record bytes 2-5, battle record bytes 8-11): only these can be used in battle
// (the 道具 command), and one is used up each time; medicines and the like (128+) go here from the bag.
function itemGrid(h,entries,selected,onSelect){const grid=document.createElement('div');grid.className='bag-grid';   // the icon area scrolls on its own when there are many items; the detail panel stays in view
const panel=document.createElement('div');panel.className='bag-detail';
  const show=()=>{for(const b of grid.children)b.setAttribute('aria-pressed',String(b.dataset.id===String(selected)));const name=document.createElement('strong');name.textContent=itemName(selected);const d=document.createElement('p');d.textContent=itemText[Number(selected)]??'';panel.replaceChildren(name,d,statChips(selected));onSelect?.(selected);};
  for(const [id,n]of entries){const b=button('',()=>{selected=id;show();},'slot');b.dataset.id=id;b.setAttribute('aria-label',`${itemName(id)} × ${n}`);const i=document.createElement('img');i.src=`assets/items/${Number(id)}.webp`;i.alt='';const nm=document.createElement('span');nm.className='slot-name';nm.textContent=itemName(id);b.append(i,nm);if(n>1){const c=document.createElement('b');c.textContent=n;b.append(c);}grid.append(b);}
  dragScroll(grid);h.append(grid,panel);if(selected!=null)show();}
// Mouse/pen drag scrolls a list like a finger does (touch already scrolls natively); a drag never counts as a tap.
function dragScroll(el){let d=null;el.addEventListener('pointerdown',e=>{if(e.pointerType==='touch')return;d={y:e.clientY,top:el.scrollTop,moved:false,id:e.pointerId};});
  el.addEventListener('pointermove',e=>{if(!d||e.pointerId!==d.id)return;const dy=e.clientY-d.y;if(!d.moved&&Math.abs(dy)>5){d.moved=true;el.setPointerCapture(d.id);}if(d.moved)el.scrollTop=d.top-dy;});
  const end=()=>{if(d?.moved)el.addEventListener('click',ev=>{ev.stopPropagation();ev.preventDefault();},{capture:true,once:true});d=null;};
  el.addEventListener('pointerup',end);el.addEventListener('pointercancel',()=>{d=null;});}
function pickItem(title,entries,verb,onPick){let chosen=entries[0][0];modal(title,h=>itemGrid(h,entries,chosen,id=>{chosen=id;}),[{label:verb,primary:true,fn:()=>onPick(chosen)}]);}
function setItemSlot(id,k,item){if(equipLocked())return;const r=editableRecord(id),inv=vm.state.inventory,old=r[2+k];if(old)inv[old]=(inv[old]??0)+1;if(item){inv[item]-=1;if(inv[item]<=0)delete inv[item];}r[2+k]=item?Number(item):0;save();}
function chooseItem(id,k){const r=rosterRecord(id),list=Object.entries(vm.state.inventory).filter(([item,n])=>n>0&&Number(item)>=128&&canUse(r?.[8],item));if(!list.length)return toast(`行囊里没有${unitName(id)}能带的道具`);
  pickItem('选择道具',list,'确定',item=>{setItemSlot(id,k,item);closeModal();renderModal();toast(`带上 ${itemName(item)}`);});}
function itemSlot(id,k,item){if(equipLocked())return;if(!item)return chooseItem(id,k);modal(itemName(item),h=>{const box=document.createElement('div');box.className='item-detail';box.append(itemIcon(item));const t=document.createElement('p');t.textContent=itemText[Number(item)]??'';box.append(t);h.append(box);},
  [{label:'更换',primary:true,fn:()=>chooseItem(id,k)},{label:'卸下',fn:()=>{setItemSlot(id,k,0);closeModal();renderModal();toast(`放回 ${itemName(item)}`);}}]);}
// Generated button art (assets/ui/buttons, text painted in); the alt/aria text keeps it readable for screen readers.
// A button in the art buttons' frame with live text on it (bt-blank is bt-end with its painted words removed).
function textButton(label,fn,frame='bt-blank'){const b=button('',fn,'art-btn text-btn');const i=document.createElement('img');i.src=`assets/ui/buttons/${frame}.webp`;i.alt='';const t=document.createElement('span');t.textContent=label;b.append(i,t);b.setAttribute('aria-label',label);return b;}
// 戰鬥目的 (the battle system menu's first entry): this stage's victory and defeat conditions, as the cartridge words them
// (objectives.json from ROM 0x1A73C), over a dimmed field; any tap closes it.
function showObjective(){const o=objectives?.[session?.stage??vm.state.stage];if(!o)return;document.querySelector('.objective')?.remove();
  const w=document.createElement('div');w.className='objective';w.innerHTML='<div class="obj-card"><h3>战斗目的</h3><div class="obj-row win"><b>胜利条件</b><span></span></div><div class="obj-row lose"><b>失败条件</b><span></span></div><small>点任意处关闭</small></div>';
  w.querySelector('.win span').textContent=o.victory;w.querySelector('.lose span').textContent=o.defeat.join('、');w.addEventListener('pointerup',()=>w.remove());$('app').append(w);}
function artButton(key,label,fn,pressed){const b=button('',fn,'art-btn');const i=document.createElement('img');i.src=`assets/ui/buttons/${key}${pressed?'-on':''}.webp`;i.alt=label;b.append(i);b.setAttribute('aria-label',label);if(pressed!=null)b.setAttribute('aria-pressed',String(!!pressed));return b;}
const FOOTER_ART={'开始战斗':'bt-start-on','确认结束':'bt-end','取消 / 返回':'act-cancel','关闭':'act-cancel','取消':'act-cancel','购买':'act-buy-on','出售一件':'act-sell-on','确定':'act-ok-on','开始':'act-ok-on'};
function footerButton(label,fn,primary){return FOOTER_ART[label]?artButton(FOOTER_ART[label],label,fn):button(label,fn,primary?'primary':'');}
function heading(host,title,note){const box=document.createElement('div');box.className='plaque';const t=document.createElement('strong');t.textContent=title;box.append(t);if(note){const n=document.createElement('small');n.textContent=note;box.append(n);}host.append(box);return box;}
function itemName(id){const entry=assets.item_skill_names.find(x=>x.id===Number(id));return (entry?.tokens??[]).filter(t=>t.type==='glyph').map(t=>unicode.glyphs[`${t.bank}:${t.code}`]??'').join('').trim()||`物品 #${id}`;}
// A hidden-item cell becomes a plain wall (0x50) once its reward is taken; say so instead of "cannot pass".
function hiddenAt(x,y){return (storyData.hiddenItems??[]).some(i=>parseInt(i.mapId,16)===vm.state.mapId&&i.cellIndex===y*map.widthTiles+x);}
// Strolling villagers, as the ROM moves them (0x7768, every frame): an NPC whose movement byte is a direction 0-3 walks
// 1 px per frame that way inside its own box (record bytes 8-15: min x, min y, max x, max y in pixels). On each whole
// cell it stops if the next cell is blocked (logic code above 0x4F, 0x7842), holds another NPC (0x7982) or the player
// (0x7A32), or the box edge is reached; a stopped NPC picks a random new direction only on every 32nd frame (0x789E),
// so they walk, pause and turn. 255 stands still; 254 also does not turn to face the player when spoken to (0x18478).
let strollFrame=0;
const STROLL_STEP=[[0,-1,0],[0,1,4],[-1,0,8],[1,0,12]];   // dx, dy, walking pose per direction 0 up, 1 down, 2 left, 3 right
setInterval(()=>{if(!map||battle||vm?.running||dialogue||modalStack.length||document.hidden)return;strollFrame++;const W=map.widthTiles,H=map.heightTiles,p=player();
  for(const a of actors){if(!a.active||!(a.slot>=8)||!a.raw||a.raw.length<16)continue;if(a.strollDir===undefined)a.strollDir=a.movementByte<=3?a.movementByte:null;if(a.strollDir==null||(a.moving&&!a.strolling))continue;
    const word=k=>(a.raw[k]<<8)|a.raw[k+1],box={minX:word(8),minY:word(10),maxX:word(12),maxY:word(14)},[dx,dy,pose]=STROLL_STEP[a.strollDir],aligned=a.x%32===0&&a.y%32===0;
    let blocked=(dy<0&&a.y<=box.minY)||(dy>0&&a.y>=box.maxY)||(dx<0&&a.x<=box.minX)||(dx>0&&a.x>=box.maxX);
    if(!blocked&&aligned){const nx=a.x/32+dx,ny=a.y/32+dy;blocked=nx<0||ny<0||nx>=W||ny>=H||collision[ny*W+nx]>0x4f||
      actors.some(b=>b!==a&&b.active&&Math.abs(b.x-nx*32)<32&&Math.abs(b.y-ny*32)<32)||(p&&Math.abs(p.x-nx*32)<32&&Math.abs(p.y-ny*32)<32)||route.some(r=>r.x===nx&&r.y===ny);}
    if(!blocked){a.x+=dx;a.y+=dy;a.animationState=pose;a.moving=a.strolling=true;continue;}
    a.moving=a.strolling=false;if(aligned&&strollFrame%32===0)a.strollDir=Math.floor(Math.random()*4);}},1000/60);
function collectedHidden(x,y){const item=(storyData.hiddenItems??[]).find(i=>parseInt(i.mapId,16)===vm.state.mapId&&i.cellIndex===y*map.widthTiles+x);return !!item&&!!((vm.state.pickupFlags?.[item.group]??0)&(1<<item.pickupFlag.bit));}
function nameCanvas(tokens){const span=document.createElement('span');span.className='game-name';span.textContent=(tokens??[]).filter(t=>t.type==='glyph').map(t=>unicode.glyphs[`${t.bank}:${t.code}`]??'□').join('');return span;}
// Centred reward card (item icon, or silver for gold); the story waits until it closes (timeout or tap).
function rewardCard(r){return new Promise(resolve=>{const card=document.createElement('div');card.className='reward-card';card.setAttribute('role','status');const label=document.createElement('small');label.textContent='获得';const name=document.createElement('strong');if(r.gold){const coin=document.createElement('img');coin.className='reward-coin';coin.src='assets/ui/silver-pile.webp';coin.alt='';card.append(coin);name.textContent=`${r.gold} 两银子`;}else{card.append(itemIcon(r.item));name.textContent=itemName(r.item)+(r.count>1?` ×${r.count}`:'');const d=itemText[Number(r.item)];if(d){const p=document.createElement('p');p.textContent=d;card.append(label,name,p);}}if(!card.contains(name))card.append(label,name);$('app').append(card);let done=false;const close=()=>{if(done)return;done=true;card.classList.add('leaving');setTimeout(()=>{card.remove();resolve();},220);};card.addEventListener('pointerup',close);setTimeout(close,2200);});}
// Item picture on the green medallion cut from the save/load board.
function itemIcon(id){const badge=document.createElement('span');badge.className='item-icon';const icon=document.createElement('img');icon.alt='';icon.loading='lazy';icon.src=`assets/items/${Number(id)}.webp`;icon.onerror=()=>icon.remove();badge.append(icon);return badge;}
function namedRow(host,id,count,fn){const row=button('',fn,'row item-row');const entry=assets.item_skill_names.find(x=>x.id===Number(id));const text=document.createElement('span');text.className='item-text';text.append(nameCanvas(entry?.tokens));if(itemText[Number(id)]){const d=document.createElement('small');d.className='item-desc';d.textContent=itemText[Number(id)];text.append(d);}if(itemStats(id).length)text.append(statChips(id));row.append(itemIcon(id),text);const span=document.createElement('span');span.textContent=count;row.append(span);host.append(row);}
// Item numbers from the ROM item table (0x28E54) as battle.js uses them: power is added to attack (effect 0) or
// strategy attack (effect 1), hit_bonus to hit; healing items use battle.json healingAmounts; uses 99 = never wears out.
// Passive slot items (record byte 9). 112-118: effect_type 0-6 raises one stat by power% (=10, applied as x11/10 after
// level growth, battle.js growthStats). 119/120 widen the passable terrain mask in the original's move code (0x4EE2:
// 0x77 -> mask 0x6F, 0x78 -> 0x5F); 121 wards off the AI's curses (0xD750), 122 gives a step after a blow (0x4A12),
// 123 bursts on its carrier's death (0x4570).
const PASSIVE_STAT=['攻击','防御','计攻','计防','命中','闪避','体力上限'];
const PASSIVE_TEXT={119:['特效','可越过险地（如駕霧人）'],120:['特效','可涉水过河（如漁人）'],121:['特效','敌人的诅咒对其无效'],122:['特效','攻击后还可再移动一次'],123:['特效','阵亡时爆散，伤及周围三格']};
// What each carried item does, from the ROM's item switch (0x15BAA): the four status effects are 混乱 (cannot act
// normally, always hit), 中毒, 虚弱 (攻击减半) and 破甲 (防御减半); curses and consumables last 3 turns.
const STATUS_NAMES=['混乱','中毒','虚弱','破甲'];
function consumableStats(id,r,heal){const e=r.effect_type,out=[];
  if(e===0)out.push(['对象','我方'],['效果',heal?`回复体力 ${heal}`:'体力全满']);
  else if(e>=1&&e<=4)out.push(['对象','我方'],['效果',`解除${STATUS_NAMES[e-1]}`]);
  else if(e===6)out.push(['对象','敌方'],['效果','虚弱：攻击减半'],['持续','3 回合'],['命中','必中']);
  else if(e===7)out.push(['对象','敌方'],['效果','破甲：防御减半'],['持续','3 回合'],['命中','必中']);
  else if(e===8)out.push(['对象','敌方'],['伤害','50 − 对方计防'],['命中','必中']);
  out.push(['类别','消耗']);return out;}
function itemStats(id){id=Number(id);const r=battleData?.skills?.[id-1],out=[],heal=battleData?.healingAmounts?.[id];if(!r)return out;
  if(id>=128)return consumableStats(id,r,heal);
  if(id>=80&&id<=83)return [['对象','敌方'],['效果',`${STATUS_NAMES[r.effect_type-3]}${r.effect_type===5?'：攻击减半':r.effect_type===6?'：防御减半':''}`],['持续','3 回合'],['命中',r.hit_bonus],['次数',battleStages?.itemUses?.[id]??r.initial_uses]];
  if(id>=112&&id<=118)return [['装备于','饰品栏'],[PASSIVE_STAT[r.effect_type],`+${r.power_or_quantity}%`]];if(PASSIVE_TEXT[id])return [['装备于','饰品栏'],PASSIVE_TEXT[id]];
if(heal)out.push(['回复体力',heal]);else if(id<112&&r.power_or_quantity>0&&r.effect_type<=1)out.push([r.effect_type===0?'攻击':'计策',r.power_or_quantity]);
if(id<112&&r.hit_bonus>0&&r.effect_type<=1)out.push(['命中',r.hit_bonus]);
if(id<112){const uses=battleStages?.itemUses?.[id]??r.initial_uses;if(uses===99)out.push(['次数','无限']);else if(uses>0)out.push(['次数',uses]);}else if(heal||id>=128)out.push(['类别','消耗']);
  // Byte 2 of the item record: 2 = the attack is made twice (ROM 0x49E4). Reach is the user's, by job (rangePatterns).
  if(id<112&&r.range_candidate===2)out.push(['连击','两次']);
  const kind=itemKind(id),who=Array.from({length:30},(_,i)=>i+1).filter(st=>canUse(st,id)).map(jobName);
  if(id<112&&kind){out.unshift(['类型',kind]);if(who.length)out.push(['适用',who.join('·')]);out.push(['范围','依职业']);}else if(id>=128&&who.length&&who.length<30)out.push(['适用',who.join('·')]);
  if(id>=128)out.push(['携带','人物道具栏']);
  return out;}
function statChips(id){const box=document.createElement('span');box.className='item-stats';for(const [k,v] of itemStats(id)){const c=document.createElement('span');c.className='item-stat';const kk=document.createElement('i');kk.textContent=k;const vv=document.createElement('b');vv.textContent=v;c.append(kk,vv);box.append(c);}return box;}
// Item detail: large icon, name, flavour text and its numbers.
function itemDetail(id){modal(itemName(id),h=>{const box=document.createElement('div');box.className='item-detail';const icon=itemIcon(id);box.append(icon);const t=document.createElement('p');t.textContent=itemText[Number(id)]??'这件物品的来历尚不清楚。';box.append(t,statChips(id));h.append(box);para(h,'物品效果正在逐项核对，当前不能在地图中使用。').className='note';});}
function showPanel(kind){if(kind==='menu'){modal('江湖菜单',h=>{const grid=document.createElement('div');grid.className='art-menu';for(const [label,k,key] of [['人物','party','menu-party'],['行囊','bag','menu-bag'],['保存与读取','save','menu-save'],['游戏设置','settings','title-settings'],['操作说明','help','menu-help']])grid.append(artButton(key,label,()=>showPanel(k)));grid.append(artButton('menu-title','返回标题',()=>{if(vm.running||busy||battle)return toast('请先完成当前剧情或战斗');closeModal(true);$('titleScreen').hidden=false;}));h.append(grid);});}
else if(kind==='settings'){modal('游戏设置',h=>{const line=(labelKey,label,options)=>{const row=document.createElement('div');row.className='opt-line';const l=document.createElement('img');l.className='opt-label';l.src=`assets/ui/buttons/${labelKey}.webp`;l.alt=label;const g=document.createElement('div');g.className='opt-group';for(const o of options)g.append(artButton(o.key,o.label,o.fn,o.on));row.append(l,g);h.append(row);};
  line('label-art','画面风格',ART_STYLES.map(st=>({key:{original:'opt-original',ghibli:'opt-ghibli',hd2d:'opt-hd2d'}[st.id],label:st.name,on:art?.style===st.id,fn:async()=>{await art.select(st.id,map);renderModal();toast(art.active?.fallback?'这张地图的高清版还在校验，暂用原版':'画面已切换');}})));
  line('label-orientation','画面方向',[['landscape','横屏','opt-landscape'],['portrait','竖屏','opt-portrait'],['auto','自动','opt-auto']].map(([mode,label,key])=>({key,label,on:orientationMode===mode,fn:()=>{setOrientation(mode);renderModal();}})));
  line('label-volume','音乐音量',[0,1,2,3].map(v=>({key:`opt-vol${v}`,label:['关','低','中','高'][v],on:(soundEnabled?musicLevel:0)===v,fn:()=>{setVolume(v);renderModal();}})));
  line('label-guide','引导提示',[[true,'开启','opt-enable'],[false,'关闭','opt-disable']].map(([on,label,key])=>({key,label,on:guideOn===on,fn:()=>{guideOn=on;try{localStorage.setItem('shuihu.guide',on?'1':'0');}catch{}renderModal();}})));
  line('label-control','操作方式',[['tap','点按移动','opt-tap'],['joystick','方向摇杆','opt-joystick'],['dpad','方向按键','opt-dpad']].map(([mode,label,key])=>({key,label,on:controlMode===mode,fn:()=>{setControlMode(mode);renderModal();}})));});}
else if(kind==='help'){modal('触摸操作',h=>{para(h,'点击可通行的地面，人物会自动绕开障碍。点击人物或门口，会走近并交互。再次点地面可更换路线。');para(h,'方向键操作：键盘方向键或 WASD 移动，Enter / 空格确认，Esc 取消；手柄十字键或左摇杆移动，A 确认，B 取消，Start 打开菜单；电视遥控器的方向键和确定键同样可用。菜单里用方向键移动选中框，战斗中用方向键移动光标、确认键选格。');para(h,'对话时，点击屏幕任意位置继续。商店、人物、行囊与存档界面，都有返回和关闭按钮。选择技能或目标时点“取消选择”，不消耗行动。');para(h,'本版是独立 HTML5 重构，正在恢复与核对原版剧情。战斗 AI、部分技能范围与状态时机仍属重写规则；不代表已完成全流程复刻。');});}
else if(kind==='bag'){modal('行囊',h=>{const purse=document.createElement('div');purse.className='purse-line';purse.innerHTML='<img class="coin" src="assets/ui/silver-ingot.webp" alt="">';purse.append(`银两 ${vm.state.gold}`);if(cheatOn){purse.classList.add('cheat');purse.onclick=()=>{vm.state.gold+=1000;save();renderModal();toast('银两 +1000');};}h.append(purse);const entries=Object.entries(vm.state.inventory).filter(([,n])=>n>0);if(!entries.length){para(h,'行囊暂时为空。');return;}
  // Icon grid (slots from the inventory board); the panel under it describes the tapped item.
  itemGrid(h,entries,bagSelection&&vm.state.inventory[bagSelection]>0?bagSelection:entries[0][0],id=>{bagSelection=id;});});}
else if(kind==='party'){modal('人物状态',h=>{const party=[...new Set(vm.state.party)];if(!party.length){para(h,'暂无同行人物。');return;}if(!party.includes(statusSelection))statusSelection=party[0];
  if(party.length>1){const tabs=document.createElement('div');tabs.className='status-tabs';tabs.style.setProperty('--cols',String(Math.min(party.length,$('app').clientWidth<600?10:20)));for(const id of party){const b=button('',()=>{statusSelection=id;renderModal();},'status-tab');b.setAttribute('aria-pressed',String(id===statusSelection));b.setAttribute('aria-label',unitName(id));const i=document.createElement('img');i.src=portraitImage(id);i.onerror=()=>{i.onerror=null;i.src=portraitImage(id,false);i.classList.add('pixel');};i.alt='';b.append(i);tabs.append(b);}h.append(tabs);}
  h.append(statusCard(statusSelection));});}
else if(kind==='save'){modal('保存与读取',h=>{const locked=vm.running||busy||(!!session&&!battleSavable());if(locked)para(h,session?'敌方行动、战场事件或动画进行中，稍后即可保存或读取。':'剧情或移动进行中，暂不能保存或读取。').className='note';for(const slot of ['auto',1,2,3]){const data=readSave(slot),row=document.createElement('div');row.className='row save-row';const t=document.createElement('span');t.className='save-text';const n=document.createElement('strong');n.textContent=slot==='auto'?'自动存档':`存档 ${'一二三'[slot-1]}`;const w=document.createElement('small');w.textContent=data?new Date(data.date).toLocaleString():'空';t.append(n,w);row.append(t);
  if(slot!=='auto'){const b=artButton('btn-save','保存',()=>{save(slot);renderModal();toast('已保存');});b.disabled=locked;row.append(b);}const b=artButton('btn-load','读取',()=>{if(data){closeModal(true);loadSave(data);}});b.disabled=!data||locked;row.append(b);h.append(row);}});}}
$('homeButton').onclick=()=>showPanel('menu');document.querySelectorAll('[data-panel]').forEach(b=>b.onclick=()=>{setDock(false);showPanel(b.dataset.panel);});
// Landscape dock: the toolbar floats folded away at the bottom; the small handle opens and closes it (as the macOS /
// iPadOS dock), and opening a panel folds it again, so nothing stands over the map's side exits.
function setDock(open){document.documentElement.style.setProperty('--dock-h',`${$('toolbar').offsetHeight||56}px`);document.documentElement.classList.toggle('dock-open',open);$('dockHandle').setAttribute('aria-expanded',String(open));$('dockHandle').setAttribute('aria-label',open?'收起工具栏':'展开工具栏');}
$('dockHandle').onclick=()=>setDock(!document.documentElement.classList.contains('dock-open'));canvas.addEventListener('pointerdown',()=>setDock(false));$('titleHelp').onclick=()=>showPanel('settings');
function readSave(slot){try{return JSON.parse(localStorage.getItem('shuihu.native.v1.'+slot));}catch{return null;}}
function save(slot='auto'){if(vm.running||busy||pendingBattle||(session&&!battleSavable()))return;try{localStorage.setItem('shuihu.native.v1.'+slot,JSON.stringify({version:1,date:Date.now(),state:vm.save(),actors,battle:session?{...session.snapshot(),sceneMusic}:undefined}));if(slot!=='auto')toast('已保存');$('continueGame').hidden=false;}catch{toast('保存失败，浏览器存储不可用或空间不足');}}
async function loadSave(data){try{if(data.version!==1)throw Error('存档版本不兼容');closeBattle();vm.load(data.state);actors=structuredClone(data.actors);vm.setEntities(actors);await changeMap(vm.state.mapId,null,{entities:actors,patches:vm.collisionPatches()});$('titleScreen').hidden=true;if(data.battle)resumeBattle(data.battle);else placeMusic(map.id);}catch(e){toast(e.message);}}
// Battles can be saved and loaded on our turn, as with the cartridge's 儲存 / 載入 in its battle menu: whenever our side is
// to act and no event, animation or level-up card is under way.
function battleSavable(){return !!session&&!session.busy&&!session.ended&&session.activeEvent==null&&!!battle&&battle.activeTeam==='player'&&!vm.running&&performance.now()>=fx.until&&!levelUpShowing&&!levelUps.length;}
function closeBattle(){if(session){session.ended=true;session.generation++;}session=null;battle=null;pendingBattle=null;selectedSkill=null;moveMode=false;attackMenuOpen=false;itemMenuOpen=false;$('battleHud').hidden=true;if($('unitMenu'))$('unitMenu').hidden=true;document.querySelector('.objective')?.remove();fx.moves.clear();fx.bursts=[];fx.deaths=[];fx.pops=[];updateControls();}
function resumeBattle(snap){const s=createSession({stage:snap.stage,mapId:snap.battleMap.mapId,width:snap.battleMap.width,height:snap.battleMap.height});openSession(s,snap.stage);if(snap.sceneMusic!=null)sceneMusic=snap.sceneMusic;bannerKey=`${snap.engine.turn}:player`;s.resume(snap);}
// Each of our turns is also kept in the auto save once its opening has settled.
function autoSaveBattle(tries=0){if(!session)return;if(battleSavable())save('auto');else if(tries<60)setTimeout(()=>autoSaveBattle(tries+1),300);}
async function changeMap(id,spawnId,context={}){scriptCam=null;stageCam=null;if(!vm?.running)screenFade={from:0,to:0,t0:0,dur:1};{const sp=spawnId!=null&&vm?.running?storyData.spawns.find(x=>x.id===hex(spawnId)):null;
  // During a script the screen opens where the spawn record puts it (camera_x/y = top-left cell of the 320x224 screen),
  // not on the player: cutscenes frame the people talking, as on the cartridge.
  if(sp&&sp.camera_x!=null)scriptCam={x:sp.camera_x*32+160-16,y:sp.camera_y*32+112-16};}const next=assets.maps.find(m=>m.id===hex(id));if(!next)throw Error('地图尚未恢复：'+hex(id));if(session&&session.activeEvent!=null)storyView=true;
  // Load the next map's chosen art before switching, so the original picture never flashes before the HD one.
  if(art&&art.style!=='original'){const v=resolveArt(next,art.style,artManifest);await ready(v.image).catch(()=>{});await ready(next.image).catch(()=>{});}
  route=[];map=next;collision=[...map.collision];for(const [x,y] of COLLISION_CLOSED[map.id]??[])collision[y*map.widthTiles+x]=0x70;actors=context.entities??actors;const spawn=storyData.spawns.find(s=>s.id===hex(spawnId));if(spawnId!=null&&spawn&&actors[0])Object.assign(actors[0],{x:spawn.player_x,y:spawn.player_y,animationState:spawn.animation,active:true});for(const p of context.patches??[])collision[p.index]=p.value;vm.state.mapId=Number(id);vm.setEntities(actors);actors=vm.state.entities;await ready(map.image);await Promise.all([art?.refresh(map),foreground?.refresh(map)]);$('place').textContent=id===0x106?'晁家 · 内室':id===0x100?'晁家庄':'江湖行旅';updateControls();if(battle)updateBattle();}
function player(){return actors.find(a=>a.slot===0);}
function passable(x,y){return x>=0&&y>=0&&x<map.widthTiles&&y<map.heightTiles&&collision[y*map.widthTiles+x]<0x50&&!actors.some(a=>a.active&&a.slot>=8&&a.slot<=15&&x*32<a.x+32&&x*32+32>a.x&&y*32<a.y+32&&y*32+32>a.y);}
async function runEvent(id){if(vm.running)return;route=[];try{await vm.start(vm.state.mapId>>8,id);actors=vm.state.entities;await startPendingBattle();save();}catch(e){storyError(e);}}
function storyError(e){modal('剧情恢复待核对',h=>{para(h,'此处剧情尚未通过原版对照，已暂停推进。可以关闭此窗口查看当前地图，或在菜单读取此前存档。');para(h,e.message);});}
// Talking: the NPC turns to face the player and the player faces the NPC (states 0 up, 4 down, 8 left, 12 right);
// NPCs that do not wander turn back to their original pose afterwards.
function faceEachOther(actor){const p=player();if(!p)return;const dx=p.x-actor.x,dy=p.y-actor.y;const toward=(x,y)=>Math.abs(x)>Math.abs(y)?(x>0?12:8):(y>0?4:0);if(actor.movementByte!==254)actor.animationState=toward(dx,dy);p.animationState=toward(-dx,-dy);}
async function talk(actor){busy=true;const pose=actor.animationState;faceEachOther(actor);try{const variants=npcs.identities.find(i=>i.identity===actor.byte7)?.variants??[];const key=variants[vm.state.counters[actor.byte7]??0]??variants[0];const d=npcs.dialogues.find(d=>d.id===key);if(d){await showDialogue(d,actor.characterId);busy=false;if(d.scriptId!=null)await runEvent(d.scriptId);}else toast('这位人物的对白暂未恢复');}finally{busy=false;if(actor.movementByte!==255&&!actor.moving)actor.animationState=pose;}}
async function walkPath(path,after){if(!path){toast('这里暂时无法到达');return;}route=path;walking=true;busy=true;const generation=++walkPath.generation;try{while(route.length&&generation===walkPath.generation){const p=route.shift();await moveActor(0,{x:p.x*32,y:p.y*32});const event=collision[p.y*map.widthTiles+p.x];if(event>0&&event<0x50){route=[];busy=false;await runEvent(event);return;}}if(generation===walkPath.generation){busy=false;await after?.();}}finally{if(generation===walkPath.generation){walking=false;busy=false;}}}walkPath.generation=0;
// Screen fades (script opcodes 0x10 / 0x11): the picture goes to black and back between scenes, so the people a scene
// walks away are not left standing in view when the next one starts.
let screenFade={from:0,to:0,t0:0,dur:1};
function fadeLevel(t){const f=Math.min(1,Math.max(0,(t-screenFade.t0)/screenFade.dur));return screenFade.from+(screenFade.to-screenFade.from)*f;}
function fadeScreen(to,dur=420){const now=performance.now();screenFade={from:fadeLevel(now),to,t0:now,dur};return new Promise(r=>setTimeout(r,dur));}
function drawScreenFade(t){if(t<screenFlash){ctx.save();ctx.setTransform(1,0,0,1,0,0);ctx.fillStyle='#fff';ctx.fillRect(0,0,canvas.width,canvas.height);ctx.restore();}const k=fadeLevel(t);if(k<=0)return;ctx.save();ctx.setTransform(1,0,0,1,0,0);ctx.globalAlpha=k;ctx.fillStyle='#000';ctx.fillRect(0,0,canvas.width,canvas.height);ctx.restore();}
// People a script takes off the map (0x24, or 0x23 with no character) fade out briefly instead of blinking away.
let vanishSeen=new Set(),vanishMapId=null,vanishFrame=0,vanishing=[];
const VANISH_MS=350,VANISH_DIRS={0:[0,-1],4:[0,1],8:[-1,0],12:[1,0]};
function trackVanish(shown,t){const fresh=map.id!==vanishMapId||t-vanishFrame>250;vanishMapId=map.id;vanishFrame=t;
  if(fresh)vanishing=[];else for(const a of vanishSeen)if(!a.active&&actors.includes(a)&&!vanishing.some(v=>v.a===a))vanishing.push({a,t0:t,x:a.x,y:a.y,walk:false});
  vanishing=vanishing.filter(v=>!v.a.active&&t<v.t0+VANISH_MS);vanishSeen=new Set(shown);}
function vanishGhosts(t){return vanishing.map(v=>{const f=Math.min(1,(t-v.t0)/VANISH_MS),[dx,dy]=v.walk?VANISH_DIRS[(v.a.animationState??4)&~3]??[0,0]:[0,0];return {...v.a,x:v.x+dx*72*f,y:v.y+dy*72*f,moving:v.walk,fade:1-f};});}
// Cutscenes are staged for the cartridge's 320x224 screen: people "leave" by walking past its edge (often to a cell past
// the map's own edge, beyond a doorway) and the script carries on. Our view shows more of the map, so during a script
// someone a script walks to a spot outside that screen (or off the map) fades by the share of them still inside it while
// crossing the edge, and is gone once wholly past it. Only leaving is treated so: people walking in, or standing outside
// that screen, are always shown. The screen is the script camera (spawn camera / 0x1C / 0x33) or, without one, the
// player-centred screen clamped to the map, taken when the script starts and moved only by the player's own walks.
let stageCam=null;   // the cartridge's screen while a script runs without a camera of its own: where the player stood, held still
function originalScreen(){const W=map.widthTiles*32,H=map.heightTiles*32;
  if(scriptCam)return {x:scriptCam.x+16-160,y:scriptCam.y+16-112,w:320,h:224};
  if(!stageCam){const p=actors.find(a=>a.slot===0)??{x:0,y:0};stageCam={x:Math.max(0,Math.min(W-320,p.x+16-160)),y:Math.max(0,Math.min(H-224,p.y+16-112)),w:320,h:224};}
  return stageCam;}
function offstageAlpha(a,stage){const part=(p,lo,hi)=>Math.max(0,Math.min(1,(Math.min(p+32,hi)-Math.max(p,lo))/32));   // share of the 32 px figure inside [lo, hi]
  let k=part(a.x,0,map.widthTiles*32)*part(a.y,0,map.heightTiles*32);if(stage)k*=part(a.x,stage.x,stage.x+stage.w)*part(a.y,stage.y,stage.y+stage.h);return k;}
// Scripted and walking moves go along the grid one axis at a time (x first, then y, as the original's script moves do),
// never diagonally through furniture.
async function moveActor(slot,p){if(p.follow){scriptCam=null;stageCam=null;}   // only the player's own walk (0x1B/0x20) takes the screen along
const a=actors.find(x=>x.slot===slot);if(!a)return;const tx=p.x??a.x,ty=p.y??a.y;
  if(tx!==a.x&&ty!==a.y){const first=p.pathOrder==='y-then-x'?{...p,x:a.x,y:ty}:{...p,x:tx,y:a.y};await moveStraight(slot,first);}
  return moveStraight(slot,p);}
async function moveStraight(slot,p){const a=actors.find(x=>x.slot===slot);if(!a)return;const sx=a.x,sy=a.y,tx=p.x??sx,ty=p.y??sy;// While walking, face the way of travel (script moves pass a start pose that made people walk backwards out of rooms);
// a script pose only applies to turns on the spot.
const travel=Math.abs(tx-sx)>Math.abs(ty-sy)?tx>sx?12:8:ty>sy?4:0;{const st=vm?.running?originalScreen():null;a.leaveTo=st&&offstageAlpha({x:tx,y:ty},st)===0?{x:tx,y:ty}:null;}Object.assign(a,{animationState:tx===sx&&ty===sy?p.animationState??a.animationState:travel});if(tx===sx&&ty===sy)return;const pace=vm?.running?(vm.state.animationSpeed||2):2,start=performance.now(),duration=Math.hypot(tx-sx,ty-sy)/(pace*60)*1000;   /* FFE10D px per frame: 2 while exploring, scripts set 1 with 0x1E for a slow walk */
a.moving=true;await new Promise(resolve=>{function tick(t){const f=Math.min(1,(t-start)/duration);a.x=sx+(tx-sx)*f;a.y=sy+(ty-sy)*f;if(f<1)requestAnimationFrame(tick);else{a.moving=false;a.movedAt=performance.now();resolve();}}requestAnimationFrame(tick);});}
// Battle camera: centred on our units at the start, follows the selected unit, and can be dragged to look around.
// Mouse cursor over the map: walk where the ground is passable, a hand over things to investigate (cells 0x80-0xAF,
// including uncollected hidden items), a speech bubble over people, the plain arrow elsewhere.
canvas.addEventListener('pointermove',e=>{if(e.pointerType!=='mouse'||!map)return;const q=localPoint(e,canvas),x=Math.floor((q.x*view.width/canvas.clientWidth+camera.x)/32),y=Math.floor((q.y*view.height/canvas.clientHeight+camera.y)/32);let kind='';
  if(x>=0&&y>=0&&x<map.widthTiles&&y<map.heightTiles){if(battle){kind=battle.alive().some(u=>u.x===x&&u.y===y)||battle.selectedId!=null&&battle.reachable(battle.selectedId).some(r=>r.x===x&&r.y===y)?'walk':'';}   // battle: arrow only, no talk bubble
  else{const v=collision[y*map.widthTiles+x];kind=actors.some(a=>a.active&&a.slot!==0&&x*32<a.x+32&&x*32+32>a.x&&y*32<a.y+32&&y*32+32>a.y)?'talk':v>=0x80&&v<=0xaf&&!collectedHidden(x,y)?'grab':v<0x50?'walk':'';}}
  canvas.dataset.cursor=kind;});
canvas.addEventListener('pointerleave',()=>{canvas.dataset.cursor='';});
const battleView={x:null,y:null,dragged:false,drag:null};
// Battle scripts (e.g. the victory event) can move the story to another map before the battle formally ends (0x27);
// there the normal exploration view with its people is shown, not the battle units.
// Once a battle script itself changes map (victory/defeat cut-scenes), the story view stays until the battle ends.
// Cells the remake closes although the ROM lets the player walk there, because the redrawn art shows solid furniture
// (chosen with the user): 0102 the right end of the inn counter, which led behind the shopkeeper. No event, item or
// script path uses them.
const COLLISION_CLOSED={'0102':[[8,4]]};
let storyView=false;
// Script camera (opcode 0x1C, ROM 0x63F8): scrolls the screen so its top-left cell reaches (x, y), y first then x, one
// cell per 32 frames; with flags 0 the script waits for it. Holds until the event ends, the map changes or the
// player is walked by the script. Positions are kept in the same "follow point" form as the player's.
let scriptCam=null;
// Camera requests from scripts: a cell (0x33) or a person by identity (0x01/0x42). In a battle they move the battle view;
// while exploring, a cell is panned to and held, and a person request hands the screen back to following the player.
async function focusCamera(c){
  // Opcode 06 (0x101A4): the camera goes to where the unit just loaded by 05 / 43 will appear, and the script waits for it.
  if(c.unit!=null){const e=vm.state.battleUnits?.[c.unit];if(e&&onBattlefield()){Object.assign(battleView,{x:(((e.raw[2]<<8)|e.raw[3])>>5)*32,y:(((e.raw[4]<<8)|e.raw[5])>>5)*32,dragged:false});await new Promise(r=>setTimeout(r,500));}return;}
  if(c.tileX!=null){if(onBattlefield()){Object.assign(battleView,{x:c.tileX*32,y:c.tileY*32,dragged:false});return;}await scrollCamera({x:c.tileX-4.5,y:c.tileY-3,flags:0});return;}
  if(c.unitIdentity!=null){const u=battle?.units.find(u=>u.identity===c.unitIdentity&&u.hp>0);if(u&&onBattlefield()){Object.assign(battleView,{x:u.x*32,y:u.y*32,dragged:false});return;}scriptCam=null;}}
async function scrollCamera(c){const w=view.width,h=view.height;const from=scriptCam??{x:camera.x+w/2-16,y:camera.y+h/2-16},to={x:c.x*32+160-16,y:c.y*32+112-16};
  const cam={...from};scriptCam=cam;const leg=async(key)=>{const a=cam[key],b=to[key],dur=Math.abs(b-a)/32*260;if(!dur)return;const t0=performance.now();await new Promise(r=>{function f(t){if(scriptCam!==cam)return r();const k=Math.min(1,(t-t0)/dur);cam[key]=a+(b-a)*k;if(k<1)requestAnimationFrame(f);else r();}requestAnimationFrame(f);});};
  const run=(async()=>{await leg('y');await leg('x');})();if(!c.flags)await run;}
function onBattlefield(){return !!battle&&!!session&&!storyView&&hex(session.battleMap.mapId)===map?.id;}
// Battle presentation: units glide between cells, hits flash and show damage, and AI turns wait for it (session ui.pace).
const fx={moves:new Map(),pops:[],flash:new Map(),hits:[],deaths:[],rises:new Map(),bars:[],bursts:[],tints:new Map(),dodges:new Map(),looks:[],until:0};
// A sprite filled with one colour (amount 0-1 over its own pixels only), drawn through a scratch canvas: the cartridge's
// palette fades, white for the dying and red for units struck by a 散體符 burst.
const tintCanvas=document.createElement('canvas'),tintCtx=tintCanvas.getContext('2d');
function tintedSprite(a,color,amount){if(tintCanvas.width!==canvas.width||tintCanvas.height!==canvas.height)Object.assign(tintCanvas,{width:canvas.width,height:canvas.height});const g=tintCtx;g.setTransform(1,0,0,1,0,0);g.clearRect(0,0,tintCanvas.width,tintCanvas.height);g.setTransform(ctx.getTransform());g.imageSmoothingEnabled=ctx.imageSmoothingEnabled;
  sprite(a,0,g);g.globalCompositeOperation='source-atop';g.globalAlpha=amount;g.fillStyle=color;g.fillRect(a.x-camera.x-32,a.y-camera.y-64,96,112);g.globalCompositeOperation='source-over';g.globalAlpha=1;
  ctx.save();if('filter' in ctx)ctx.filter='none';ctx.setTransform(1,0,0,1,0,0);ctx.drawImage(tintCanvas,0,0);ctx.restore();}
// 散體符 timing (ms from the burst): the comet rises, splits over the victims, drops on them; then the white flash.
const BURST={rise:330,split:480,drop:690,flash:80};
// Hit effects (assets/vfx/<sheet>.webp: 6 frames x 5 animations of 128 px, cut by shuihu-assets/tools/slice_vfx_sheets.py),
// chosen from what each item does in the ROM's skill table (weapon class, stratagem element, curse effect_type, cure):
// sabres chop, swords cross, halberds sweep, spears thrust, bows shoot, firearms blast, needles pierce, books and
// talismans call their element, curses and cures show their state. Books are opened on the caster first (CAST).
const VFX_FRAME=120,VFX_SHEETS=['physical','elements','nature','mystic','blades','missiles','strategy','curses','deities','items'];
const VFX_ITEMS={};{const set=(ids,sheet,row)=>{for(const id of ids)VFX_ITEMS[id]=[sheet,row];},span=(a,b)=>Array.from({length:b-a+1},(_,k)=>a+k);
  set([1,4,7,8,11],'blades',0);set([2,3,5,6,9,10,12,13],'blades',1);set(span(14,21),'physical',1);set(span(22,29),'physical',2);set([30],'missiles',0);
  set([31,36,41],'blades',2);set([32,33,34,35,38,39,40,42],'physical',3);set([37],'blades',3);set([43],'missiles',3);set([44,46],'missiles',1);set([45,48],'missiles',2);set([47],'physical',4);
  set([64],'elements',0);set([65],'elements',1);set([66],'elements',2);set([67],'elements',3);set([68],'elements',4);set([69],'nature',0);set([70],'nature',1);set([71],'nature',2);set([72],'nature',3);
  set([73],'strategy',1);set([74],'strategy',2);set([75],'strategy',3);set([76],'nature',4);set([77],'missiles',4);set([80],'curses',0);set([81],'mystic',2);set([82],'curses',1);set([83],'curses',2);
  set([84],'strategy',4);set([85],'curses',3);set([86],'deities',0);set([87],'deities',1);set([88],'deities',2);set([89],'deities',3);set([90],'blades',4);
  set([96,97,98],'mystic',3);set([99],'curses',4);set([100,101],'items',3);set([102],'deities',4);set([103,104],'mystic',4);
  set([128,133],'items',0);set([129,130,134],'items',4);set([131],'curses',4);set([132],'items',3);set([136,138,140,141,142],'items',1);set([137,139],'items',2);}
const CAST={sheet:'strategy',row:0};
const castsBook=id=>id>=64&&id<=104&&id!==77&&id!==90;
function vfxFor(id){const v=VFX_ITEMS[id]??['blades',0];return {sheet:v[0],row:v[1]};}
let battleSummary={},levelUps=[],levelUpShowing=false;
// Level-up card: portrait, level change and how much each stat rose (growthStats at the old vs new level, as battle.js
// recalculates). Shown one at a time; AI turns wait while it is open (session ui.pace).
// World map (opcode 0x29, ROM 0x10B58): the region's places; only those whose bit is set in the allowed mask can be chosen;
// the current destination starts selected; choosing returns its index, closing keeps the current one. Closing is offered
// only when the current destination is itself allowed: event 12:48 presets destination 3 with only 0 and 4 open and has
// no branch for 3 (label FFE3), so leaving there would run the script off its end (the ROM's B button would too).
function worldMap(c){return new Promise(resolve=>{const reg=worldMapData?.regions?.[c.region];if(!reg)return resolve({cancelled:true});let done=false;const finish=v=>{if(done)return;done=true;wrap.remove();resolve(v);};
  const wrap=document.createElement('div');wrap.className='worldmap';const box=document.createElement('div');box.className='wm-box';const title=document.createElement('div');title.className='wm-title';title.textContent='选 择 去 处';
  const stage=document.createElement('div');stage.className='wm-stage';const bg=document.createElement('img');bg.className='wm-bg';const hd=`assets/worldmap/hd-${c.region}.webp`;bg.src=art?.style!=='original'?hd:`assets/worldmap/orig-${c.region}.png`;bg.onerror=()=>{bg.onerror=null;bg.src=`assets/worldmap/orig-${c.region}.png`;bg.classList.add('pixel');};stage.append(bg);
  reg.forEach((p,i)=>{const ok=!!(c.allowed&(1<<i));if(!ok&&i!==c.current)return;   /* places not yet open stay hidden under the map, as on the cartridge (0x10B58) */
  const b=document.createElement('button');b.className='wm-place'+(ok?'':' locked')+(i===c.current?' here':'');b.style.left=`${(p.x+4)/worldMapData.width*100}%`;b.style.top=`${(p.y+4)/worldMapData.height*100}%`;b.innerHTML=`<i></i><span>${p.name}</span>`;b.disabled=!ok;b.setAttribute('aria-label',p.name+(ok?'':'（尚未开放）'));b.onclick=()=>finish(i);stage.append(b);});
  const close=document.createElement('button');close.className='wm-close';close.append(Object.assign(document.createElement('img'),{src:'assets/ui/buttons/btn-back.webp',alt:'返回'}));close.onclick=()=>finish({cancelled:true});if(c.canCancel===false)close.hidden=true;
  const hint=document.createElement('small');hint.className='wm-hint';hint.textContent='点地名前往';box.append(title,stage,hint,close);wrap.append(box);$('app').append(wrap);});}
function showLevelUps(){if(levelUpShowing||!levelUps.length)return;const {u,level}=levelUps.shift();levelUpShowing=true;
  const before=growthStats(battleData,u.classId,level-1,u.passive),after=growthStats(battleData,u.classId,level,u.passive);
  const card=document.createElement('div');card.className='levelup';card.innerHTML='<div class="lu-burst"></div>';const face=document.createElement('img');face.className='lu-face';face.src=portraitImage(u.identity);face.onerror=()=>{face.src=portraitImage(u.identity,false);};const title=document.createElement('div');title.className='lu-title';title.textContent='升 级';
  const name=document.createElement('div');name.className='lu-name';name.textContent=`${u.name}　Lv ${level-1} → ${level}`;const grid=document.createElement('div');grid.className='lu-stats';
  for(const [label,a,b] of [['体力',before.maxHp,after.maxHp],['攻击',before.attack[0],after.attack[0]],['计攻',before.attack[1],after.attack[1]],['防御',before.defense[0],after.defense[0]],['计防',before.defense[1],after.defense[1]],['命中',before.hit,after.hit],['闪避',before.resist,after.resist],['会心',before.critical,after.critical]]){const row=document.createElement('div');row.className='lu-row'+(b>a?' up':'');row.innerHTML=`<span>${label}</span><b>${b}</b><i>${b>a?'+'+(b-a):''}</i>`;grid.append(row);}
  const hint=document.createElement('small');hint.textContent='点击继续';card.append(title,face,name,grid,hint);const veil=document.createElement('div');veil.className='levelup-veil';veil.append(card);$('app').append(veil);
  const close=()=>{veil.remove();levelUpShowing=false;showLevelUps();};setTimeout(()=>veil.addEventListener('pointerup',close),400);}
// Battle result: victory banner, silver reward and what each fighter gained this battle.
// Ending (opcodes 0x49 / 0x4A, ROM 0x271C0 / 0x2732C). After the closing narration the original shows three full-screen
// pictures for 300 frames each (0x49); after the epilogue on map 0707 it shows one last picture and stops in an endless
// loop (0x4A). The remake plays painted scenes with slow camera moves and the narration as captions, then the finale with
// the party roll; a tap there returns to the title (the story state stays saved, so the world can still be roamed).
// Captions: the emperor's grant and toast (dialogue 499), then the closing narration (509) line by line.
const ENDING=[{img:'court',text:'宋江受封武德大夫　任职兵马总都'},{img:'banquet',text:'君臣同庆　共饮几杯'},{img:'capital',text:'自此　宋江为宋朝奠定了百年之根基\n百姓安居乐业　歌舞升平'},{img:'marsh',text:'梁山泊一干好汉事迹'},{img:'storyteller',text:'被后世广为流传'}];
const wait=ms=>new Promise(r=>setTimeout(r,ms));
function endingOverlay(){let el=document.querySelector('.ending');if(!el){el=document.createElement('div');el.className='ending';el.innerHTML='<div class="end-motes"></div><div class="end-bars"></div>';$('app').append(el);requestAnimationFrame(()=>el.classList.add('on'));}return el;}
// Each scene cross-fades in over the previous one; its caption appears character by character. A tap moves on early.
async function endingScenes(scenes,hold=7000){const el=endingOverlay();
  for(const [i,s] of scenes.entries()){const sc=document.createElement('div');sc.className=`end-scene pan-${i%4}`;const im=new Image();im.alt='';im.src=`assets/ending/${s.img}.webp`;await im.decode().catch(()=>{});sc.append(im);
    if(s.text){const cap=document.createElement('div');cap.className='end-caption';[...s.text].forEach((ch,k)=>{if(ch==='\n')return cap.append(document.createElement('br'));const c=document.createElement('span');c.textContent=ch;c.style.animationDelay=`${1+k*.13}s`;cap.append(c);});sc.append(cap);}
    el.insertBefore(sc,el.querySelector('.end-motes'));requestAnimationFrame(()=>requestAnimationFrame(()=>sc.classList.add('on')));const old=[...el.querySelectorAll('.end-scene')].slice(0,-1);setTimeout(()=>old.forEach(o=>o.remove()),1800);
    await new Promise(r=>{const t0=performance.now(),tm=setTimeout(done,hold);function done(){clearTimeout(tm);el.removeEventListener('pointerup',tap);r();}function tap(){if(performance.now()-t0>900)done();}el.addEventListener('pointerup',tap);});}
  return el;}
async function endingPictures(){const el=await endingScenes(ENDING);el.classList.remove('on');await wait(1400);el.remove();}
// Finale roll: the 108 stars of Liangshan in their stone-tablet order (data/heroes108.json); heroes who appear in this game
// show their portrait, those who fought in the party are gilded.
async function endingFinale(){const el=await endingScenes([{img:'chase',text:'江湖路远　后会有期'}],6000);
  const roster=await fetch('data/heroes108.json').then(r=>r.json()).catch(()=>({heroes:[]})),party=new Set(vm.state.party??[]);
  const fin=document.createElement('div');fin.className='end-scene end-finale';fin.innerHTML='<img src="assets/ending/finale.webp" alt="">';
  const roll=document.createElement('div');roll.className='end-roll';const list=document.createElement('div');list.className='end-roll-list';list.innerHTML='<h3>梁山泊英雄排座次</h3>';
  for(const h of roster.heroes){if(h.rank===1||h.rank===37){const sec=document.createElement('h4');sec.textContent=h.rank===1?'三十六天罡星':'七十二地煞星';list.append(sec);}
    const row=document.createElement('div');row.className='end-hero'+(h.identity?' known':'')+(party.has(h.identity)?' party':'');
    if(h.identity){const f=document.createElement('img');f.src=portraitImage(h.identity);f.onerror=()=>{f.onerror=null;f.src=portraitImage(h.identity,false);};row.append(f);}
    const t=document.createElement('span');t.innerHTML=`<small>${h.star}</small><em>${h.nickname}</em><b>${h.name}</b>`;row.append(t);list.append(row);}
  roll.append(list);const title=document.createElement('div');title.className='end-title';title.innerHTML='<b>水滸傳</b><i>完</i><small>点击返回标题</small>';fin.append(roll,title);
  el.insertBefore(fin,el.querySelector('.end-motes'));requestAnimationFrame(()=>requestAnimationFrame(()=>fin.classList.add('on')));setTimeout(()=>[...el.querySelectorAll('.end-scene')].filter(x=>x!==fin).forEach(x=>x.remove()),1800);
  list.style.animationDuration=`${Math.max(30,roster.heroes.length*.62)}s`;
  await wait(4000);title.classList.add('on');await wait(1500);
  await new Promise(r=>el.addEventListener('pointerup',r,{once:true}));try{localStorage.setItem('shuihu.native.cleared','1');}catch{}
  el.classList.remove('on');await wait(1200);el.remove();$('titleScreen').hidden=false;}
// Script op 0x34 (ROM 0x11732): before a reinforcement is revealed (op 07) the ground effect graphics at 0x9155E play
// on its cell and the script waits; zombies (sprite 78) all enter this way. Here: the ground cracks, then the unit
// rises out of it when it appears.
async function emergeEffect(){const slot=vm.state.lastSpawn,raw=vm.state.battleUnits?.[slot]?.raw;if(!raw||!battle)return;const x=((raw[2]<<8)|raw[3])>>5,y=((raw[4]<<8)|raw[5])>>5,now=performance.now();
  if(!battleView.dragged)Object.assign(battleView,{x:x*32,y:y*32});fx.hits.push({sheet:'nature',row:3,x,y,t0:now,big:true});fx.rises.set(slot,{t0:now+5*VFX_FRAME});await wait(6*VFX_FRAME);}
// Script presentation: fades run at the speed opcode 0x28 set (FF601B: (mask+1)*7 frames, e.g. 7 -> about 56, 1 -> 14);
// 0x47 whitens the whole screen for 2 frames (0x11F66); 0x14 / 0x17 / 0x37 / 0x46 hold the script 32 frames (0x10586).
const fadeMs=()=>{const f=vm?.state?.displayFlags;return f?((f[1]&7)+1)*7*1000/60:420;};
let screenFlash=0;
// Map props (props.json, ROM table 0x25F86): carts, the cave mouth, captives and the fallen, drawn behind people while
// their map is loaded and their bit of FFE11C (starts 0x243, flipped by opcode 0x3D) is set (0x25F02).
function drawProps(){if(!propData||!map)return;const id=String(map.id).toLowerCase(),mask=vm?.state?.spriteMask??propData.initialMask,hd=art?.active?.mapId===map.id&&!art.active.fallback&&art.style!=='original';   // over an HD map the redrawn prop (props-hd, 4x)
  for(const p of propData.props){if(p.map!==id||!((mask>>>p.bit)&1))continue;const b=hd&&p.hd?p.hd:p,i=img(b.image);if(i?.complete&&i.naturalWidth)ctx.drawImage(i,p.x+b.dx-Math.round(camera.x),p.y+b.dy-Math.round(camera.y),b.w,b.h);}}   // hd: a box with room for the shadow
// Opcodes 0x2E / 0x2F / 0x30 (0x115A2 / 0x1160A / 0x11672): a sweat drop running down beside the head (32 frames), shock
// lines over it (24) and puffs of angry smoke at both sides (64), on each listed figure at once; the script waits for them.
const EMOTES={0x2e:{frames:32,pat:f=>f<8?0x6b:f<16?0x6c:0x6d,dx:16,dy:f=>f>>1},0x2f:{frames:24,pat:f=>f<6?0x6e:f<12?0x70:f<18?0x6f:0x6e},0x30:{frames:64,pat:f=>[0x71,0x72,0x73,0x74][(f>>3)&3]}};
let emotes=[];
function emoteEffect(c){const e=EMOTES[c.opcode],t0=performance.now();for(const slot of c.entities??[])emotes.push({e,slot,t0});return new Promise(r=>setTimeout(r,e.frames*1000/60));}
function drawEmotes(t){emotes=emotes.filter(m=>t<m.t0+m.e.frames*1000/60);for(const m of emotes){const f=Math.max(0,Math.floor((t-m.t0)*60/1000)),fr=propData?.emotes?.[m.e.pat(f).toString(16)];if(!fr)continue;
  const u=onBattlefield()?battle.units.find(u=>u.slot===m.slot&&u.hp>0):null,a=u?unitDrawPos(u,t):actors.find(a=>a.slot===m.slot&&a.active);if(!a)continue;const i=img(fr.image);
  if(i?.complete&&i.naturalWidth)ctx.drawImage(i,Math.round(a.x+(m.e.dx??0)+fr.dx-camera.x),Math.round(a.y+(m.e.dy?.(f)??0)+fr.dy-camera.y),fr.w,fr.h);}}
function storyEffect(c){if(c?.kind==='fadeOut')return fadeScreen(1,fadeMs());if(c?.kind==='fadeIn')return fadeScreen(0,fadeMs());
  if(EMOTES[c?.opcode])return emoteEffect(c);if(c?.opcode===0x47){screenFlash=performance.now()+2000/60;return new Promise(r=>setTimeout(r,2000/60));}
  if([0x14,0x17,0x37,0x46].includes(c?.opcode))return new Promise(r=>setTimeout(r,32000/60));if(c?.opcode===0x49)return endingPictures();if(c?.opcode===0x4a)return endingFinale();if(c?.opcode===0x34)return emergeEffect();}
async function battleResult(r){await new Promise(r=>setTimeout(r,Math.max(0,fx.until-performance.now())));while(levelUpShowing||levelUps.length){showLevelUps();await new Promise(r=>setTimeout(r,200));}
  return new Promise(resolve=>{const wrap=document.createElement('div');wrap.className='result';const box=document.createElement('div');box.className='result-box';
  const title=document.createElement('div');title.className='result-title';title.textContent='战 斗 胜 利';const gold=document.createElement('div');gold.className='result-gold';gold.innerHTML=`<img src="assets/ui/silver-pile.webp" alt=""><span>获得银两</span><b>${r.gold}</b><span>两</span>`;
  const list=document.createElement('div');list.className='result-list';for(const sum of Object.values(battleSummary)){const row=document.createElement('div');row.className='result-row';const f=document.createElement('img');f.src=portraitImage(sum.identity);f.onerror=()=>{f.src=portraitImage(sum.identity,false);};row.append(f);const t=document.createElement('span');t.innerHTML=`<b>${sum.name}</b><small>经验 +${sum.exp}${sum.levels?`　升 ${sum.levels} 级`:''}</small>`;row.append(t);list.append(row);}
  const hint=document.createElement('small');hint.className='result-hint';hint.textContent='点击继续';box.append(title,gold);if(list.children.length)box.append(list);box.append(hint);wrap.append(box);$('app').append(wrap);battleSummary={};
  setTimeout(()=>wrap.addEventListener('pointerup',()=>{wrap.remove();resolve();}),600);});}
// 散體符 (ROM 0x4570 -> 0x170AE), drawn the way the cartridge does: the carrier whitens and melts into a cloud
// (drawSoul) that gathers into a comet and shoots up; high above it splits into one ball per victim, each ball drops on
// its victim trailing smaller balls, the screen flashes white, the victims show red and their damage falls onto them.
function drawSoul(d,look,t){const e=t-d.t0,cx=d.x+16-camera.x,cy=d.y+16-camera.y;
  if(e<470){ctx.globalAlpha=e<390?1:1-(e-390)/80;tintedSprite(look,'#ffffff',Math.min(1,e/390));ctx.globalAlpha=1;}
  if(e>320){const k=Math.min(1,(e-320)/300);ctx.fillStyle='#fff';
    for(let i=0;i<8;i++){const a=i*.785+e/260,r=(1-k)*11+1;ctx.globalAlpha=k<.85?1:(1-k)/.15;ctx.beginPath();ctx.arc(cx+Math.cos(a)*r,cy+Math.sin(a)*r*.8-k*6,4+2*Math.sin(i*1.7)*(1-k)+k*2,0,7);ctx.fill();}
    ctx.globalAlpha=1;}}
function drawBurst(b,t){const e=t-b.t0;if(e<0)return;const sx=b.x+16-camera.x,sy=b.y+10-camera.y,apex=Math.max(14,sy-130);ctx.fillStyle='#fff';
  const ball=(x,y,r,a=1)=>{ctx.globalAlpha=a;ctx.beginPath();ctx.arc(x,y,Math.max(.5,r),0,7);ctx.fill();},
    comet=(x,y,dir)=>{for(let k=4;k>0;k--)ball(x,y-dir*k*6.5,7-k*1.2,.95-k*.12);ball(x,y,7);};   // dir -1 rising (tail below), 1 falling (tail above)
  if(e<BURST.rise){const f=e/BURST.rise;comet(sx,sy+(apex-sy)*(1-(1-f)*(1-f)),-1);}
  else if(e<BURST.split){const f=(e-BURST.rise)/(BURST.split-BURST.rise),s=f*f*(3-2*f);for(const v of b.targets)ball(sx+(v.x+16-camera.x-sx)*s,apex-Math.sin(f*Math.PI)*6,6.5+Math.sin(e/40));if(!b.targets.length)ball(sx,apex,7*(1-f));}
  else if(e<BURST.drop){const f=(e-BURST.split)/(BURST.drop-BURST.split);for(const v of b.targets){const ty=v.y+12-camera.y;comet(v.x+16-camera.x,apex+(ty-apex)*f*f,1);}}
  else if(b.targets.length){const f=(e-BURST.drop)/BURST.flash;ctx.save();ctx.setTransform(1,0,0,1,0,0);ctx.globalAlpha=Math.max(0,1-f*f);ctx.fillRect(0,0,canvas.width,canvas.height);ctx.restore();}
  ctx.globalAlpha=1;}
function battleFx(events){const now=performance.now();let t=Math.max(now,fx.until),burstAt=null;
  const pop=(u,text,color,at)=>{if(u)fx.pops.push({x:u.x*32+16,y:u.y*32,text,color,t0:at});};
  for(const ev of events){const u=battle.unit(ev.unitId),tg=ev.targetId!=null?battle.unit(ev.targetId):null;
    if(u&&tg&&u.team!=='player'&&(ev.type==='attack'||ev.type==='heal'||ev.type==='status'))fx.looks.push({x:(u.x+tg.x)*16,y:(u.y+tg.y)*16,t0:t,t1:t+1500});   // the camera watches the other side's blows
    if(ev.type==='move'){const d=Math.max(1,Math.abs(ev.to.x-ev.from.x)+Math.abs(ev.to.y-ev.from.y));fx.moves.set(ev.unitId,{from:ev.from,to:ev.to,t0:t,dur:Math.min(900,170*d)});t+=Math.min(900,170*d)+150;}
    else if(ev.type==='attack'){if(ev.counter&&u){pop(u,'反击','#ffd27a',t);t+=350;}if(castsBook(ev.skillId)&&u){fx.hits.push({...CAST,x:u.x,y:u.y,t0:t});t+=4*VFX_FRAME;}if(tg)fx.hits.push({...vfxFor(ev.skillId),x:tg.x,y:tg.y,t0:t,big:!!ev.critical});const at=t+3*VFX_FRAME;if(ev.hit)fx.flash.set(ev.targetId,{t0:at,dur:300});else fx.dodges.set(ev.targetId,{t0:t});pop(tg,ev.hit?`${ev.critical?'会心 ':''}-${ev.damage}`:'闪避',ev.hit?(ev.critical?'#ffd84a':'#ff5a46'):'#d8e8ff',at);t=at+850;}
    else if(ev.type==='defeated'&&u){// the fallen fade and scatter into rising motes (the ROM's death effect, script op 0F)
      if(!battleView.dragged)battleView.x=u.x*32,battleView.y=u.y*32;const soul=events.some(e=>e.type==='burst'&&e.unitId===ev.unitId);fx.deaths.push({unitId:u.id,sprite:u.spriteType,x:u.x*32,y:u.y*32,t0:t,soul,seed:u.x*31+u.y*17+fx.deaths.length,tint:u.team==='player'?'#c8f5ff':'#ffe2b0'});t+=soul?620:750;}
    else if(ev.type==='burst'&&u){const victims=events.filter(e=>e.type==='burst-hit'&&e.unitId===ev.unitId).map(e=>battle.unit(e.targetId)).filter(Boolean);
      fx.bursts.push({x:ev.x*32,y:ev.y*32,targets:victims.map(v=>({x:v.x*32,y:v.y*32})),t0:t});burstAt=t+BURST.drop;t=burstAt;}
    else if(ev.type==='burst-hit'){const at=burstAt??t;fx.tints.set(ev.targetId,{t0:at+BURST.flash,dur:140,color:'#e84040'});fx.flash.set(ev.targetId,{t0:at+BURST.flash,dur:300});if(tg)fx.pops.push({x:tg.x*32+16,y:tg.y*32,text:`${ev.damage}`,color:'#ffffff',t0:at+BURST.flash,drop:true});t=Math.max(t,at+BURST.flash+900);}
    else if(ev.type==='heal'&&ev.rest){pop(tg,`休整 +${ev.amount}`,'#7dff9a',t);t+=600;}
    else if(ev.type==='heal'){if(castsBook(ev.skillId)&&u){fx.hits.push({...CAST,x:u.x,y:u.y,t0:t});t+=4*VFX_FRAME;}if(tg)fx.hits.push({...vfxFor(ev.skillId),x:tg.x,y:tg.y,t0:t});pop(tg,`+${ev.amount}`,'#7dff9a',t+3*VFX_FRAME);t+=3*VFX_FRAME+450;}
    else if(ev.type==='poison'&&u){fx.flash.set(u.id,{t0:t,dur:300});pop(u,`中毒 -${ev.damage}`,'#9be37a',t);t+=650;}
    else if(ev.type==='refresh'){pop(tg,'再次行动','#ffd27a',t);t+=650;}
    else if(ev.type==='reposition'&&u){pop(u,'可再移动','#ffd27a',t);t+=450;}
    else if(ev.type==='status'){if(castsBook(ev.skillId)&&u){fx.hits.push({...CAST,x:u.x,y:u.y,t0:t});t+=4*VFX_FRAME;}if(tg)fx.hits.push({...vfxFor(ev.skillId),x:tg.x,y:tg.y,t0:t});pop(tg,ev.hit?`${STATUS_NAMES[ev.field]??'中招'}${ev.field===1?'':` ${ev.duration??3}回合`}`:'无效','#e0a8ff',t+3*VFX_FRAME);t+=3*VFX_FRAME+450;}
    else if(ev.type==='experience'&&u&&u.team==='player'){if(ev.gained){const to=u.experience,from=ev.leveled?Math.max(0,to+100-ev.gained):Math.max(0,to-ev.gained);fx.bars.push({x:u.x,y:u.y,from,to,leveled:!!ev.leveled,t0:t});t+=ev.leveled?0:500;}const sum=battleSummary[u.identity]??={name:u.name,identity:u.identity,exp:0,levels:0,from:u.level-(ev.leveled?1:0)};sum.exp+=ev.gained;if(ev.leveled){sum.levels++;pop(u,'升级！','#ffe27a',t);t+=600;levelUps.push({u,level:u.level,at:t});}}}
  fx.until=t;}
// During the other side's turn the camera follows whoever is walking (from a moment before the step, so it arrives in time)
// and otherwise frames the latest blow it deals.
let battleCam=null;
function battleFollow(t){let walk=null;for(const [id,m] of fx.moves){const u=battle.unit(id);if(!u||u.team==='player'||t<m.t0-400)continue;if(!walk||m.t0<walk.m.t0)walk={u,m};}
  if(walk)return unitDrawPos(walk.u,t);fx.looks=fx.looks.filter(l=>t<l.t1);let look=null;for(const l of fx.looks)if(t>=l.t0&&(!look||l.t0>look.t0))look=l;return look;}
function unitDrawPos(u,now){const m=fx.moves.get(u.id);if(!m)return {x:u.x*32,y:u.y*32};if(now<m.t0)return {x:m.from.x*32,y:m.from.y*32};const f=Math.min(1,(now-m.t0)/m.dur);if(f>=1){fx.moves.delete(u.id);return {x:u.x*32,y:u.y*32};}
  // Walk along x then y, as the grid movement does.
  const dx=m.to.x-m.from.x,dy=m.to.y-m.from.y,total=Math.abs(dx)+Math.abs(dy)||1,s=f*total,sx=Math.min(Math.abs(dx),s),sy=Math.max(0,s-Math.abs(dx));return {x:(m.from.x+Math.sign(dx)*sx)*32,y:(m.from.y+Math.sign(dy)*sy)*32,moving:true,dir:sx<Math.abs(dx)?(dx>0?12:8):(dy>0?4:0)};}
// Dragging the battle map starts from what is on screen (the camera may be held at the map's edge while battleView points
// past it, which used to swallow the first part of every drag), stays within what the camera can reach, and follows the
// finger on the rotated screen too.
const viewCentre=(c,size,mapSize)=>mapSize<size?c:Math.max(size/2-16,Math.min(mapSize-size/2-16,c));
canvas.addEventListener('pointerdown',e=>{if(battle)battleView.drag={x:e.clientX,y:e.clientY,vx:camera.x+view.width/2-16,vy:camera.y+view.height/2-16,moved:false};});
canvas.addEventListener('pointermove',e=>{const d=battleView.drag;if(!battle||!d)return;const k=view.width/canvas.clientWidth,[dx,dy]=unrotate((e.clientX-d.x)*k,(e.clientY-d.y)*k);if(!d.moved&&Math.hypot(dx,dy)<8)return;d.moved=true;battleView.dragged=true;battleView.x=viewCentre(d.vx-dx,view.width,map.widthPixels);battleView.y=viewCentre(d.vy-dy,view.height,map.heightPixels);});
canvas.addEventListener('pointerup',async e=>{if(battleView.drag?.moved){battleView.drag=null;return;}battleView.drag=null;if(levelUpShowing||document.querySelector('.result,.levelup-veil'))return;if(!map||(!battle&&vm.running)||dialogue||modalStack.length||(!battle&&busy))return;if(!battle&&controlMode==='joystick')return;let q=localPoint(e,canvas),x=Math.floor((q.x*view.width/canvas.clientWidth+camera.x)/32),y=Math.floor((q.y*view.height/canvas.clientHeight+camera.y)/32);if(battle){battleTap(x,y);return;}if(x<0||y<0||x>=map.widthTiles||y>=map.heightTiles){const near=exitCells().filter(e=>Math.abs(e.x-x)+Math.abs(e.y-y)<=2).sort((a,b)=>Math.abs(a.x-x)+Math.abs(a.y-y)-Math.abs(b.x-x)-Math.abs(b.y-y))[0];if(!near)return;x=near.x;y=near.y;}const start={x:Math.floor(player().x/32),y:Math.floor(player().y/32)},actor=actors.find(a=>a.active&&a.slot!==0&&x*32<a.x+32&&x*32+32>a.x&&y*32<a.y+32&&y*32+32>a.y),v=collision[y*map.widthTiles+x];if(actor||v>=0x51&&v<=0xaf){// A person half a cell down (shopkeepers) also occupies the cell below, so they can be talked to across the counter, as on the cartridge.
const goals=actor?[...new Set([Math.floor((actor.y+31)/32),Math.floor(actor.y/32)])].map(cy=>({x:Math.round(actor.x/32),y:cy})):[{x,y}];let path=null;for(const g of goals){path=adjacentPath(start,g,map.widthTiles,map.heightTiles,passable);if(path)break;}if(!path&&!actor){toast(hiddenAt(x,y)?'有人挡在前面，等一会儿再来':'此处无法通行');return;}await walkPath(path,()=>actor?talk(actor):runEvent(v));}else if(passable(x,y))await walkPath(findPath(start,{x,y},map.widthTiles,map.heightTiles,passable));else toast(collectedHidden(x,y)?'这里的物品已经取走了':'此处无法通行');});
// The original places some NPCs half a cell down so their feet stand in a blocked cell (shopkeepers: y=112 over the counter
// row). With the taller HD figures that cell's top is painted again over their legs, so they read as behind the counter.
function behindCounter(a){if(!(a.slot>=8)||a.moving||!(art?.active&&!art.active.fallback&&art.style!=='original')||a.y%32===0)return false;const cx=Math.round(a.x/32),fy=Math.floor((a.y+31)/32);if(fy>=map.heightTiles)return false;return collision[fy*map.widthTiles+cx]>=0x50;}
function sprite(a,time,g=ctx){const c=assets.characters.find(c=>c.id===a.characterId),i=img(c?.sheet);if(!i?.complete||!i.naturalWidth)return;const state=(a.animationState??4)&~3,anim=state+(a.moving?Math.floor(time/130)%4:0),frame=(assets.animationFrameLookup[anim]??0)%c.frames;
  // A dark contact shadow under the feet so people sit in the painted scenery (skipped in the original pixel style).
  if(g===ctx&&art?.style!=='original'&&ctx.globalAlpha>.5){ctx.save();const sg=ctx.createRadialGradient(0,0,0,0,0,1);sg.addColorStop(0,'rgba(0,0,0,.8)');sg.addColorStop(.55,'rgba(0,0,0,.62)');sg.addColorStop(1,'rgba(0,0,0,0)');ctx.translate(Math.round(a.x-camera.x)+16,Math.round(a.y-camera.y)+30);ctx.scale(14,5);ctx.fillStyle=sg;ctx.beginPath();ctx.arc(0,0,1,0,7);ctx.fill();ctx.restore();}
  // With an HD map showing, original frames 0-8 come from the HD walk sheet (3x3 cells), feet on the cell's bottom edge.
  const hd=art?.active&&!art.active.fallback&&art.style!=='original'?hdSprites[c.bank]:null,hi=hd&&frame<9?img(hd.image):null;
  if(hi?.complete&&hi.naturalWidth){const size=hd.cell*hd.scale*32,sx=frame%3*hd.cell,sy=Math.floor(frame/3)*hd.cell;g.save();g.imageSmoothingEnabled=true;g.translate(Math.round(a.x-camera.x)+16,Math.round(a.y-camera.y)+32);if(state===12)g.scale(-1,1);g.drawImage(hi,sx,sy,hd.cell,hd.cell,-size/2,-size,size,size);g.restore();return;}
  g.save();g.translate(Math.round(a.x-camera.x)+(state===12?32:0),Math.round(a.y-camera.y));if(state===12)g.scale(-1,1);g.drawImage(i,frame*32,0,32,32,0,0,32,32);g.restore();}
// The view always holds at least the cartridge's 320x224 screen (cutscenes are framed for it): wider in landscape,
// taller in portrait.
// Exits: step events (01-4F) on the map's outer ring leave the map, as on the cartridge one cell past the doorway. A soft
// arrow pointing out of the map marks them so the last cell reads as the way out.
function exitCells(){if(exitCells.map===map&&exitCells.col===collision)return exitCells.list;const W=map.widthTiles,H=map.heightTiles,list=[];
  for(let y=0;y<H;y++)for(let x=0;x<W;x++){if(x&&y&&x<W-1&&y<H-1)continue;const v=collision[y*W+x];if(v>0&&v<0x50)list.push({x,y,dx:x===0?-1:x===W-1?1:0,dy:y===0?-1:y===H-1?1:0});}
  Object.assign(exitCells,{map,col:collision,list});return list;}
// 引导提示 (off by default, the cartridge shows none of this): arrows at the map's exits, an arrow in front of every door
// (an investigate cell whose event opens with the door sound / fade / map change, 0014 0010 0012 as in 0100:62), and a
// twinkle on hidden items not yet picked up.
let guideOn=false;try{guideOn=localStorage.getItem('shuihu.guide')==='1';}catch{}
function isDoorEvent(group,id){const bank=storyData.banks.find(b=>b.group===group),e=bank?.entries[id];if(e==null)return false;const B=storyData.bytes,w=k=>((B[e+2*k]??255)<<8)|(B[e+2*k+1]??255),ws=[0,1,2].map(w),i=ws.indexOf(0x12);return i>=0&&!ws.slice(0,i).some(op=>op===0||op===0x1d||op===0x36);}
// Doors: where the game puts the player when they come back out of a building. Every plain exit event that loads this
// map with a spawn record (0010 0012 map spawn 0013 0011 ffff) gives a cell and a facing; when the cell behind the player is an investigate cell whose
// event is a door (isDoorEvent), the arrow goes on that cell pointing at the door. (Whole house fronts often share the
// door's event code, so the code alone would mark every wall.)
function doorMarks(){if(doorMarks.map===map&&doorMarks.col===collision)return doorMarks.list;const W=map.widthTiles,H=map.heightTiles,g=vm.state.mapId>>8,id=vm.state.mapId,B=storyData.bytes,list=[],seen=new Set();
  const W16=k=>((B[k]??255)<<8)|(B[k+1]??255);
  for(let p=2;p+11<B.length;p+=2){// only plain exits (0010 0012 map spawn 0013 0011 ffff), not cutscenes that reuse a spawn
    if(W16(p)!==0x12||W16(p+2)!==id||W16(p-2)!==0x10||W16(p+6)!==0x13||W16(p+8)!==0x11||W16(p+10)!==0xffff)continue;const sid=hex((B[p+4]<<8)|B[p+5]);if(seen.has(sid))continue;seen.add(sid);
    const sp=storyData.spawns.find(x=>x.id===sid);if(!sp)continue;const x=Math.round(sp.player_x/32),y=Math.round(sp.player_y/32),[fx,fy]=[[0,-1],[0,1],[-1,0],[1,0]][sp.direction]??[0,0],dx=x-fx,dy=y-fy;
    if(dx<0||dy<0||dx>=W||dy>=H)continue;const v=collision[dy*W+dx];if(v>0x50&&v<=0xaf&&isDoorEvent(g,v))list.push({x,y,dx:-fx,dy:-fy});}
  Object.assign(doorMarks,{map,col:collision,list});return list;}
function drawGuide(t){if(!guideOn||vm?.running||!map)return;drawExits(t);const k=.5+.5*Math.sin(t/260);ctx.save();
  ctx.globalAlpha=.4+.45*k;ctx.fillStyle='#ffe9a8';ctx.strokeStyle='#5a3a12';ctx.lineWidth=1.5;
  for(const e of doorMarks()){const cx=e.x*32+16-camera.x+e.dx*(6+4*k),cy=e.y*32+16-camera.y+e.dy*(6+4*k),ax=e.dx,ay=e.dy;ctx.beginPath();ctx.moveTo(cx+ax*6,cy+ay*6);ctx.lineTo(cx-ax*4+ay*6,cy-ay*4+ax*6);ctx.lineTo(cx-ax*4-ay*6,cy-ay*4-ax*6);ctx.closePath();ctx.fill();ctx.stroke();}
  for(const h of storyData.hiddenItems??[]){if(parseInt(h.mapId,16)!==vm.state.mapId)continue;const x=h.cellIndex%map.widthTiles,y=Math.floor(h.cellIndex/map.widthTiles);if(collectedHidden(x,y))continue;
    const ph=(t/700+x*.37+y*.61)%1,a=Math.max(0,Math.sin(ph*Math.PI)),cx=x*32+16-camera.x,cy=y*32+14-camera.y,r=2+5*a;ctx.globalAlpha=.25+.75*a;ctx.fillStyle='#fffbe6';
    ctx.beginPath();ctx.moveTo(cx,cy-r);ctx.lineTo(cx+r*.25,cy-r*.25);ctx.lineTo(cx+r,cy);ctx.lineTo(cx+r*.25,cy+r*.25);ctx.lineTo(cx,cy+r);ctx.lineTo(cx-r*.25,cy+r*.25);ctx.lineTo(cx-r,cy);ctx.lineTo(cx-r*.25,cy-r*.25);ctx.closePath();ctx.fill();
    ctx.globalAlpha=.35*a;ctx.beginPath();ctx.arc(cx,cy,r*1.4,0,7);ctx.fill();}
  ctx.restore();}
function drawExits(t){if(vm?.running)return;const k=.5+.5*Math.sin(t/260);ctx.save();ctx.globalAlpha=.35+.4*k;ctx.fillStyle='#ffe9a8';ctx.strokeStyle='#5a3a12';ctx.lineWidth=1.5;
  for(const e of exitCells()){const cx=e.x*32+16-camera.x+e.dx*(3+4*k),cy=e.y*32+16-camera.y+e.dy*(3+4*k),ax=e.dx||0,ay=e.dy||(e.dx?0:1);
    ctx.beginPath();ctx.moveTo(cx+ax*7,cy+ay*7);ctx.lineTo(cx-ax*5+ay*7,cy-ay*5+ax*7);ctx.lineTo(cx-ax*5-ay*7,cy-ay*5-ax*7);ctx.closePath();ctx.fill();ctx.stroke();}
  ctx.restore();}
// A map narrower or shorter than the screen is shown as an unrolled hand-scroll: dark brocade outside it and a wooden
// roller with gold caps along each open edge.
function drawScrollFrame(w,h){if(!map)return;const x0=-Math.round(camera.x),y0=-Math.round(camera.y),x1=x0+map.widthPixels,y1=y0+map.heightPixels;if(x0<=0&&y0<=0&&x1>=w&&y1>=h)return;
  ctx.save();ctx.fillStyle='#1b1410';const bands=[[0,0,w,Math.max(0,y0)],[0,y1,w,h-y1],[0,0,Math.max(0,x0),h],[x1,0,w-x1,h]];for(const [x,y,bw,bh] of bands)if(bw>0&&bh>0)ctx.fillRect(x,y,bw,bh);
  ctx.globalAlpha=.07;ctx.fillStyle='#d9b26a';for(const [x,y,bw,bh] of bands){if(bw<=0||bh<=0)continue;for(let yy=y-(y%12);yy<y+bh;yy+=12)for(let xx=x-(x%12)+((yy/12)%2)*6;xx<x+bw;xx+=12){ctx.beginPath();ctx.arc(xx,yy,1.3,0,7);ctx.fill();}}ctx.globalAlpha=1;
  const roller=(x,y,len,vertical)=>{const t=9,g=vertical?ctx.createLinearGradient(x-t/2,0,x+t/2,0):ctx.createLinearGradient(0,y-t/2,0,y+t/2);g.addColorStop(0,'#3a2412');g.addColorStop(.35,'#a8723e');g.addColorStop(.6,'#6b4422');g.addColorStop(1,'#2a1a0c');ctx.fillStyle=g;
    if(vertical){ctx.fillRect(x-t/2,y-6,t,len+12);ctx.fillStyle='#d9b05a';ctx.fillRect(x-t/2-1.5,y-12,t+3,7);ctx.fillRect(x-t/2-1.5,y+len+5,t+3,7);}
    else{ctx.fillRect(x-6,y-t/2,len+12,t);ctx.fillStyle='#d9b05a';ctx.fillRect(x-12,y-t/2-1.5,7,t+3);ctx.fillRect(x+len+5,y-t/2-1.5,7,t+3);}};
  const top=Math.max(y0,0),bottom=Math.min(y1,h),left=Math.max(x0,0),right=Math.min(x1,w);
  if(x0>0)roller(x0-4,top,bottom-top,true);if(x1<w)roller(x1+4,top,bottom-top,true);if(y0>0)roller(left,y0-4,right-left,false);if(y1<h)roller(left,y1+4,right-left,false);
  ctx.restore();}
function render(t){const r={width:canvas.clientWidth,height:canvas.clientHeight},aspect=Math.max(1,r.height)/Math.max(1,r.width),w=Math.max(320,Math.round(224/aspect)),h=Math.round(w*aspect);const scale=art?.active&&!art.active.fallback&&art.style!=='original'?Math.min(4,Math.max(2,art.active.scale)):2;   // at least 2x so small text stays sharp; pixel art is drawn unsmoothed
Object.assign(view,{width:w,height:h,scale});if(canvas.width!==w*scale||canvas.height!==h*scale){canvas.width=w*scale;canvas.height=h*scale;}ctx.setTransform(scale,0,0,scale,0,0);ctx.imageSmoothingEnabled=false;ctx.fillStyle='#14221e';ctx.fillRect(0,0,w,h);if(map){let px,py;if(onBattlefield()){const sel=battle.units.find(u=>u.id===battle.selectedId),fol=battle.activeTeam!=='player'?battleFollow(t):null;if(fol){battleView.x=fol.x;battleView.y=fol.y;battleView.dragged=false;}else if(sel&&!battleView.dragged)battleView.x=sel.x*32,battleView.y=sel.y*32;else if(battleView.x==null){const mine=battle.units.filter(u=>u.team==='player'&&u.hp>0);battleView.x=mine.length?mine.reduce((t,u)=>t+u.x,0)/mine.length*32:0;battleView.y=mine.length?mine.reduce((t,u)=>t+u.y,0)/mine.length*32:0;}px=battleView.x;py=battleView.y;
  // The battle camera glides to where it is sent (about 0.1 s behind) instead of jumping; a drag moves it directly.
  if(!battleCam||battleView.drag?.moved)battleCam={x:px,y:py,t};else{const k=Math.min(1,Math.max(0,t-battleCam.t)/110);battleCam={x:battleCam.x+(px-battleCam.x)*k,y:battleCam.y+(py-battleCam.y)*k,t};}px=battleCam.x;py=battleCam.y;}else if(scriptCam){battleCam=null;px=scriptCam.x;py=scriptCam.y;}else{const p=player();px=p?.x??0;py=p?.y??0;}camera.x=map.widthPixels<w?(map.widthPixels-w)/2:Math.max(0,Math.min(map.widthPixels-w,px-w/2+16));camera.y=map.heightPixels<h?(map.heightPixels-h)/2:Math.max(0,Math.min(map.heightPixels-h,py-h/2+16));const bg=art?.active?.mapId===map.id?art.active.bitmap:art&&art.style!=='original'?null:img(map.image);if(bg?.complete&&bg.naturalWidth)ctx.drawImage(bg,-Math.round(camera.x),-Math.round(camera.y),map.widthPixels,map.heightPixels);drawScrollFrame(w,h);if(onBattlefield()){const iu=inspectId!=null?battle.unit(inspectId):null;if(iu&&iu.hp>0&&selectedSkill==null&&!moveMode){ctx.fillStyle='#ff5a1a66';ctx.strokeStyle='#ffb35acc';ctx.lineWidth=1;for(const q of battle.moveRange(iu.id)){ctx.fillRect(q.x*32-camera.x,q.y*32-camera.y,32,32);ctx.strokeRect(q.x*32-camera.x+.5,q.y*32-camera.y+.5,31,31);}}if(battle.selectedId!=null){const su=battle.unit(battle.selectedId);if(selectedSkill!=null&&su){ctx.fillStyle='#e0402c66';ctx.strokeStyle='#ffb0a0cc';ctx.lineWidth=1;for(const c of battle.reachCells(su.id)){ctx.fillRect(c.x*32-camera.x,c.y*32-camera.y,32,32);ctx.strokeRect(c.x*32-camera.x+.5,c.y*32-camera.y+.5,31,31);}   // the unit's own reach shape (by job)
ctx.strokeStyle='#ffd84a';ctx.lineWidth=2;for(const tg of battle.targets(su.id,selectedSkill))ctx.strokeRect(tg.x*32-camera.x+2,tg.y*32-camera.y+2,28,28);}else if(moveMode){ctx.fillStyle='#2f9fe066';ctx.strokeStyle='#a8e4ffd9';ctx.lineWidth=1;for(const q of battle.reachable(battle.selectedId)){ctx.fillRect(q.x*32-camera.x,q.y*32-camera.y,32,32);ctx.strokeRect(q.x*32-camera.x+.5,q.y*32-camera.y+.5,31,31);}}}drawProps();for(const u of battle.units.filter(u=>u.hp>0).sort((a,b)=>a.y-b.y)){const q=unitDrawPos(u,t),fl=fx.flash.get(u.id),hitNow=fl&&t>=fl.t0&&t<fl.t0+fl.dur,dg=fx.dodges.get(u.id),de=dg?t-dg.t0:-1,shake=(hitNow?Math.round(2.5*Math.sin((t-fl.t0)/67*2*Math.PI)*(1-(t-fl.t0)/fl.dur)):0)-(de>=0&&de<800?Math.round(6*Math.min(1,de/60,(800-de)/60)):0);
  // struck units shake from side to side (about 16 frames, 2-3 px) and a unit that evades steps 6 px aside while the blow passes (about 48 frames), as on the cartridge
// Player units that have finished this turn are drawn grey and standing still, so the ones still to act stand out.
  const done=u.team==='player'&&u.acted&&battle.activeTeam==='player'&&!q.moving;if(done){if('filter' in ctx)ctx.filter='grayscale(1) brightness(.72)';else ctx.globalAlpha=.55;}{const rise=fx.rises.get(u.slot),rf=rise?Math.min(1,Math.max(0,(t-rise.t0)/700)):1;if(rise&&rf>=1)fx.rises.delete(u.slot);
    if(rf<1){ctx.save();ctx.beginPath();ctx.rect(q.x-camera.x-24,q.y-camera.y-48,80,80);ctx.clip();}   // rising out of the ground: hidden below the cell's bottom edge
    {const look={characterId:u.spriteType,x:q.x+shake,y:q.y+(1-rf)*30,animationState:q.dir??4,moving:q.moving||(!done&&u.team===battle.activeTeam&&!u.acted),slot:-1},tn=fx.tints.get(u.id);if(tn&&t>=tn.t0&&t<tn.t0+tn.dur)tintedSprite(look,tn.color,1);else sprite(look,done?0:t);}if(rf<1)ctx.restore();}ctx.filter='none';ctx.globalAlpha=1;if(u.team==='player'&&battle.activeTeam==='player'&&!q.moving&&(done||u.moved)){const bx=q.x-camera.x+25,by=q.y-camera.y+3;ctx.fillStyle=done?'#b3261ee6':'#a8741ae6';ctx.fillRect(bx-6,by-6,12,12);ctx.strokeStyle='#ffe9c8';ctx.lineWidth=1;ctx.strokeRect(bx-5.5,by-5.5,11,11);ctx.fillStyle='#fff6e6';ctx.font='bold 9px "LXGW WenKai",serif';ctx.textAlign='center';ctx.textBaseline='middle';ctx.fillText(done?'完':'移',bx,by+.5);ctx.textAlign='start';ctx.textBaseline='alphabetic';}{// status badges (混乱/中毒/虚弱/破甲) in a row above the head, each with the turns left
const st=u.status??[],n=st.filter(Boolean).length;let sx=q.x-camera.x+16-(n*15-1)/2;for(let k=0;k<4;k++){if(!st[k])continue;const by=q.y-camera.y-11;ctx.fillStyle=['#8a4bd6f0','#2f8a3ef0','#c0761af0','#b02c2cf0'][k];ctx.fillRect(sx,by,14,10);ctx.strokeStyle='#fff8';ctx.lineWidth=.6;ctx.strokeRect(sx+.3,by+.3,13.4,9.4);ctx.fillStyle='#fff';ctx.font='bold 7.5px "LXGW WenKai",sans-serif';ctx.textBaseline='middle';ctx.textAlign='left';ctx.fillText('乱毒弱破'[k],sx+1,by+5.3);ctx.font='bold 6px sans-serif';if(k!==1)ctx.fillText(String(st[k]),sx+9.2,by+5.6);/* 中毒 has no count: it lasts until cured */ctx.textBaseline='alphabetic';sx+=15;}}
{// HP bar under each unit with the numbers written inside it
const bx=q.x-camera.x+3,by=q.y-camera.y+29,bw=26,bh=6.5,f=Math.max(0,u.hp/u.maxHp);ctx.fillStyle='#140d07e0';ctx.fillRect(bx-.5,by-.5,bw+1,bh+1);ctx.fillStyle=u.team==='player'?'#3f9a63':u.team==='ally'?'#b68a2c':'#b9412f';if(f<=1/3)ctx.fillStyle='#d2502e';ctx.fillRect(bx,by,bw*f,bh);if(!q.moving){ctx.font='bold 5.6px -apple-system,"Helvetica Neue",Arial,sans-serif';ctx.textAlign='center';ctx.textBaseline='middle';ctx.lineWidth=1.6;ctx.strokeStyle='#000b';const ht=`${u.hp}/${u.maxHp}`;ctx.strokeText(ht,bx+bw/2,by+bh/2+.3);ctx.fillStyle='#fff';ctx.fillText(ht,bx+bw/2,by+bh/2+.3);ctx.textAlign='start';ctx.textBaseline='alphabetic';}}}
  placeUnitMenu();if(iu&&iu.hp>0&&selectedSkill==null&&!moveMode){const tx=iu.x*32+16-camera.x,ty=iu.y*32-camera.y-4,label=iu.name;ctx.font='bold 8px "LXGW WenKai",serif';const w=ctx.measureText(label).width+6;ctx.fillStyle='#1a120ad9';ctx.fillRect(tx-w/2,ty-10,w,11);ctx.strokeStyle='#ff9a3c';ctx.lineWidth=1;ctx.strokeRect(tx-w/2+.5,ty-9.5,w-1,10);ctx.fillStyle='#ffe2b8';ctx.textAlign='center';ctx.fillText(label,tx,ty-2);}if(battleCursor&&document.body.classList.contains('keys')){const k=.5+.5*Math.sin(t/180);ctx.strokeStyle=`rgba(255,226,120,${.6+.4*k})`;ctx.lineWidth=2;ctx.strokeRect(battleCursor.x*32-camera.x+1.5,battleCursor.y*32-camera.y+1.5,29,29);}
  // Experience bar: pops up over the unit and fills from the old to the new value (to full, then the remainder, on a level-up).
  fx.bars=fx.bars.filter(b=>t<b.t0+1300);for(const b of fx.bars){if(t<b.t0)continue;const k=Math.min(1,(t-b.t0)/650),fade=t>b.t0+1000?1-(t-b.t0-1000)/300:1,e=1-Math.pow(1-k,3);
    let v=b.leveled?(e<.6?b.from+(100-b.from)*(e/.6):b.to*((e-.6)/.4)):b.from+(b.to-b.from)*e;const bx=b.x*32+2-camera.x,by=b.y*32-14-camera.y;ctx.save();ctx.globalAlpha=Math.max(0,fade);
    ctx.fillStyle='#140d07e6';ctx.fillRect(bx-1,by-1,30,6);ctx.fillStyle='#4a3a18';ctx.fillRect(bx,by,28,4);const g=ctx.createLinearGradient(bx,0,bx+28,0);g.addColorStop(0,'#c9952f');g.addColorStop(1,'#ffe27a');ctx.fillStyle=g;ctx.fillRect(bx,by,28*Math.min(1,v/100),4);
    if(b.leveled&&e>.55&&e<.7){ctx.fillStyle='#fff8';ctx.fillRect(bx,by,28,4);}ctx.font='bold 5.5px sans-serif';ctx.fillStyle='#ffe9a8';ctx.textAlign='right';ctx.fillText('EXP',bx-2,by+4);ctx.textAlign='start';ctx.restore();}
  fx.deaths=fx.deaths.filter(d=>t<d.t0+(d.soul?720:1100));for(const d of fx.deaths){const look={characterId:d.sprite,x:d.x,y:d.y,animationState:4,slot:-1};if(t<d.t0){const tn=fx.tints.get(d.unitId);if(tn&&t>=tn.t0&&t<tn.t0+tn.dur)tintedSprite(look,tn.color,1);else sprite(look,0);continue;}if(d.soul){drawSoul(d,look,t);continue;}const f=(t-d.t0)/1100;
    ctx.globalAlpha=Math.max(0,1-f*1.6);sprite({characterId:d.sprite,x:d.x,y:d.y-f*4,animationState:4,slot:-1},0);ctx.globalAlpha=1;
    let r=d.seed*9301+49297;const rnd=()=>((r=(r*9301+49297)%233280)/233280);ctx.fillStyle=d.tint;
    for(let i=0;i<30;i++){const ox=4+rnd()*24,oy=2+rnd()*28,sp=.5+rnd(),sz=1+rnd()*1.6,delay=rnd()*.25,k=Math.max(0,(f-delay)/(1-delay));if(!k)continue;
      ctx.globalAlpha=Math.max(0,(1-k)*(.6+.4*Math.sin((t/90)+i)));ctx.beginPath();ctx.arc(d.x+ox-camera.x+Math.sin(i+k*5)*4*k,d.y+oy-camera.y-k*30*sp,sz*(1-k*.4),0,7);ctx.fill();}
    ctx.globalAlpha=1;}
  fx.bursts=fx.bursts.filter(b=>t<b.t0+BURST.drop+BURST.flash+40);for(const b of fx.bursts)drawBurst(b,t);
  fx.hits=fx.hits.filter(h=>t<h.t0+6*VFX_FRAME);for(const h of fx.hits){if(t<h.t0)continue;const sh=img(`assets/vfx/${h.sheet}.webp`);if(!sh?.complete||!sh.naturalWidth)continue;const f=Math.min(5,Math.floor((t-h.t0)/VFX_FRAME)),size=h.big?72:60;ctx.drawImage(sh,f*128,h.row*128,128,128,h.x*32+16-size/2-camera.x,h.y*32+16-size/2-camera.y,size,size);}ctx.textAlign='center';ctx.font='bold 13px "LXGW WenKai",serif';fx.pops=fx.pops.filter(p=>t<p.t0+1300);for(const p of fx.pops){if(t<p.t0)continue;const f=(t-p.t0)/1300;const py=p.drop?p.y-camera.y-26+20*Math.min(1,((t-p.t0)/260)**2):p.y-camera.y-6-f*18;   // burst damage falls onto the head and stays, as on the cartridge
    ctx.globalAlpha=p.drop?Math.min(1,(1-f)*4):1-f*f;ctx.lineWidth=3;ctx.strokeStyle='#000a';ctx.strokeText(p.text,p.x-camera.x,py);ctx.fillStyle=p.color;ctx.fillText(p.text,p.x-camera.x,py);}ctx.globalAlpha=1;ctx.textAlign='start';}else{drawProps();drawGuide(t);const shown=actors.filter(a=>a.active);trackVanish(shown,t);const drawn=[...shown,...vanishGhosts(t)].sort((a,b)=>a.y-b.y);const bgPic=art?.active?.mapId===map.id&&!art.active.fallback&&art.style!=='original'?art.active.bitmap:null;
  // NPCs placed half a cell into a counter row (shopkeepers) stand whole on the floor behind it: lifted so their feet
  // meet the top of the counter's cell, instead of their taller HD figure standing on the counter.
  const stage=vm?.running?originalScreen():null;const blink=vm?.state?.displayFlag??0;for(const a of drawn){if(blink&&(blink>>((a.slot>>2)&15))&1&&Math.floor(t/(1000/60))%2)continue;   /* 0x3A: those slots flicker */
    if(a.leaveTo&&!a.moving&&(a.x!==a.leaveTo.x||a.y!==a.leaveTo.y))a.leaveTo=null;   // placed elsewhere since
    ctx.globalAlpha=(a.fade??1)*(stage&&a.leaveTo?offstageAlpha(a,stage):1);if(ctx.globalAlpha<=0)continue;sprite(bgPic&&behindCounter(a)?{...a,y:Math.floor((a.y+31)/32)*32-32}:a,t);}ctx.globalAlpha=1;foreground?.draw(ctx,{map,image:art?.active?.mapId===map.id?art.active.image:map.image,camera});}drawEmotes(t);   // original priority tiles (roofs, tree tops) over the people, original art only
  if(route.length){const p=route.at(-1);ctx.strokeStyle='#f9e5a0';ctx.lineWidth=1;ctx.strokeRect(p.x*32-camera.x+3,p.y*32-camera.y+3,26,26);}drawScreenFade(t);}requestAnimationFrame(render);}
function splitDialogue(d,portrait){
 const override=unicode.overrides?.[String(d.id)];if(override)return override;
 let pages=[],text='',pic=portrait;
 const flush=()=>{if(text.trim()){pages.push({text,portrait:pic});text='';}};
 for(const t of d.tokens){if(t.type==='portrait'){flush();pic=t.id;}else if(t.type==='glyph')text+=unicode.glyphs[`${t.bank}:${t.code}`]??'□';else if(t.type==='newline')text+='\n';else if(t.type==='segment_end')flush();}flush();return pages;
}
// Pages hold at most DIALOGUE_LINES lines as laid out in the box: text is cut after a line break or punctuation
// (one character at a time only when a single clause is longer than a page), measured on the box itself.
const DIALOGUE_LINES=3;
function fitPages(pages){const el=$('dialogueText'),pic=$('dialoguePortrait');const lh=parseFloat(getComputedStyle(el).lineHeight)||30,max=lh*DIALOGUE_LINES+lh*.5,out=[];
  const fits=t=>{el.textContent=t;return el.scrollHeight<=max;};
  for(const p of pages){pic.hidden=!assets.portraits.some(x=>x.id===p.portrait);let cur='';
    const push=()=>{const t=cur.replace(/^\n+|\n+$/g,'');if(t.trim())out.push({...p,text:t});cur='';};
    for(const part of p.text.split(/(?<=\n)|(?<=[。！？；，、…」])/)){
      if(fits(cur+part)){cur+=part;continue;}push();
      for(const ch of part){if(!fits(cur+ch))push();cur+=ch;}}
    push();}
  return out.length?out:pages;}
async function showDialogue(d,portrait){if(typeof d==='number')d=assets.dialogues.find(x=>x.id===d);if(!d)throw Error('缺少对话文本');let pages=splitDialogue(d,portrait);if(!pages.length)return;$('dialogue').hidden=false;pages=fitPages(pages);return new Promise(resolve=>{dialogue={pages,index:0,resolve,shownAt:performance.now()};$('dialogue').hidden=false;document.body.classList.add('talking');resetStick();drawDialogue();});}
function drawDialogue(){const p=dialogue.pages[dialogue.index],portrait=assets.portraits.find(x=>x.id===p.portrait);$('dialoguePortrait').hidden=!portrait;if(portrait){const el=$('dialoguePortrait'),hd=portraitImage(portrait.id);el.classList.toggle('hd',!!hd);el.onerror=()=>{el.onerror=null;el.classList.remove('hd');el.src=portrait.image;};el.src=hd||portrait.image;}$('dialogueText').textContent=p.text;}
function advanceDialogue(){if(!dialogue||performance.now()-dialogue.shownAt<220)return;if(dialogue.index<dialogue.pages.length-1){dialogue.index++;dialogue.shownAt=performance.now();drawDialogue();}else{const resolve=dialogue.resolve;dialogue=null;$('dialogue').hidden=true;document.body.classList.remove('talking');resolve();}}
// Capture the gesture before it can also move the player or activate an underlying menu.
let dialogueTapTime=0;document.addEventListener('pointerup',event=>{if(dialogue&&!modalStack.length){event.preventDefault();event.stopImmediatePropagation();dialogueTapTime=performance.now();advanceDialogue();}},true);
document.addEventListener('click',event=>{if((dialogue&&!modalStack.length)||performance.now()-dialogueTapTime<350){event.preventDefault();event.stopImmediatePropagation();}},true);
$('dialogue').addEventListener('keydown',event=>{if(event.key==='Enter'||event.key===' '){event.preventDefault();advanceDialogue();}});
// Shop: buy/sell tabs, icon grid with prices, the tapped item described below with its buy or sell button.
// Shop (ROM 0x1BBBA): the number to buy or sell is chosen, with the total price, the count in the bag and the count held
// altogether (bag plus everyone's equipment and carried items); what is held may not pass 99 (0x1BDAC), and more than the
// purse covers cannot be chosen. Selling pays half the price, bag items only (0x1C3AC).
function heldCount(id){id=Number(id);let n=vm.state.inventory[id]??0;for(const r of vm.state.roster??[])for(const k of [2,3,4,5,9,10,11,12,13])if(r[k]===id)n++;return n;}
async function shop(context){return new Promise(resolve=>{let tab='buy',selected=null,qty=1;modal('商店',function build(h){
  const tabs=document.createElement('div');tabs.className='shop-tabs';tabs.append(artButton('tab-buy','购买',()=>{tab='buy';selected=null;renderModal();},tab==='buy'),artButton('tab-sell','出售',()=>{tab='sell';selected=null;renderModal();},tab==='sell'));
  const purse=document.createElement('div');purse.className='purse-line';purse.innerHTML='<img class="coin" src="assets/ui/silver-ingot.webp" alt="">';purse.append(`银两 ${vm.state.gold}`);const top=document.createElement('div');top.className='shop-top';top.append(tabs,purse);h.append(top);
  const list=tab==='buy'?context.items.map(it=>({id:it.id,price:it.price})):Object.entries(vm.state.inventory).filter(([,n])=>n>0).map(([id,n])=>({id:Number(id),count:n,price:Math.floor(storyData.prices[id]/2)}));
  if(!list.length){para(h,tab==='buy'?'这里暂时没有货。':'行囊里没有可卖的东西。');return;}if(!list.some(x=>x.id===selected))selected=list[0].id;
  const grid=document.createElement('div');grid.className='bag-grid';const panel=document.createElement('div');panel.className='bag-detail';
  for(const it of list){const b=button('',()=>{if(selected!==it.id)qty=1;selected=it.id;renderModal();},'slot');b.setAttribute('aria-pressed',String(it.id===selected));b.setAttribute('aria-label',`${itemName(it.id)} ${it.price} 两`);const i=document.createElement('img');i.src=`assets/items/${it.id}.webp`;i.alt='';b.append(i);const pr=document.createElement('i');pr.className='price';pr.textContent=it.price;b.append(pr);if(it.count>1){const c=document.createElement('b');c.textContent=it.count;b.append(c);}grid.append(b);}
  const it=list.find(x=>x.id===selected),name=document.createElement('strong');name.textContent=itemName(it.id);const d=document.createElement('p');d.textContent=itemText[it.id]??'';const deal=document.createElement('div');deal.className='shop-deal';const price=document.createElement('span');price.className='purse-line';price.innerHTML='<img class="coin" src="assets/ui/silver-ingot.webp" alt="">';price.append(`${tab==='buy'?'售价':'收购价'} ${it.price}`);
  const held=heldCount(it.id),max=tab==='buy'?Math.min(it.price>0?Math.floor(vm.state.gold/it.price):99,99-held):it.count;qty=Math.max(Math.min(qty,max),max>0?1:0);
  const step=document.createElement('div');step.className='shop-qty';const minus=button('−',()=>{qty=Math.max(1,qty-1);renderModal();},'qty-btn'),plus=button('+',()=>{qty=Math.min(max,qty+1);renderModal();},'qty-btn'),all=button('最多',()=>{qty=max;renderModal();},'qty-btn');
  minus.disabled=qty<=1;plus.disabled=qty>=max;all.disabled=qty>=max;const n=document.createElement('b');n.textContent=`×${qty}`;step.append(minus,n,plus,all);
  const info=document.createElement('small');info.className='shop-held';info.textContent=`总价 ${it.price*qty} 两 · 行囊 ${vm.state.inventory[it.id]??0} · 持有 ${held}${tab==='buy'&&held>=99?'（已满 99）':''}`;
  const act=tab==='buy'?artButton('act-buy-on','买下',()=>{if(qty>0&&context.transact({kind:'buy',item:it.id,count:qty})){toast(`买下 ${itemName(it.id)} ×${qty}`);qty=1;renderModal();}else toast(held>=99?'最多持有 99 个':'银两不足');}):artButton('act-sell-on','卖出',()=>{if(qty>0&&context.transact({kind:'sell',item:it.id,count:qty})){toast(`卖出 ${itemName(it.id)} ×${qty}，得 ${it.price*qty} 两`);qty=1;renderModal();}});
  act.disabled=qty<1;deal.append(price,step,act);
  panel.append(name,d,statChips(it.id),info,deal);h.append(grid,panel);},[],()=>resolve({cancelled:true}));});}
// Action menu for the selected unit: a vertical strip floating beside it on the map (positioned every frame in render).
// Head of the floating unit menu: portrait, name, level and an HP bar (replaces the old bottom status bar).
// Each new turn / phase is announced once in the middle of the screen and fades out by itself.
let bannerKey='';function turnBanner(){const key=`${battle.turn}:${battle.activeTeam}`;if(key===bannerKey)return;bannerKey=key;if(battle.activeTeam==='player'){const lead=battle.units.find(u=>u.team==='player'&&u.hp>0);if(lead)Object.assign(battleView,{x:lead.x*32,y:lead.y*32,dragged:false});setTimeout(autoSaveBattle,1500);}   // each player phase opens on our leader
document.querySelector('.turn-banner')?.remove();const b=document.createElement('div');b.className='turn-banner '+battle.activeTeam;b.innerHTML=`<b>第 ${battle.turn} 回合</b><span>${battle.activeTeam==='player'?'我 方 行 动':battle.activeTeam==='ally'?'友 军 行 动':'敌 方 行 动'}</span>`;canvas.parentElement.append(b);setTimeout(()=>b.remove(),1900);}
function menuHead(u){const head=document.createElement('div');head.className='menu-head';const f=document.createElement('img');f.src=portraitImage(u.identity);f.alt='';f.onerror=()=>{f.onerror=null;f.src=portraitImage(u.identity,false);};
  const info=document.createElement('div');const n=document.createElement('b');n.textContent=u.name;const lv=document.createElement('small');lv.textContent=`Lv ${u.level}`;n.append(lv);const bar=document.createElement('div');bar.className='hp-bar';const fill=document.createElement('i');fill.style.width=`${Math.max(0,Math.min(100,u.hp/u.maxHp*100))}%`;if(u.hp/u.maxHp<.3)fill.className='low';bar.append(fill);const hp=document.createElement('span');hp.textContent=`体力 ${u.hp} / ${u.maxHp}`;const xp=document.createElement('div');xp.className='exp-bar';xp.title=`经验 ${u.experience??0} / 100`;const xf=document.createElement('i');xf.style.width=`${Math.min(100,u.experience??0)}%`;xp.append(xf);info.append(n,bar,hp,xp);head.append(f,info);const sts=(u.status??[]).map((v,k)=>v?`<i class="st st${k}">${'乱毒弱破'[k]}${v}</i>`:'').join('');if(sts){const row=document.createElement('div');row.className='menu-status';row.innerHTML=sts;const wrap=document.createElement('div');wrap.className='menu-head-wrap';wrap.append(head,row);return wrap;}return head;}
function unitMenu(){let m=$('unitMenu');if(!m){m=document.createElement('div');m.id='unitMenu';m.hidden=true;canvas.parentElement.append(m);}return m;}
function placeUnitMenu(){const m=$('unitMenu');if(!m||m.hidden)return;const u=battle?.unit(battle.selectedId);if(!u||session?.busy){m.hidden=true;return;}const k=canvas.clientWidth/view.width,q=unitDrawPos(u,performance.now()),sx=(q.x-camera.x)*k,sy=(q.y-camera.y)*k;m.style.visibility=q.moving||fx.moves.has(u.id)?'hidden':'';const right=sx+40*k+m.offsetWidth<canvas.clientWidth;
  m.style.left=`${canvas.offsetLeft+Math.max(4,Math.min(canvas.clientWidth-m.offsetWidth-4,right?sx+36*k:sx-m.offsetWidth-4*k))}px`;/* never past either edge */m.style.top=`${canvas.offsetTop+Math.max(4,Math.min(canvas.clientHeight-m.offsetHeight-4,sy+16*k-m.offsetHeight/2))}px`;}
function updateBattle(){if(!onBattlefield()){if($('unitMenu'))$('unitMenu').hidden=true;$('battleHud').hidden=true;return;}if($('unitMenu'))$('unitMenu').hidden=true;updateControls();const h=$('battleHud');h.replaceChildren();const u=battle.unit(battle.selectedId);h.hidden=!!u||!!session?.busy;turnBanner();const actions=document.createElement('div');actions.className='battle-actions';if(session?.busy){}else{
  // 攻击 = the unit's weapon; 计策 = books, curses and medicine (64-104); 道具 = consumables (128+).
  // Items carried on the person: the same icon grid as the bag; 确定 then asks for a target.
  const pick=(title,filter)=>{const list=battle.skillOptions(u.id).filter(o=>filter(o.skillId)&&o.enabled);if(!list.length)return toast(`没有可用的${title}`);pickItem(title,list.map(o=>[o.skillId,1]),'确定',id=>{selectedSkill=Number(id);closeModal();updateBattle();});};
  // As in the original, attacking means using one of the unit's equipped weapons/books/needles (each with its own range and
  // remaining uses, 攻擊次數); picking one shows its range in red on the map, then a target inside it is tapped.
  if(u){const menu=unitMenu();menu.replaceChildren();menu.hidden=moveMode||selectedSkill!=null;const body=document.createElement('div');body.className='menu-body';menu.append(menuHead(u),body);
    // While picking a target the menu is hidden so only the red range and the target frames show; a tap anywhere
    // outside a target cancels (battleTap).
    if(selectedSkill!=null){}
    else{const main=document.createElement('div');main.className='menu-col';
      const atk=artButton('bt-attack','攻击',()=>{itemMenuOpen=false;attackMenuOpen=!attackMenuOpen;updateBattle();});atk.classList.toggle('open',attackMenuOpen);const mv=artButton('bt-move','移动',()=>{attackMenuOpen=false;moveMode=true;updateBattle();});mv.disabled=!!u.moved;if(u.repositionOnly)atk.disabled=true;   // 一苇渡江鞋: after its blow only a step (or 待机) remains
      mv.classList.toggle('open',moveMode);main.append(mv,atk,(()=>{const it=artButton('bt-item','道具',()=>{attackMenuOpen=false;itemMenuOpen=!itemMenuOpen;updateBattle();});it.classList.toggle('open',itemMenuOpen);it.disabled=!!u.repositionOnly;return it;})(),artButton('bt-wait','待机',()=>{attackMenuOpen=false;battleAct(e=>e.wait(u.id));}),artButton(u.moved&&!u.acted?'bt-undo':'bt-cancel',u.moved&&!u.acted?'撤销':'取消',()=>{attackMenuOpen=false;moveMode=false;if(u.moved&&!u.acted){battle.undoMove(u.id);updateBattle();}else{battle.selectedId=null;selectedSkill=null;updateBattle();}}));body.append(main);
      // Second-level list: the unit's equipped weapons/books/needles with their numbers (攻击/命中 or 回复, 次数, 范围).
      // Item strip: the 4 things carried on the person, icon + name + one-line effect; tapping one picks a target.
      if(itemMenuOpen){const sub=document.createElement('div');sub.className='menu-col menu-sub';for(const o of battle.skillOptions(u.id).filter(o=>o.skillId>=128&&o.enabled)){const b=document.createElement('button');b.className='menu-weapon';const ic=document.createElement('img');ic.src=`assets/items/${o.skillId}.webp`;ic.alt='';const nm=document.createElement('strong');nm.textContent=itemName(o.skillId);
        const info=Object.fromEntries(itemStats(o.skillId));const st=document.createElement('small');st.textContent=[info['效果']??(info['伤害']?`伤害 ${info['伤害']}`:''),info['对象']].filter(Boolean).join(' · ');const txt=document.createElement('span');txt.append(nm,st);b.append(ic,txt);
        b.onclick=()=>{itemMenuOpen=false;selectedSkill=o.skillId;updateBattle();};sub.append(b);}if(!sub.children.length)sub.append(Object.assign(document.createElement('div'),{className:'menu-tip',textContent:'身上没有道具'}));body.append(sub);}
      if(attackMenuOpen){const sub=document.createElement('div');sub.className='menu-col menu-sub';for(const o of battle.skillOptions(u.id).filter(o=>o.skillId<128)){const b=document.createElement('button');b.className='menu-weapon';b.disabled=!o.enabled;const ic=document.createElement('img');ic.src=`assets/items/${o.skillId}.webp`;ic.alt='';const nm=document.createElement('strong');nm.textContent=itemName(o.skillId);const r=battleData.skills[o.skillId-1]??{},heal=battleData.healingAmounts?.[o.skillId],parts=[];
        if(heal)parts.push(`回复${heal}`);else if(r.power_or_quantity)parts.push(`攻${r.power_or_quantity}`);if(r.hit_bonus&&!heal)parts.push(`命${r.hit_bonus}`);if(r.range_candidate===2)parts.push('连击×2');parts.push(o.uses==null?'':o.uses>=99?'次数∞':`余${o.uses}`);if(o.kind==='unsupported')parts.push('效果待还原');
        const st=document.createElement('small');st.textContent=parts.filter(Boolean).join(' · ');const txt=document.createElement('span');txt.append(nm,st);b.append(ic,txt);b.onclick=()=>{attackMenuOpen=false;selectedSkill=o.skillId;updateBattle();};sub.append(b);}if(!sub.children.length)sub.append(Object.assign(document.createElement('div'),{className:'menu-tip',textContent:'没有可用的武器'}));body.append(sub);}}}
  else actions.append(textButton('战斗目的',showObjective,'bt-blank-4'),textButton('撤退',()=>modal('撤退',h=>para(h,'撤退即本场战斗失败，回到出战编成重新开始。已获得的经验和等级会保留。'),[{label:'确定',primary:true,fn:async()=>{closeModal();selectedSkill=null;if(battle)battle.selectedId=null;await session?.retreat();updateBattle();}}]),'bt-blank-2'),textButton('结束回合',()=>modal('结束本回合',host=>para(host,'未行动的同伴也将结束本回合。'),[{label:'确认结束',primary:true,fn:async()=>{closeModal();selectedSkill=null;battle.selectedId=null;await session?.endPlayerPhase();updateBattle();}}]),'bt-blank-4'));}
h.append(actions);}
function showUnitInfo(u){const st=document.createElement('div');modal(`${u.name} · ${u.team==='enemy'?'敌方':'友军'}`,h=>{const rows=document.createElement('div');rows.className='rs-rows';
  for(const [k,l,v] of [['rl-level','等级',u.level],['rl-hp','体力',`${u.hp} / ${u.maxHp}`],['rl-atk','攻击',u.attack[0]],['rl-satk','计攻',u.attack[1]],['rl-def','防御',u.defense[0]],['rl-sdef','计防',u.defense[1]],['rl-hit','命中',u.hit],['rl-eva','闪避',u.resist],['rl-crit','会心',u.critical],['rl-move','移动',u.movement]]){const row=document.createElement('div');row.className='rs-row';const i=document.createElement('img');i.src=`assets/ui/buttons/${k}.webp`;i.alt=l;const b=document.createElement('b');b.textContent=v;row.append(i,b);rows.append(row);}
  h.append(rows);{const list=(u.status??[]).map((n,k)=>n?`${STATUS_NAMES[k]}（剩 ${n} 回合）`:null).filter(Boolean);para(h,list.length?`状态：${list.join('　')}`:'状态：正常').className='note';}const eq=document.createElement('div');eq.className='rs-equip';for(const item of u.equipment??[]){const slot=document.createElement('div');slot.className='rs-slot';if(item){const i=document.createElement('img');i.src=`assets/items/${item}.webp`;i.alt='';const n=document.createElement('span');n.className='rs-slot-name';n.textContent=itemName(item);slot.append(i,n);}eq.append(slot);}h.append(eq);para(h,'地图上标出的橙色格子是它本回合能走到的范围。').className='note';},[],()=>{});}
function battleTap(x,y){if(!battle||!session||session.busy)return;const target=battle.alive().find(u=>u.x===x&&u.y===y),id=battle.selectedId,skill=selectedSkill;if(skill!=null&&id!=null){if(!target||!battle.targets(id,skill).some(t=>t.id===target.id)){selectedSkill=null;updateBattle();return;}battleAct(e=>e.useSkill(id,skill,target.id));return;}if(target?.team==='player'&&target.acted&&skill==null){inspectId=null;return;}   // a unit that has finished this turn stays put: no menu
if(target?.team==='player'){inspectId=null;battle.select(target.id);battleView.dragged=false;attackMenuOpen=false;itemMenuOpen=false;moveMode=false;updateBattle();return;}// Tapping an enemy or ally (with no own unit acting on it) shows its movement range and its status card.
// First tap on an enemy/ally shows its movement range (orange) with a small name tag; tapping it again opens its status.
if(target&&target.team!=='player'&&(id==null||selectedSkill==null&&!moveMode)){if(inspectId===target.id)showUnitInfo(target);else inspectId=target.id;return;}
inspectId=null;
if(id==null){inspectId=null;return;}if(target){battleAct(e=>e.attack(id,target.id));return;}if(!moveMode)return;const result=battle.move(id,x,y);moveMode=false;if(result.ok)session.settle();updateBattle();}
// After opcode 0x45 character 1's record is 宋江's (identity 0x15): names and faces of party member 1 follow it.
const shownIdentity=id=>id===1&&vm?.state?.firstPartyIdentity===0x1515?0x15:id;
function unitName(identity){identity=shownIdentity(identity);const n=assets.character_names.find(c=>c.id===identity-1);return (n?.tokens??[]).filter(t=>t.type==='glyph').map(t=>unicode.glyphs[`${t.bank}:${t.code}`]??'□').join('').replace(/\s+/g,'')||`人物 ${identity}`;}
// Battles start after the event that ran opcode 0x25 finishes; the stage scheduler then drives all battle events.
// Battle music (ROM 0x27EBE, table 0x27EE4 by stage): the cartridge rotates three tunes, 1 / 7 / 8, stage by stage and
// plays the scene's tune again afterwards. Its tune 1 is also the town music, so here that slot takes 9 (决战), and the
// rotation runs on through three tunes made for this remake (13-15), six in all, so battles never share the places' music.
const BATTLE_ROTATION=[9,7,8,13,14,15],battleTune=stage=>BATTLE_ROTATION[Math.max(0,stage|0)%BATTLE_ROTATION.length];
function createSession(p){return new BattleSession({vm,battleData,tables:battleStages,stage:p.stage,battleMap:{mapId:p.mapId,width:p.width,height:p.height},passable:(x,y,u)=>x>=0&&y>=0&&x<map.widthTiles&&y<map.heightTiles&&collision[y*map.widthTiles+x]<terrainLimit(u),ui:{chooseDeployment,runEvent:runBattleEvent,changed:(s,events)=>{if(session!==s)return;battle=s.ended?null:s.engine;if(battle){for(const u of battle.units)u.name=unitName(u.identity);battleFx(events??[]);updateBattle();setTimeout(showLevelUps,Math.max(0,fx.until-performance.now()));}},pause:ms=>new Promise(r=>setTimeout(r,ms)),lost:()=>new Promise(r=>{document.querySelector('.turn-banner')?.remove();const b=document.createElement('div');b.className='turn-banner lost';b.innerHTML='<b>战 役 失 败</b>';$('app').append(b);setTimeout(()=>{b.remove();r();},1700);}),pace:async()=>{await new Promise(r=>setTimeout(r,Math.max(0,fx.until-performance.now())+400));showLevelUps();while(levelUpShowing)await new Promise(r=>setTimeout(r,200));},ended:async s=>{if(session!==s)return;if(sceneMusic!=null&&musicStamp===s.musicStamp)playMusic(sceneMusic);sceneMusic=null;   /* a tune the battle's scripts chose (4B / 4C) stays */
session=null;battle=null;selectedSkill=null;$('battleHud').hidden=true;updateControls();actors=vm.state.entities;await startPendingBattle();}}});}
function openSession(s,stage){session=s;s.musicStamp=musicStamp;sceneMusic=currentMusic;playMusic(battleTune(stage));storyView=false;bannerKey="";battleSummary={};levelUps=[];Object.assign(battleView,{x:null,y:null,dragged:false,drag:null});}
async function startPendingBattle(){for(const n of VFX_SHEETS)img(`assets/vfx/${n}.webp`);while(pendingBattle&&!session){const p=pendingBattle;pendingBattle=null;const s=createSession(p);openSession(s,p.stage);try{await s.start();}catch(e){session=null;battle=null;$('battleHud').hidden=true;updateControls();storyError(e);}}}
async function runBattleEvent(group,id){try{await vm.start(group,id);actors=vm.state.entities;}catch(e){storyError(e);throw e;}}
// Deployment (original 0x248E2): party members on the stage's must-deploy list are locked in and preselected; the others
// are optional; at most min(stage limit, party size) go. Cards show portrait, name, job and level.
// Deployment (original 0x248E2): party members on the stage's must-deploy list are locked in and preselected; the others
// are optional; at most min(stage limit, party size) go. Left: the roster (tapping a portrait deploys or stands the
// member down, as in the original); right: the last tapped member's status.
function chooseDeployment(options){return new Promise(resolve=>{const chosen=new Set(options.mandatory),all=[...options.mandatory,...options.optional];let focus=all[0];modal('出战人员',function build(h){
  const head=document.createElement('div');head.className='deploy-head';const count=document.createElement('strong');count.textContent=`出战 ${chosen.size} / ${options.limit}`;const note=document.createElement('span');note.textContent='点头像：出战 / 待命';head.append(count,note);h.append(head);
  const wrap=document.createElement('div');wrap.className='deploy-wrap';const grid=document.createElement('div');grid.className='deploy-grid';
  for(const id of all){const locked=options.mandatory.includes(id),r=rosterRecord(id)??[];const card=button('',()=>{focus=id;if(locked)toast(`${unitName(id)}必须出战`);else if(chosen.has(id))chosen.delete(id);else if(chosen.size<options.limit)chosen.add(id);else toast(`最多 ${options.limit} 人出战`);renderModal();},'deploy-card');card.setAttribute('aria-pressed',String(chosen.has(id)));if(id===focus)card.classList.add('focus');
    const face=document.createElement('img');face.className='deploy-face';face.src=portraitImage(id);face.onerror=()=>{face.src=portraitImage(id,false);};face.alt='';const name=document.createElement('strong');name.textContent=unitName(id);const sub=document.createElement('small');sub.textContent=`${r[6]||1}级`;card.title=`${unitName(id)} · ${jobName(r[8])} · ${r[6]||1}级`;card.append(face,name,sub);
    if(locked){const seal=document.createElement('img');seal.className='deploy-seal';seal.src='assets/ui/buttons/seal-must.webp';seal.alt='必须出战';card.append(seal);}
    card.setAttribute('aria-label',`${unitName(id)}${chosen.has(id)?'，出战':'，待命'}${locked?'，必须出战':''}`);grid.append(card);}
  const side=document.createElement('div');side.className='deploy-side';side.append(statusCard(focus));

  wrap.append(grid,side);h.append(wrap);},[{label:'开始战斗',primary:true,fn:()=>{closeModal();resolve([...chosen]);}}],()=>resolve([...chosen]));});}
async function battleAct(action){if(!session||session.busy)return toast('请等待战场事件结束');selectedSkill=null;const result=await session.act(action);if(result&&!result.ok)toast(result.error);if(battle)battle.selectedId=null;updateBattle();
  // once this action's animation has played, the camera moves on to the next of our people who has not acted yet
  if(result?.ok)setTimeout(selectNextUnit,Math.max(0,fx.until-performance.now())+300);}
// After one of ours has acted and its animation has played, the next of ours who has not acted yet is selected and its
// menu opens, so play carries on without hunting for whose turn it is (waits out level-up cards and battle events).
function selectNextUnit(tries=0){if(!battle||battle.activeTeam!=='player'||battle.selectedId!=null||modalStack.length)return;
  if(session?.busy||levelUpShowing||levelUps.length||dialogue||document.querySelector('.result,.levelup-veil')){if(tries<40)setTimeout(()=>selectNextUnit(tries+1),250);return;}
  const ours=battle.units.filter(u=>u.team==='player'&&u.hp>0&&!u.removed&&!u.acted),next=ours.find(u=>u.repositionOnly)??ours[0];if(!next)return;
  inspectId=null;battle.select(next.id);Object.assign(battleView,{x:next.x*32,y:next.y*32,dragged:false});attackMenuOpen=false;itemMenuOpen=false;moveMode=!!next.repositionOnly;updateBattle();}
// Music volume: 关/低/中/高 (remembered); the ♪ corner button mutes and unmutes.
const VOLUMES=[0,.2,.45,.8];let musicLevel=2;try{const v=Number(localStorage.getItem('shuihu.volume'));if(v>=0&&v<=3&&localStorage.getItem('shuihu.volume')!=null)musicLevel=v;}catch{}
// Music is on by default (中) unless the player chose 关; browsers only let sound start after a first tap or key, so the
// first one starts it.
soundEnabled=musicLevel>0;
{const start=()=>{removeEventListener('pointerdown',start,true);removeEventListener('keydown',start,true);if(soundEnabled)playMusic(currentMusic);};addEventListener('pointerdown',start,true);addEventListener('keydown',start,true);}
setTimeout(()=>{if(soundEnabled)playMusic(currentMusic);},0);
// Music stops while the game is not on screen (app switched away, phone locked, other tab) and resumes on return;
// the iOS shell also calls shuihuPause / shuihuResume from its own background notifications.
window.shuihuPause=()=>music.pause();window.shuihuResume=()=>{if(soundEnabled&&!document.hidden)playMusic(currentMusic);};
document.addEventListener('visibilitychange',()=>document.hidden?window.shuihuPause():window.shuihuResume());
addEventListener('pagehide',()=>window.shuihuPause());addEventListener('blur',()=>{if(document.hidden)window.shuihuPause();});   // the iOS app allows this at once; browsers wait for the first tap
function setVolume(level){musicLevel=level;try{localStorage.setItem('shuihu.volume',String(level));}catch{}music.volume=VOLUMES[level];soundEnabled=level>0;$('audioToggle').textContent=soundEnabled?'♫':'♪';if(soundEnabled)playMusic(currentMusic);else music.pause();}
function playMusic(id){currentMusic=id;if(!soundEnabled)return;const src=`assets/audio/music_${String(id).padStart(2,'0')}.m4a`;if(!music.src.endsWith(src)){music.src=src;music.loop=true;}music.volume=VOLUMES[musicLevel]||.45;music.play().catch(()=>{});}
$('audioToggle').textContent=soundEnabled?'♫':'♪';
$('audioToggle').onclick=()=>{soundEnabled=!soundEnabled;try{localStorage.setItem('shuihu.volume',String(soundEnabled?(musicLevel||2):0));}catch{}if(soundEnabled&&!musicLevel)musicLevel=2;$('audioToggle').textContent=soundEnabled?'♫':'♪';if(soundEnabled)playMusic(currentMusic);else music.pause();toast(soundEnabled?'声音已开启':'声音已关闭');};
// A place's own tune (music.json, from the cartridge's table for opcode 0x4C). The title theme also hands over to it when
// the opening ends or a save is loaded, which no script asks for.
function placeMusic(id){const v=musicData?.maps?.[id];if(v!=null)playMusic(v);}
async function newGame(){if(vm?.running||busy)return;closeModal(true);vm=createVM();actors=structuredClone(initial.actors);vm.setEntities(actors);actors=vm.state.entities;await changeMap(0x106,0x100,{entities:actors,patches:vm.collisionPatches()});$('titleScreen').hidden=true;await runEvent(0x41);if(currentMusic===12)placeMusic(map.id);}
function createVM(){return new StoryVM({data:storyData,hooks:{dialogue:showDialogue,changeMap,setEntities:a=>{actors=a;},moveEntity:moveActor,collision:p=>{for(const q of p)collision[q.index]=q.value;},wait:frames=>new Promise(r=>setTimeout(r,frames*1000/60)),shop,music:id=>{musicStamp++;playMusic(id);},mapMusic:id=>{musicStamp++;placeMusic(hex(id));},spawnUnit:slot=>session?.spawnNow(slot),battle:()=>{},prepareBattle:async c=>{await changeMap(c.mapId,null,{entities:vm.state.entities});pendingBattle={...c,stage:vm.state.stage};},battleReset:c=>{session?.onReset(c);if(c.retry)toast('战斗将重新开始');},battleEnd:()=>session?.onEnd(),battleRewards:async r=>{vm.state.gold;await battleResult(r);},reward:r=>rewardCard(r),effect:storyEffect,choice:context=>worldMap(context),error:e=>console.error(e),movement:c=>scrollCamera(c),camera:c=>focusCamera(c),complete:()=>{scriptCam=null;stageCam=null;if(fadeLevel(performance.now())>0)fadeScreen(0);actors=vm.state.entities;save();}}});}
$('newGame').onclick=()=>{if(readSave('auto'))modal('开始新的旅程',h=>para(h,'自动存档会随新旅程更新，手动存档将保留。'),[{label:'开始',primary:true,fn:()=>{closeModal();newGame();}}]);else newGame();};$('continueGame').onclick=()=>loadSave(readSave('auto'));
try{[assets,storyData,npcs,battleData,battleStages,initial,unicode]=await Promise.all(['assets','story','npc-dialogues','battle','battle-stages','initial-world','unicode'].map(f=>fetch(`data/${f}.json`).then(r=>{if(!r.ok)throw Error('数据载入失败');return r.json();})));await Promise.all([...assets.fonts.banks.map(f=>f.sheet),...assets.characters.map(c=>c.sheet),...assets.portraits.map(p=>p.image)].map(ready));artManifest=await fetch('data/art-styles.json').then(r=>r.ok?r.json():{}).catch(()=>({}));itemText=await fetch('data/item-descriptions.json').then(r=>r.ok?r.json():{}).then(d=>d.items??{}).catch(()=>({}));worldMapData=await fetch('data/worldmap.json').then(r=>r.ok?r.json():null).catch(()=>null);musicData=await fetch('data/music.json').then(r=>r.ok?r.json():null).catch(()=>null);propData=await fetch('data/props.json').then(r=>r.ok?r.json():null).catch(()=>null);objectives=await fetch('data/objectives.json').then(r=>r.ok?r.json():null).then(d=>d?.stages??null).catch(()=>null);hdSprites=await fetch('data/characters-hd.json').then(r=>r.ok?r.json():{}).then(d=>d.sheets??{}).catch(()=>({}));/* the build number on the title screen is the service worker's cache version, so there is one number to bump *//* (the iPhone app has no service worker: ios/Shuihu/sync_web.sh writes version.txt) */Promise.all(['sw.js','version.txt'].map(f=>fetch(f,{cache:'no-store'}).then(r=>r.ok?r.text():'').catch(()=>''))).then(([sw,txt])=>{const v=sw.match(/CACHE='shuihu-native-(v\d+)'/)?.[1]??txt.trim();if(/^v\d+$/.test(v))$('buildTag').textContent=`版本 ${v}`;});let storage;try{storage=localStorage;}catch{}art=new ArtSelection({storage,manifest:artManifest,load:ready});const foregroundManifest=await fetch('data/foreground.json').then(r=>r.ok?r.json():{maps:{}}).catch(()=>({maps:{}}));foreground=new OriginalForeground({manifest:foregroundManifest,load:ready});vm=createVM();$('newGame').disabled=false;$('titleHelp').disabled=false;$('continueGame').hidden=!readSave('auto');playIntro($('titleScreen'));$('hint').textContent='点地面移动 · 点人物交谈';requestAnimationFrame(render);}catch(e){$('loadError').textContent='载入失败，请刷新重试：'+e.message;console.error(e);}
if('serviceWorker' in navigator)navigator.serviceWorker.register('./sw.js').catch(()=>{});

let controlMode='tap',stickDirection=null,stickRunning=false;
try{controlMode=localStorage.getItem('shuihu.controlMode')==='joystick'?'joystick':'tap';}catch{}
// Screen orientation: 'auto' follows the device; 'landscape'/'portrait' rotate the whole #app by 90° when the device
// is held the other way (and ask the browser to lock, where it allows). Touch input is mapped back through the rotation.
let orientationMode='auto',rotation=0;try{orientationMode=localStorage.getItem('shuihu.orientation')||'auto';}catch{}
function applyOrientation(){const portrait=innerHeight>innerWidth;rotation=orientationMode==='landscape'&&portrait?90:orientationMode==='portrait'&&!portrait?-90:0;document.documentElement.dataset.rotate=rotation;document.documentElement.dataset.layout=(portrait?rotation!==0:rotation===0)?'landscape':'portrait';}   // what the player sees, after any forced rotation
function setOrientation(mode){orientationMode=mode;try{localStorage.setItem('shuihu.orientation',mode);}catch{}if(mode==='auto')screen.orientation?.unlock?.();else screen.orientation?.lock?.(mode).catch(()=>{});applyOrientation();}
addEventListener('resize',applyOrientation);applyOrientation();
const unrotate=(dx,dy)=>rotation===90?[dy,-dx]:rotation===-90?[-dy,dx]:[dx,dy];
function localPoint(e,el){const r=el.getBoundingClientRect(),sx=e.clientX-r.left,sy=e.clientY-r.top;return rotation===90?{x:sy,y:r.width-sx}:rotation===-90?{x:r.height-sy,y:sx}:{x:sx,y:sy};}
const resetStick=bindJoystick($('joystickPad'),$('joystickKnob'),direction=>{stickDirection=direction;if(direction!=null)stepStick();},unrotate);
function updateControls(){$('joystickControls').hidden=controlMode!=='joystick'||!!battle;if($('dpadControls'))$('dpadControls').hidden=controlMode!=='dpad';$('hint').hidden=true;/* the how-to line over the map is gone; 操作说明 in the menu covers it */}
function setControlMode(mode){controlMode=mode;resetStick();route=[];try{localStorage.setItem('shuihu.controlMode',mode);}catch{}updateControls();}
async function stepStick(){if(stickRunning)return;stickRunning=true;try{while(stickDirection!=null&&map&&!battle&&!dialogue&&!vm.running&&!modalStack.length&&!busy){const dir=stickDirection,p=player(),x=Math.round(p.x/32)+[0,0,-1,1][dir],y=Math.round(p.y/32)+[-1,1,0,0][dir];p.animationState=[0,4,8,12][dir];const v=x>=0&&y>=0&&x<map.widthTiles&&y<map.heightTiles?collision[y*map.widthTiles+x]:0x50;if(!passable(x,y)){if(v>0x50&&v<0x80){resetStick();await runEvent(v);}break;}busy=true;await moveActor(0,{x:x*32,y:y*32,animationState:p.animationState});busy=false;if(v>0&&v<0x50){resetStick();await runEvent(v);break;}}}finally{busy=false;stickRunning=false;}}
async function interactFront(){if(!map||busy||vm.running||dialogue||battle)return;resetStick();const p=player(),dir=Math.floor((p.animationState??4)/4),x=Math.round(p.x/32)+[0,0,-1,1][dir],y=Math.round(p.y/32)+[-1,1,0,0][dir];const actor=actors.find(a=>a.active&&a.slot!==0&&x*32<a.x+32&&x*32+32>a.x&&y*32<a.y+32&&y*32+32>a.y);if(actor)return talk(actor);const v=x>=0&&y>=0&&x<map.widthTiles&&y<map.heightTiles?collision[y*map.widthTiles+x]:0;if(v>0x50&&v<=0xaf)await runEvent(v);else toast('面前没有可调查的东西');}
$('interactButton').onclick=interactFront;
// Direction keys: keyboard (arrows / WASD, Enter·Space·Z confirm, Esc·X·Backspace cancel), game pads (d-pad or left stick,
// A confirm, B cancel, Start menu), TV remotes (their arrows and OK arrive as the same keys) and the on-screen pad of the
// 方向按键 mode. Exploring, a held direction walks cell by cell; in dialogs and the battle menu it moves the focus between
// buttons; on the battlefield it moves a cell cursor, and confirm taps that cell.
let battleCursor=null;
const DIRS={ArrowUp:0,KeyW:0,ArrowDown:1,KeyS:1,ArrowLeft:2,KeyA:2,ArrowRight:3,KeyD:3};
function keysUsed(){document.body.classList.add('keys');}
function focusables(host){return [...host.querySelectorAll('button,[tabindex="0"]')].filter(b=>!b.disabled&&b.offsetParent&&getComputedStyle(b).visibility!=='hidden');}
function moveFocus(host,dir){const list=focusables(host);if(!list.length)return false;const cur=list.includes(document.activeElement)?document.activeElement:null;if(!cur){list[0].focus();return true;}
  const r=cur.getBoundingClientRect(),cx=r.left+r.width/2,cy=r.top+r.height/2,[vx,vy]=[[0,-1],[0,1],[-1,0],[1,0]][dir];let best=null;
  for(const b of list){if(b===cur)continue;const q=b.getBoundingClientRect(),dx=q.left+q.width/2-cx,dy=q.top+q.height/2-cy,along=dx*vx+dy*vy;if(along<=4)continue;const score=along+Math.abs(dx*vy-dy*vx)*2.5;if(!best||score<best[0])best=[score,b];}
  best?.[1].focus();return true;}
function battleCursorMove(dir){if(!battle)return;if(!battleCursor){const u=battle.unit(battle.selectedId)??battle.units.find(u=>u.team==='player'&&u.hp>0);battleCursor={x:u?.x??0,y:u?.y??0};}
  else{battleCursor.x=Math.max(0,Math.min(map.widthTiles-1,battleCursor.x+[0,0,-1,1][dir]));battleCursor.y=Math.max(0,Math.min(map.heightTiles-1,battleCursor.y+[-1,1,0,0][dir]));}
  Object.assign(battleView,{x:battleCursor.x*32,y:battleCursor.y*32,dragged:true});}
function inputDirection(dir,down){keysUsed();
  if(!down){if(stickDirection===dir){stickDirection=null;}return;}
  if(tapLayer())return;const wm=document.querySelector('.worldmap');if(wm){moveFocus(wm,dir);return;}
  if(modalStack.length){moveFocus($('modalHost'),dir);return;}
  if(dialogue)return;
  const menu=$('unitMenu');if(battle&&menu&&!menu.hidden){moveFocus(menu,dir);return;}
  if(battle&&onBattlefield()){battleCursorMove(dir);return;}
  if(stickDirection!==dir){stickDirection=dir;stepStick();}}
// Full-screen "tap to continue" layers (level-up, battle result, reward, ending) take any confirm or cancel key; the world
// map takes the arrows to move between places.
function tapLayer(){return document.querySelector('.levelup-veil,.result,.reward-card,.ending');}
function dismissLayer(){const l=tapLayer();if(!l)return false;l.dispatchEvent(new PointerEvent('pointerup',{bubbles:true}));return true;}
function inputConfirm(){keysUsed();if(dismissLayer())return;const wm=document.querySelector('.worldmap');if(wm){const a=document.activeElement;if(a&&wm.contains(a))a.click();else moveFocus(wm,1);return;}
  if(dialogue){advanceDialogue();return;}
  const active=document.activeElement;
  if(modalStack.length){if(active&&$('modalHost').contains(active)&&active!==document.body)active.click();else moveFocus($('modalHost'),1);return;}
  const menu=$('unitMenu');if(battle&&menu&&!menu.hidden&&active&&menu.contains(active)){active.click();return;}
  if(battle&&onBattlefield()){if(!battleCursor)return battleCursorMove(1);battleTap(battleCursor.x,battleCursor.y);setTimeout(()=>{const m=$('unitMenu');if(m&&!m.hidden)moveFocus(m,1);},60);return;}
  interactFront();}
function inputCancel(){keysUsed();if(dismissLayer())return;const wm=document.querySelector('.worldmap');if(wm){wm.querySelector('.wm-close:not([hidden])')?.click();return;}
  if(modalStack.length){closeModal();return;}
  if(dialogue){advanceDialogue();return;}
  if(battle){if(selectedSkill!=null)selectedSkill=null;else if(moveMode)moveMode=false;else battle.selectedId=null;attackMenuOpen=false;updateBattle();return;}
  showPanel('menu');}
document.addEventListener('keydown',e=>{if(e.target.closest?.('input,textarea,select'))return;
  if(e.code in DIRS||e.key in DIRS){e.preventDefault();if(!e.repeat||battle||modalStack.length)inputDirection(DIRS[e.code]??DIRS[e.key],true);return;}
  if(e.key==='Enter'||e.key===' '||e.code==='KeyZ'){e.preventDefault();if(!e.repeat)inputConfirm();return;}
  if(e.key==='Escape'||e.key==='Backspace'||e.code==='KeyX'){e.preventDefault();inputCancel();}},true);
document.addEventListener('keyup',e=>{if(e.code in DIRS||e.key in DIRS)inputDirection(DIRS[e.code]??DIRS[e.key],false);});
// Game pads: polled each frame; directions repeat while held (fast enough to walk, slower for cursors and menus).
{const prev={};let held=null,next=0;
  (function poll(t){const pad=[...(navigator.getGamepads?.()??[])].find(Boolean);if(pad){const b=i=>!!pad.buttons[i]?.pressed,ax=pad.axes[0]??0,ay=pad.axes[1]??0;
      const dir=b(12)||ay<-.6?0:b(13)||ay>.6?1:b(14)||ax<-.6?2:b(15)||ax>.6?3:null;
      if(dir!==held){if(held!=null)inputDirection(held,false);held=dir;if(dir!=null){inputDirection(dir,true);next=t+380;}}else if(dir!=null&&t>next&&(battle||modalStack.length)){inputDirection(dir,true);next=t+150;}
      for(const [i,fn] of [[0,inputConfirm],[1,inputCancel],[9,()=>{keysUsed();if(!modalStack.length&&!dialogue)showPanel('menu');}]]){if(b(i)&&!prev[i])fn();prev[i]=b(i);}}
    requestAnimationFrame(poll);})(0);}
// On-screen pad of the 方向按键 mode.
for(const [id,dir] of [['dpadUp',0],['dpadDown',1],['dpadLeft',2],['dpadRight',3]]){const el=$(id);if(!el)continue;
  el.addEventListener('pointerdown',e=>{e.preventDefault();el.setPointerCapture(e.pointerId);inputDirection(dir,true);if(battle||modalStack.length){el.repeat=setInterval(()=>inputDirection(dir,true),170);}});
  for(const t of ['pointerup','pointercancel','lostpointercapture'])el.addEventListener(t,()=>{clearInterval(el.repeat);inputDirection(dir,false);});}
$('dpadOk')?.addEventListener('click',()=>inputConfirm());$('dpadBack')?.addEventListener('click',()=>inputCancel());
canvas.addEventListener('pointerdown',()=>{document.body.classList.remove('keys');battleCursor=null;});   // touching the map hands control back to taps
updateControls();
