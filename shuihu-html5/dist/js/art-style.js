/** Visual selection never owns map logic, coordinates, inventory or save state. */
export const ART_STYLES=[{id:'original',name:'原版素材'},{id:'ghibli',name:'吉卜力手绘'},{id:'hd2d',name:'HD-2D 光影'}];
export function normalizeStyle(value){return ART_STYLES.some(s=>s.id===value)?value:'original';}
export function resolveArt(map,style,manifest){
 const candidate=manifest?.styles?.[normalizeStyle(style)]?.maps?.[map.id];
 // Every map uses its whole-map redraw (the user's choice); geometryVerified only says whether the cell check passed,
 // and unverified maps are queued for another redraw rather than shown as the original pixels.
 const ok=candidate?.status==='approved'&&candidate?.signsVerified===true&&candidate?.width===map.widthPixels&&candidate?.height===map.heightPixels&&candidate?.image;
 return ok?{image:candidate.image,scale:candidate.scale??1,fallback:false}:{image:map.image,scale:1,fallback:style!=='original'};
}
export class ArtSelection{
 constructor({storage,manifest={},load}){this.storage=storage;this.manifest=manifest;this.load=load;this.request=0;this.active=null;try{this.style=normalizeStyle(storage?.getItem('shuihu.artStyle'));}catch{this.style='original';}}
 async select(style,map){this.style=normalizeStyle(style);try{this.storage?.setItem('shuihu.artStyle',this.style);}catch{}return this.refresh(map);}
 async refresh(map){const request=++this.request;if(!map){this.active=null;return null;}const visual=resolveArt(map,this.style,this.manifest);let image;
 try{image=await this.load(visual.image);if(!image?.naturalWidth)throw Error('Image unavailable');}catch{image=await this.load(map.image);visual.image=map.image;visual.fallback=true;visual.scale=1;}
 if(request!==this.request)return null;this.active={...visual,bitmap:image,mapId:map.id};return this.active;}
}
