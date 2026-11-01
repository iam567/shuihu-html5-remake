// Packs the game for Mac (universal: Apple silicon + Intel) and Windows (x64) into build/*.zip.
// The game is shuihu-html5/dist minus its service worker, copied to www/ with the build number in version.txt, as
// the iOS and Android shells do. The Mac app is signed ad hoc (no Apple Developer ID), so the first launch needs
// right-click > Open; the Windows exe gets its icon and file details from resedit (no Wine needed).
// Usage: npm install && npm run build
import {packager} from '@electron/packager';
import {execFileSync} from 'node:child_process';
import fs from 'node:fs';
import path from 'node:path';
import png2icons from 'png2icons';
import * as ResEdit from 'resedit';

const here=path.dirname(new URL(import.meta.url).pathname),dist=path.join(here,'../shuihu-html5/dist'),out=path.join(here,'build');
const version=fs.readFileSync(path.join(dist,'sw.js'),'utf8').match(/CACHE='shuihu-native-(v\d+)'/)[1];
const run=(cmd,args,cwd=here)=>execFileSync(cmd,args,{cwd,stdio:'inherit'});

fs.rmSync(path.join(here,'www'),{recursive:true,force:true});fs.rmSync(out,{recursive:true,force:true});fs.mkdirSync(out);
run('rsync',['-a','--exclude','sw.js','--exclude','data/playthrough.json',dist+'/','www/']);
fs.writeFileSync(path.join(here,'www/version.txt'),version+'\n');

const png=fs.readFileSync(path.join(here,'../ios/Shuihu/Shuihu/Assets.xcassets/AppIcon.appiconset/icon-1024.png'));
fs.writeFileSync(path.join(out,'icon.icns'),png2icons.createICNS(png,png2icons.BICUBIC,0));
fs.writeFileSync(path.join(out,'icon.ico'),png2icons.createICO(png,png2icons.BICUBIC,0,false,true));

const common={dir:here,out,overwrite:true,name:'水浒传',executableName:'Shuihu',appVersion:'1.0.'+version.slice(1),appCopyright:'水浒传 HTML5 复刻',
  ignore:[/^\/build($|\/)/,/^\/build\.mjs$/,/^\/\.gitignore$/,/^\/node_modules($|\/)/],asar:false};

const [mac]=await packager({...common,platform:'darwin',arch:'universal',icon:path.join(out,'icon.icns'),appBundleId:'pro.areu.shuihu',appCategoryType:'public.app-category.role-playing-games'});
const macApp=path.join(mac,'水浒传.app');
run('codesign',['--force','--deep','--sign','-',macApp]);
run('ditto',['-c','-k','--sequesterRsrc','--keepParent',macApp,path.join(out,`Shuihu-${version}-mac.zip`)]);

const [win]=await packager({...common,platform:'win32',arch:'x64'});
const exePath=path.join(win,'Shuihu.exe'),exe=ResEdit.NtExecutable.from(fs.readFileSync(exePath)),res=ResEdit.NtExecutableResource.from(exe);
const ico=ResEdit.Data.IconFile.from(fs.readFileSync(path.join(out,'icon.ico')));
ResEdit.Resource.IconGroupEntry.replaceIconsForResource(res.entries,1,1033,ico.icons.map(i=>i.data));
const [vi]=ResEdit.Resource.VersionInfo.fromEntries(res.entries);
vi.setStringValues({lang:1033,codepage:1200},{FileDescription:'水浒传',ProductName:'水浒传',CompanyName:'',OriginalFilename:'Shuihu.exe',InternalName:'Shuihu'});
const [a,b,c]=common.appVersion.split('.').map(Number);vi.setFileVersion(a,b,c,0);vi.setProductVersion(a,b,c,0);vi.outputToResourceEntries(res.entries);
res.outputResource(exe);fs.writeFileSync(exePath,Buffer.from(exe.generate()));
fs.renameSync(win,path.join(out,'水浒传-Windows'));
run('zip',['-qry',`Shuihu-${version}-windows.zip`,'水浒传-Windows'],out);

for(const f of fs.readdirSync(out).filter(f=>f.endsWith('.zip')))console.log(f,(fs.statSync(path.join(out,f)).size/1e6).toFixed(0)+' MB');
