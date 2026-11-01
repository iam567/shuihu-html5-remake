package pro.areu.shuihu;

import android.app.Activity;
import android.graphics.Color;
import android.os.Build;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowInsets;
import android.view.WindowInsetsController;
import android.view.WindowManager;
import android.webkit.WebResourceRequest;
import android.webkit.WebResourceResponse;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import java.io.IOException;
import java.io.InputStream;
import java.util.HashMap;
import java.util.Map;

// The game is the same HTML5 build as the web version (dist/, packed as assets/www by build.sh). It is served from
// https://appassets.androidplatform.net/ (the host Android reserves for this) so ES modules, fetch() and localStorage
// behave as on a web origin; nothing is downloaded. Same idea as the iOS shell (ios/Shuihu/Shuihu/ShuihuApp.swift).
public class MainActivity extends Activity {
  private static final String HOST = "appassets.androidplatform.net";
  private static final Map<String, String> TYPES = new HashMap<>();
  static {
    String[][] t = {{"html", "text/html"}, {"js", "text/javascript"}, {"mjs", "text/javascript"}, {"css", "text/css"},
      {"json", "application/json"}, {"webmanifest", "application/manifest+json"}, {"txt", "text/plain"}, {"png", "image/png"},
      {"jpg", "image/jpeg"}, {"webp", "image/webp"}, {"svg", "image/svg+xml"}, {"gif", "image/gif"}, {"mp3", "audio/mpeg"},
      {"ogg", "audio/ogg"}, {"m4a", "audio/mp4"}, {"wav", "audio/wav"}, {"woff2", "font/woff2"}, {"woff", "font/woff"},
      {"ttf", "font/ttf"}, {"otf", "font/otf"}};
    for (String[] p : t) TYPES.put(p[0], p[1]);
  }
  private WebView web;

  @Override protected void onCreate(Bundle state) {
    super.onCreate(state);
    Window w = getWindow();
    w.addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
    if (Build.VERSION.SDK_INT >= 28) w.getAttributes().layoutInDisplayCutoutMode = WindowManager.LayoutParams.LAYOUT_IN_DISPLAY_CUTOUT_MODE_SHORT_EDGES;
    web = new WebView(this);
    web.setBackgroundColor(Color.BLACK);
    WebSettings s = web.getSettings();
    s.setJavaScriptEnabled(true);
    s.setDomStorageEnabled(true);
    s.setMediaPlaybackRequiresUserGesture(false);
    s.setAllowFileAccess(false);
    s.setAllowContentAccess(false);
    web.setWebViewClient(new WebViewClient() {
      @Override public WebResourceResponse shouldInterceptRequest(WebView view, WebResourceRequest req) {
        if (!HOST.equals(req.getUrl().getHost())) return null;
        String path = req.getUrl().getPath();
        if (path == null || path.isEmpty() || path.endsWith("/")) path = (path == null ? "/" : path) + "index.html";
        String ext = path.substring(path.lastIndexOf('.') + 1).toLowerCase();
        Map<String, String> headers = new HashMap<>();
        headers.put("Access-Control-Allow-Origin", "*");
        headers.put("Cache-Control", "no-cache");
        try {
          InputStream in = getAssets().open("www" + path);
          String type = TYPES.containsKey(ext) ? TYPES.get(ext) : "application/octet-stream";
          return new WebResourceResponse(type, type.startsWith("text/") || type.endsWith("json") ? "utf-8" : null, 200, "OK", headers, in);
        } catch (IOException e) {
          return new WebResourceResponse("text/plain", "utf-8", 404, "Not Found", headers, null);
        }
      }
    });
    setContentView(web);
    hideBars();
    web.loadUrl("https://" + HOST + "/index.html");
  }

  private void hideBars() {
    if (Build.VERSION.SDK_INT >= 30) {
      WindowInsetsController c = getWindow().getInsetsController();
      if (c != null) {
        c.hide(WindowInsets.Type.statusBars() | WindowInsets.Type.navigationBars());
        c.setSystemBarsBehavior(WindowInsetsController.BEHAVIOR_SHOW_TRANSIENT_BARS_BY_SWIPE);
      }
    } else {
      getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_FULLSCREEN | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
        | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_LAYOUT_STABLE | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION);
    }
  }

  @Override public void onWindowFocusChanged(boolean focus) { super.onWindowFocusChanged(focus); if (focus) hideBars(); }
  // Stop the music when the app leaves the screen, resume when it comes back.
  @Override protected void onPause() { web.evaluateJavascript("window.shuihuPause&&window.shuihuPause()", null); web.onPause(); super.onPause(); }
  @Override protected void onResume() { super.onResume(); web.onResume(); web.evaluateJavascript("window.shuihuResume&&window.shuihuResume()", null); }
  @Override protected void onDestroy() { web.destroy(); super.onDestroy(); }
}
