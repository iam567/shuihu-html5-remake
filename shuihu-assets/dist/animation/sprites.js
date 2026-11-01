// Runtime background keying preserves generated source PNGs unchanged.
export async function loadSpriteSurface(url){
 const image=new Image();image.src=url;await image.decode();const c=document.createElement('canvas');c.width=image.width;c.height=image.height;const ctx=c.getContext('2d',{willReadFrequently:true});ctx.drawImage(image,0,0);const pixels=ctx.getImageData(0,0,c.width,c.height),d=pixels.data;
 // Match only the dedicated magenta background, never all dark pixels or purple clothes.
 for(let i=0;i<d.length;i+=4){const r=d[i],g=d[i+1],b=d[i+2];if(r>205&&b>205&&g<65&&Math.abs(r-b)<45)d[i+3]=0;}
 ctx.putImageData(pixels,0,0);c.frameBottom=[];for(let row=0;row<3;row++)for(let col=0;col<3;col++){let bottom=0;const x0=Math.round(col*c.width/3),x1=Math.round((col+1)*c.width/3),y0=Math.round(row*c.height/3),y1=Math.round((row+1)*c.height/3);for(let y=y0;y<y1;y++)for(let x=x0;x<x1;x++)if(d[(y*c.width+x)*4+3]>128)bottom=y-y0;c.frameBottom.push(bottom);}return c;
}
export function drawWalk(ctx,surface,direction,step,x,y,size){const row=direction==='front'?0:direction==='back'?1:2;const f=[0,1,0,2][step%4];const w=surface.width/3,h=surface.height/3;y+=size*.9-(surface.frameBottom[row*3+f]+1)*size/h;ctx.save();ctx.imageSmoothingEnabled=false;if(direction==='right'){ctx.translate(x+size,y);ctx.scale(-1,1);ctx.drawImage(surface,f*w,row*h,w,h,0,0,size,size);}else ctx.drawImage(surface,f*w,row*h,w,h,x,y,size,size);ctx.restore();}
