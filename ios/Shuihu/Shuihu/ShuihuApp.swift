import SwiftUI
import WebKit
import UniformTypeIdentifiers

// The game is the same HTML5 build as the web version (dist/, bundled as the "www" folder). It is served from a custom
// scheme (app://game/...) so ES modules, fetch() and localStorage behave as on a web origin; nothing is downloaded.
@main
struct ShuihuApp: App {
  var body: some Scene { WindowGroup { GameView().ignoresSafeArea().statusBarHidden(true).persistentSystemOverlays(.hidden) } }
}

struct GameView: UIViewRepresentable {
  func makeUIView(context: Context) -> WKWebView {
    let config = WKWebViewConfiguration()
    config.setURLSchemeHandler(BundleSchemeHandler(), forURLScheme: "app")
    config.allowsInlineMediaPlayback = true
    config.mediaTypesRequiringUserActionForPlayback = []
    config.websiteDataStore = .default()
    let web = WKWebView(frame: .zero, configuration: config)
    web.isOpaque = false
    web.backgroundColor = .black
    web.scrollView.isScrollEnabled = false
    web.scrollView.bounces = false
    web.scrollView.contentInsetAdjustmentBehavior = .never
    web.load(URLRequest(url: URL(string: "app://game/index.html")!))
    // Stop the music when the app leaves the screen, resume when it comes back.
    let center = NotificationCenter.default
    center.addObserver(forName: UIApplication.willResignActiveNotification, object: nil, queue: .main) { [weak web] _ in
      web?.evaluateJavaScript("window.shuihuPause&&window.shuihuPause()")
    }
    center.addObserver(forName: UIApplication.didBecomeActiveNotification, object: nil, queue: .main) { [weak web] _ in
      web?.evaluateJavaScript("window.shuihuResume&&window.shuihuResume()")
    }
    return web
  }
  func updateUIView(_ uiView: WKWebView, context: Context) {}
}

final class BundleSchemeHandler: NSObject, WKURLSchemeHandler {
  private let root = Bundle.main.resourceURL!.appendingPathComponent("www")
  func webView(_ webView: WKWebView, start task: WKURLSchemeTask) {
    guard let url = task.request.url else { return }
    var path = url.path.isEmpty || url.path == "/" ? "/index.html" : url.path
    if path.hasSuffix("/") { path += "index.html" }
    let file = root.appendingPathComponent(String(path.dropFirst()))
    guard let data = try? Data(contentsOf: file) else {
      task.didReceive(HTTPURLResponse(url: url, statusCode: 404, httpVersion: "HTTP/1.1", headerFields: nil)!)
      task.didFinish(); return
    }
    let mime = UTType(filenameExtension: file.pathExtension)?.preferredMIMEType ?? "application/octet-stream"
    let type = file.pathExtension == "js" || file.pathExtension == "mjs" ? "text/javascript" : mime
    task.didReceive(HTTPURLResponse(url: url, statusCode: 200, httpVersion: "HTTP/1.1",
      headerFields: ["Content-Type": type, "Content-Length": String(data.count), "Access-Control-Allow-Origin": "*"])!)
    task.didReceive(data)
    task.didFinish()
  }
  func webView(_ webView: WKWebView, stop task: WKURLSchemeTask) {}
}
