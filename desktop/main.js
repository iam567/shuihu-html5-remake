// Windows / Mac shell: the same HTML5 build as the web version (dist/, packed as www/ by build.mjs), served from a
// privileged app:// scheme so ES modules, fetch() and localStorage behave as on a web origin; nothing is downloaded.
// Same idea as the iOS and Android shells.
const {app,BrowserWindow,protocol,net,Menu}=require('electron');
const path=require('path'),{pathToFileURL}=require('url');

protocol.registerSchemesAsPrivileged([{scheme:'app',privileges:{standard:true,secure:true,supportFetchAPI:true,stream:true,corsEnabled:true}}]);
const ROOT=path.join(__dirname,'www');

function createWindow(){
  const win=new BrowserWindow({width:1280,height:800,minWidth:480,minHeight:360,backgroundColor:'#000000',title:'水浒传',autoHideMenuBar:true,
    webPreferences:{autoplayPolicy:'no-user-gesture-required',backgroundThrottling:true}});
  win.loadURL('app://game/index.html');
  // F11 / Ctrl+Cmd+F full screen; the window remembers nothing else.
  win.webContents.on('before-input-event',(e,input)=>{if(input.type==='keyDown'&&input.key==='F11'){win.setFullScreen(!win.isFullScreen());e.preventDefault();}});
  // Stop the music when the window is minimised, resume when it comes back (the page also listens to visibilitychange).
  win.on('minimize',()=>win.webContents.executeJavaScript('window.shuihuPause&&window.shuihuPause()'));
  win.on('restore',()=>win.webContents.executeJavaScript('window.shuihuResume&&window.shuihuResume()'));
}

app.whenReady().then(()=>{
  protocol.handle('app',req=>{
    let p=decodeURIComponent(new URL(req.url).pathname);if(!p||p.endsWith('/'))p+='index.html';
    const file=path.normalize(path.join(ROOT,p));
    if(!file.startsWith(ROOT+path.sep))return new Response('Not Found',{status:404});
    return net.fetch(pathToFileURL(file).toString());
  });
  if(process.platform!=='darwin')Menu.setApplicationMenu(null);
  createWindow();
  app.on('activate',()=>{if(BrowserWindow.getAllWindows().length===0)createWindow();});
});
app.on('window-all-closed',()=>app.quit());
