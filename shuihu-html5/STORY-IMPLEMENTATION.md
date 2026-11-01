# 剧情重写状态

`dist/js/story.js` 只解释已导出的剧情指令。`data/story.json` 保存原剧情数据区 E2E16–EE2CF 的字节、入口、NPC、商店与出生点；不加载 ROM，也不执行 68000 指令。

开场自动化测试覆盖事件 41、42：对白 0、1、2，主角/阿福位移，剧情标志置位，初始房间封门解除，转场地图 0100 / 出生点 0106。`node tools/test_story.mjs` 可重复执行。

385 个不同有效入口中，默认选择及空界面回调的机械执行有 384 个到达终止词；实际触及 69 种指令。这个数字只验证解析、分支与边界，不代表 384 场剧情已逐场视觉验证。全部 80 种指令有分派，包括 78/79 原版空操作。特殊战斗表现、镜头与界面行为交由回调，原版战场外部触发器仍未完整翻译。

唯一机械测试错误：第 12 组事件 48 的地图选择预设目的地 3，取消会选择 FFE3 标签，但原脚本无该标签。重写会明确停止并报告，而不会跳到猜测的位置。

## 已恢复的状态逻辑

- 剧情 flags、NPC 对话计数、地图选择变量、队伍增员、道具/金钱奖励。
- 12 间商店原库存，143 项原价格，卖价向下取半；取消商店不产生状态变化。
- 36 场战斗的原金币奖励。
- 所有章节 1C628–1C896 的地图碰撞条件覆写。
- 所有地图 NPC，隐藏掩码初值，脚本 NPC 隐藏修改。
- 分支标签前后扫描、变量选择；像素移动与格坐标移动，后者 X 轴先走。

## 接入约定

`new StoryVM({data,hooks})`，`setEntities(initial.actors)`，`await start(1,0x41)`。

`save()` / `load(state)` 只在剧情结束后使用，避免重复发奖励。`complete` 回调发生时 `running` 已清零。

`shop` 回调收到 `{shopId,items:[{id,price}],inventory,gold,party,canCancel:true,transact}`；交易通过 `transact({kind:'buy'|'sell',item,count})` 提交，布尔返回表示是否成功。取消直接结束回调。

`choice` 收到 `{kind:'destination',region,current,allowed,canCancel:true}`，返回数字或 `{value}`；`{cancelled:true}` 保留原目的地。

NPC 对话由 `npc-dialogues.json` 的 identities[actor.byte7].variants[counters[identity]] 查找。肖像用 actor.characterId。结束后 scriptId 非空触发同地图组事件。

第一场战斗在组 1 事件 43 末尾 opcode 25 的 `prepareBattle` 回调交接。原 stage 0 的启动事件 45 只有重置行动；失败事件 44 重置战斗；胜利事件 46 是后续长剧情。不得把战斗胜败硬写为 VM selector；原 selector 仅被 0C/29 修改。

## 尚未等价复原

原 12074 表中的 36 个战场逐帧条件调度器（增援、指定人物生死、阶段目标等）未完整重写。当前不能宣称可按原规则完整通关。剧情特效 hook 使用原 opcode 标记，部分表现尚未复现；Battle 模块另有独立复原限制。

首战实际接入使用 mandatory 队伍人物 1/3（249F2）、24A98 坐标与 176EA 初始持久属性，再合并 1CA1A 四敌记录并按 14C80 重算。不是初始化演示记录。原可选第三人部署菜单尚未实现。首战人物1或3死亡即失败，敌军清空胜利；失败可重试或读存档，胜利排队运行事件46。
