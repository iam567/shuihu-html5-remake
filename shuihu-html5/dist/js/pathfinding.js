export function findPath(start,end,width,height,passable){
 const key=(x,y)=>y*width+x, goal=key(end.x,end.y), open=[{x:start.x,y:start.y,g:0,f:0}], costs=new Map([[key(start.x,start.y),0]]),came=new Map();let scans=0;
 while(open.length&&scans++<width*height*4){open.sort((a,b)=>a.f-b.f||a.g-b.g);const p=open.shift(),k=key(p.x,p.y);if(k===goal){let path=[],cur=k;while(came.has(cur)){path.push({x:cur%width,y:Math.floor(cur/width)});cur=came.get(cur)}return path.reverse()}
 for(const [dx,dy] of [[0,1],[1,0],[0,-1],[-1,0]]){const x=p.x+dx,y=p.y+dy;if(x<0||y<0||x>=width||y>=height||!passable(x,y))continue;const n=key(x,y),g=p.g+1;if(g>=(costs.get(n)??Infinity))continue;costs.set(n,g);came.set(n,k);open.push({x,y,g,f:g+Math.abs(end.x-x)+Math.abs(end.y-y)})}}
 return null;
}
export function adjacentPath(start,end,width,height,passable){let best=null;for(const [dx,dy]of[[0,1],[1,0],[0,-1],[-1,0]]){const p={x:end.x+dx,y:end.y+dy};if(p.x<0||p.y<0||p.x>=width||p.y>=height||!passable(p.x,p.y))continue;const route=findPath(start,p,width,height,passable);if(route!==null&&(!best||route.length<best.length))best=route}return best}
