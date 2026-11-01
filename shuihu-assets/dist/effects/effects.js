// Visual sprites only; never modifies damage, range, inventory, or turn state.
export const effects=[{id:3,name:'玄鐵劍',kind:'slash'},{id:22,name:'柳木弓',kind:'arrow'},{id:33,name:'蛇尖長矛',kind:'thrust'},{id:46,name:'南蠻火槍',kind:'shot'},{id:65,name:'烈火之書',kind:'fire'}];
export function drawAttack(ctx,sheet,frame,x,y,size=288){ctx.save();ctx.imageSmoothingEnabled=false;frame=Math.max(0,Math.min(15,frame));ctx.drawImage(sheet,frame%4*96,Math.floor(frame/4)*96,96,96,x,y,size,size);ctx.restore();}
export async function mountPreview(article,e){
 const sheet=new Image();sheet.src=new URL(`./sheets/item-${e.id}.svg`,import.meta.url).href;await sheet.decode();
 const canvas=article.querySelector('canvas'),ctx=canvas.getContext('2d'),slider=article.querySelector('input'),label=article.querySelector('output'),button=article.querySelector('button');
 let playing=true,frame=0,last=performance.now(),elapsed=0;
 button.onclick=()=>{playing=!playing;button.textContent=playing?'暂停':'播放';last=performance.now();};
 slider.oninput=()=>{playing=false;frame=Number(slider.value);button.textContent='播放';paint();};
 function paint(){ctx.clearRect(0,0,288,288);ctx.fillStyle='#152b31';ctx.fillRect(0,0,288,288);ctx.fillStyle='#ffffff08';for(let y=0;y<288;y+=24)for(let x=0;x<288;x+=24)if((x+y)/24%2===0)ctx.fillRect(x,y,24,24);drawAttack(ctx,sheet,frame,0,0);slider.value=frame;label.textContent=`第 ${frame+1} / 16 帧`;}
 function tick(now){if(playing){elapsed+=now-last;while(elapsed>=62.5){frame=(frame+1)%16;elapsed-=62.5;}paint();}last=now;requestAnimationFrame(tick);}paint();requestAnimationFrame(tick);
 article.querySelector('.png').onclick=()=>{const c=document.createElement('canvas');c.width=c.height=384;c.getContext('2d').drawImage(sheet,0,0);c.toBlob(blob=>{const url=URL.createObjectURL(blob),a=document.createElement('a');a.href=url;a.download=`item-${e.id}-16-frames.png`;a.click();setTimeout(()=>URL.revokeObjectURL(url),1000);});};
}
