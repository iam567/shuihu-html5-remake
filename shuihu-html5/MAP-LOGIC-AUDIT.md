# 地图、入口与隐藏物品核验

本报告区分原 ROM 字节核验、隔离脚本执行和原版运行证据。不能据此宣称整部游戏逻辑已与原版完全一致。

- 地图 116 张，地图格 28993 个；图块编号匹配 116 张，通行事件字节匹配 116 张。
- 隐藏地点 39 处，奖励、一次领取、存档恢复检查通过 39 处。
- 地图/事件绑定 286 个，其中踏入事件 91 个；隔离执行解析首个换图 142 个，遇到战斗/选择/异常未解 12 个。
- 兼容性观察 24 项：第6章标志位 bit2 会对小地图有效范围外写入3个位置；原ROM 0x1C7AE..0x1C80A 确实如此，目前保留原逻辑。这些位置不应出现在有效通行网格里。

原 ROM SHA-256：0c97ad517c57cbb8f85e4d0250652e878e0506afb16e5b67440b2e983741279f。故事字节与 ROM 完全相同：true。

## 图块逻辑约束

0 可走；1–79 可走且触发踏入事件；80 阻挡；81–127 阻挡并接触触发；128–175 阻挡并主动调查。美术替换保持每格原始编号和逻辑，不根据颜色或水面外观重推逻辑。战斗地形不能直接用这些探索代码推断。

## 完整地图清单

|地图|尺寸|通行/踏入|阻挡/接触/调查|隐藏|事件未解|
|---|---|---|---|---|---|
|0100|24×20|208/1|0/271/0|0|1|
|0101|10×10|24/2|0/74/0|0|0|
|0102|10×15|63/2|0/85/0|0|0|
|0103|10×10|31/2|0/66/1|1|0|
|0104|10×10|25/2|0/73/0|0|0|
|0105|10×10|25/2|0/73/0|0|0|
|0106|10×10|32/2|0/65/1|1|0|
|0107|10×10|23/2|0/74/1|1|0|
|0200|24×15|210/4|23/123/0|0|2|
|0201|10×10|34/2|0/63/1|1|0|
|0202|10×10|28/4|0/68/0|0|0|
|0203|10×10|36/2|0/61/1|1|0|
|0204|10×10|36/2|0/62/0|0|0|
|0205|10×10|32/2|0/65/1|1|0|
|0206|24×15|273/0|0/87/0|0|0|
|0207|16×23|256/0|0/112/0|0|0|
|0300|32×15|298/2|0/180/0|0|1|
|0301|10×10|25/2|0/73/0|0|0|
|0302|10×10|25/2|0/72/1|1|0|
|0303|10×10|34/4|0/62/0|0|0|
|0304|10×10|33/1|0/66/0|0|0|
|0305|10×10|26/1|0/72/1|1|0|
|0306|10×10|21/2|0/77/0|0|0|
|0307|24×25|350/0|0/250/0|0|0|
|0308|13×25|188/3|0/134/0|0|0|
|0309|12×30|223/0|0/137/0|0|0|
|0400|16×28|207/2|0/238/1|0|1|
|0401|10×10|25/2|0/73/0|0|0|
|0402|10×10|26/2|0/71/1|1|0|
|0403|10×10|24/2|0/74/0|0|0|
|0404|12×12|51/2|0/90/1|1|0|
|0405|10×12|48/2|0/70/0|0|0|
|0406|10×10|31/2|0/67/0|0|0|
|0407|10×10|34/2|0/63/1|1|0|
|0408|24×15|201/0|0/159/0|0|0|
|0409|24×20|351/0|53/76/0|0|0|
|0500|24×18|175/3|0/254/0|0|0|
|0501|10×10|30/2|67/0/1|1|0|
|0502|10×10|30/2|67/0/1|1|0|
|0503|10×10|28/2|69/0/1|1|0|
|0504|10×10|30/2|68/0/0|0|0|
|0505|10×10|24/2|74/0/0|0|0|
|0506|10×10|28/2|69/0/1|1|0|
|0507|13×25|188/3|0/134/0|0|0|
|0508|24×23|342/0|0/210/0|0|0|
|0509|11×15|64/0|101/0/0|0|0|
|0600|24×15|135/3|0/222/0|0|1|
|0601|10×10|30/2|68/0/0|0|0|
|0602|10×13|53/2|75/0/0|0|0|
|0603|10×10|24/2|74/0/0|0|0|
|0604|10×10|38/2|59/0/1|1|0|
|0605|10×10|29/2|68/0/1|1|0|
|0606|10×10|35/6|59/0/0|0|0|
|0607|10×10|27/2|70/0/1|1|0|
|0608|10×10|24/2|74/0/0|0|0|
|0609|24×17|210/0|0/198/0|0|0|
|0700|16×23|148/2|212/6/0|0|1|
|0701|11×13|52/3|88/0/0|0|0|
|0702|10×10|36/2|61/0/1|1|0|
|0703|10×10|41/2|56/0/1|1|0|
|0704|10×10|26/2|72/0/0|0|0|
|0705|10×10|37/2|60/0/1|1|0|
|0706|10×10|37/2|60/0/1|1|0|
|0707|24×20|294/0|143/43/0|0|0|
|0708|24×25|300/0|0/300/0|0|0|
|0709|32×15|271/0|0/209/0|0|0|
|0800|24×15|138/3|211/7/1|0|1|
|0801|10×10|31/2|66/0/1|1|0|
|0802|10×12|47/2|71/0/0|0|0|
|0803|10×10|25/2|73/0/0|0|0|
|0804|10×10|34/2|64/0/0|0|0|
|0805|10×10|41/2|56/0/1|1|0|
|0806|10×10|34/2|63/0/1|1|0|
|0807|10×10|31/2|66/0/1|1|0|
|0808|15×20|214/0|0/86/0|0|0|
|0809|24×25|289/0|0/311/0|0|0|
|080a|10×10|38/0|62/0/0|0|0|
|080b|10×10|38/0|62/0/0|0|0|
|0900|16×20|148/2|165/5/0|0|1|
|0901|10×13|52/2|76/0/0|0|0|
|0902|10×10|34/2|63/0/1|1|0|
|0903|10×10|36/2|61/0/1|1|0|
|0904|10×10|26/2|72/0/0|0|0|
|0905|10×10|34/2|63/0/1|1|0|
|0906|16×30|313/0|0/167/0|0|0|
|0907|32×20|376/0|239/25/0|0|0|
|0908|24×25|332/0|0/268/0|0|0|
|0a00|15×25|135/3|232/5/0|0|1|
|0a01|10×15|68/2|80/0/0|0|0|
|0a02|10×10|22/2|75/0/1|1|0|
|0a03|10×10|28/2|69/0/1|1|0|
|0a04|10×10|23/2|73/0/2|2|0|
|0a05|10×10|22/2|76/0/0|0|0|
|0a06|24×25|228/0|0/372/0|0|0|
|0a07|11×12|54/0|0/78/0|0|0|
|0a08|24×30|270/0|0/450/0|0|0|
|0b00|16×15|99/2|135/4/0|0|1|
|0b01|10×10|34/2|63/0/1|1|0|
|0b02|10×10|36/2|62/0/0|0|0|
|0b03|10×10|34/2|62/0/2|2|0|
|0b04|10×10|26/2|72/0/0|0|0|
|0b05|32×25|281/0|0/519/0|0|0|
|0b06|24×30|437/0|0/283/0|0|0|
|0b07|24×25|375/0|178/47/0|0|0|
|0b08|32×20|329/0|0/311/0|0|0|
|0b09|24×25|325/0|0/275/0|0|0|
|0b0a|24×30|426/0|0/294/0|0|0|
|0c00|16×13|101/2|102/3/0|0|1|
|0c01|10×10|36/2|61/0/1|1|0|
|0c02|10×10|34/2|62/0/2|2|0|
|0c03|10×10|26/2|72/0/0|0|0|
|0c04|24×30|500/0|0/220/0|0|0|
|0c05|32×20|326/0|0/314/0|0|0|
|0c06|24×25|305/0|0/295/0|0|0|
|0c07|24×30|417/0|0/303/0|0|0|
|0c08|24×20|263/0|0/217/0|0|0|

## 原版兼容性观察

- original-buffer-write-outside-map：地图 0601，{"kind":"original-buffer-write-outside-map","mapId":"0601","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0601，{"kind":"original-buffer-write-outside-map","mapId":"0601","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0601，{"kind":"original-buffer-write-outside-map","mapId":"0601","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0602，{"kind":"original-buffer-write-outside-map","mapId":"0602","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0602，{"kind":"original-buffer-write-outside-map","mapId":"0602","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0602，{"kind":"original-buffer-write-outside-map","mapId":"0602","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0603，{"kind":"original-buffer-write-outside-map","mapId":"0603","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0603，{"kind":"original-buffer-write-outside-map","mapId":"0603","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0603，{"kind":"original-buffer-write-outside-map","mapId":"0603","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0604，{"kind":"original-buffer-write-outside-map","mapId":"0604","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0604，{"kind":"original-buffer-write-outside-map","mapId":"0604","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0604，{"kind":"original-buffer-write-outside-map","mapId":"0604","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0605，{"kind":"original-buffer-write-outside-map","mapId":"0605","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0605，{"kind":"original-buffer-write-outside-map","mapId":"0605","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0605，{"kind":"original-buffer-write-outside-map","mapId":"0605","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0606，{"kind":"original-buffer-write-outside-map","mapId":"0606","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0606，{"kind":"original-buffer-write-outside-map","mapId":"0606","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0606，{"kind":"original-buffer-write-outside-map","mapId":"0606","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0607，{"kind":"original-buffer-write-outside-map","mapId":"0607","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0607，{"kind":"original-buffer-write-outside-map","mapId":"0607","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0607，{"kind":"original-buffer-write-outside-map","mapId":"0607","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0608，{"kind":"original-buffer-write-outside-map","mapId":"0608","index":167,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0608，{"kind":"original-buffer-write-outside-map","mapId":"0608","index":191,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}
- original-buffer-write-outside-map：地图 0608，{"kind":"original-buffer-write-outside-map","mapId":"0608","index":215,"value":13,"exampleFlags":4,"inBounds":false,"evidence":"ROM 0x1C7AE..0x1C80A: non-0600 branches to 0x1C7EA, which still checks chapter flag bit 2 and writes FFD0A7/BF/D7","impact":"Outside active grid; preserve original behavior, do not infer a walkable cell or trim the condition without separate justification"}

## 验证边界

- The same graphic ID can have different per-location logic; never derive collision from artwork.
- Transitions trace fresh state only and stop at the first map load, player choice or battle; later state-dependent branches are not proven.
- Active NPC footprints and story patches alter static collision. Dynamic patch candidates are not proof of reachable flag states.
- Battle terrain, water access by unit class, later battle deployments and stage dispatch remain unverified.
- Only the recorded opening-room runtime capture is cited here; other maps have no claimed full original-runtime traversal.
- Visual geometry/door alignment of generated art requires separate review.

已留存的原版运行对照是开场 0106：图像层一致，逻辑格 84、85 在运行时从 0 改成 0x42，与开场阻止直接出门的剧情状态相符。其余地图未逐间完成原版运行对照。每格坐标、源图块号、原始逻辑、入口目的地图与出生点、39 隐藏点检查和动态改格候选均见 dist/data/map-logic-audit.json。

复现：在项目目录运行 node tools/audit_map_logic.mjs；测试 node --test tests/map-logic.test.mjs。审计需要同级 md-game-analysis 中的基准 ROM，以及 shuihu-assets 中的 tile-rules.json。
