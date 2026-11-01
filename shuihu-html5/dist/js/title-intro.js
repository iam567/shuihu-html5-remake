// Title sequence, after the cartridge's own attract intro (captured from the ROM): a starry night on which the opening
// poem of the novel (邵雍, 「紛紛五代亂離間…」) is written column by column from the right; the night lifts onto the
// mountains of Liangshan with cranes flying over the river; 水滸傳 appears in red and burns to gold; then the menu.
// A tap or any key skips to the end; after one full showing the title opens directly on its last frame.
const POEM=['紛紛五代亂離間','一旦雲開復見天','草木百年新雨露','車書萬里舊江山','尋常巷陌陳羅綺','幾處樓台奏管絃','天下太平無事日','鶯花無限日高眠'];
const SEEN_KEY='shuihu.introSeen';

export function playIntro(screen){
  const root=document.createElement('div');root.className='intro';
  root.innerHTML='<div class="intro-sky"></div><div class="intro-stars"></div><img class="intro-land" alt="" src="assets/title/land.webp">'+
    '<div class="intro-cranes"></div><div class="intro-poem" aria-hidden="true"></div><div class="intro-logo"><img class="logo-red" alt="" src="assets/title/logo.webp"><img class="logo-gold" alt="水滸傳" src="assets/title/logo.webp"></div>'+
    '<button class="intro-skip" type="button">跳过</button>';
  screen.prepend(root);
  const poem=root.querySelector('.intro-poem');let k=0;
  for(const line of POEM){const col=document.createElement('span');for(const ch of line){const c=document.createElement('i');c.textContent=ch;c.style.animationDelay=`${.4+k++*.09}s`;col.append(c);}poem.append(col);}
  const cranes=root.querySelector('.intro-cranes');
  for(let i=0;i<7;i++){const c=document.createElement('i');c.style.setProperty('--y',`${18+Math.random()*42}%`);c.style.setProperty('--s',`${.55+Math.random()*.6}`);c.style.animationDelay=`${-Math.random()*16}s, ${-Math.random()*.6}s`;c.style.animationDuration=`${13+Math.random()*9}s, .6s`;cranes.append(c);}
  let timers=[],done=false;
  const at=(ms,cls)=>timers.push(setTimeout(()=>root.classList.add(cls),ms));
  const finish=()=>{if(done)return;done=true;for(const t of timers)clearTimeout(t);root.classList.add('dawn','logo','gold','menu','skipped');screen.classList.add('intro-done');try{localStorage.setItem(SEEN_KEY,'1');}catch{}
    removeEventListener('keydown',onKey,true);};
  const onKey=e=>{if(screen.hidden)return;e.preventDefault();e.stopPropagation();finish();};
  let seen=false;try{seen=localStorage.getItem(SEEN_KEY)==='1';}catch{}
  if(seen){finish();return root;}
  root.classList.add('playing');
  at(5600,'dawn');at(8800,'logo');at(10000,'gold');timers.push(setTimeout(finish,11200));
  root.addEventListener('pointerup',finish);addEventListener('keydown',onKey,true);
  return root;}
