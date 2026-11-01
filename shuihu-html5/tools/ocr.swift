import Foundation
import Vision
import AppKit
let paths=Array(CommandLine.arguments.dropFirst())
for path in paths {
 autoreleasepool {
 do {
  let req=VNRecognizeTextRequest();req.recognitionLevel = .accurate;req.recognitionLanguages=["zh-Hant","zh-Hans","en-US"];req.usesLanguageCorrection=false
  let handler=VNImageRequestHandler(url:URL(fileURLWithPath:path));try handler.perform([req])
  let lines=(req.results ?? []).compactMap { obs -> [String:Any]? in
   guard let t=obs.topCandidates(1).first else{return nil}
   return ["text":t.string,"confidence":t.confidence,"box":[obs.boundingBox.minX,obs.boundingBox.minY,obs.boundingBox.width,obs.boundingBox.height]]
  }
  let json=try JSONSerialization.data(withJSONObject:["path":path,"lines":lines],options:[.sortedKeys]);print(String(data:json,encoding:.utf8)!)
 }catch{fputs("OCR error: \(error)\n",stderr)}
 }
}
