#!/usr/bin/env python3
"""Build a deterministic production inventory. Does not generate or approve art."""
import hashlib
import json
import struct
from collections import Counter, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DIST = ROOT / 'dist'
STYLES = ('pixel-hd', 'unreal', 'ghibli')
SOURCE_CELL = 32
TARGET_CELL = 128


def digest(data):
    return hashlib.sha256(data).hexdigest()


def stable_hash(value):
    return digest(json.dumps(value, sort_keys=True, separators=(',', ':')).encode())


def image_size(path):
    data = path.read_bytes()
    assert data[:8] == b'\x89PNG\r\n\x1a\n', path
    return struct.unpack('>II', data[16:24])


def build():
    catalog_path = DIST / 'data/catalog.json'
    rules_path = DIST / 'data/tile-rules.json'
    hidden_path = ROOT.parent / 'shuihu-html5/dist/data/hidden-items.json'
    catalog = json.loads(catalog_path.read_text())
    rules = json.loads(rules_path.read_text())
    hidden = json.loads(hidden_path.read_text())['items']
    banks = {i['id']: i for i in catalog['items'] if i['category'] == 'map-banks'}
    maps = {i['details']['mapId']: i for i in catalog['items'] if i['category'] == 'maps'}
    assert set(maps) == set(rules['maps'])
    assert set(banks) == set(rules['banks'])
    usage = defaultdict(list)
    edges = defaultdict(Counter)
    hidden_by_cell = defaultdict(list)
    for reward in hidden:
        hidden_by_cell[(reward['mapId'], reward['x'], reward['y'])].append(reward)
    map_records = []
    for mid, m in sorted(rules['maps'].items()):
        w, h, graphics, logic = m['width'], m['height'], m['graphics'], m['logic']
        assert len(graphics) == len(logic) == w * h
        assert (maps[mid]['width'], maps[mid]['height']) == (w * SOURCE_CELL, h * SOURCE_CELL)
        for index, (tile, code) in enumerate(zip(graphics, logic)):
            x, y = index % w, index // w
            placement = {'mapId': mid, 'cellIndex': index, 'x': x, 'y': y, 'logic': code}
            rewards = hidden_by_cell.get((mid, x, y))
            if rewards:
                placement['hiddenRewards'] = rewards
            usage[(m['bankId'], tile)].append(placement)
            for direction, offset, allowed in [('right', 1, x + 1 < w), ('down', w, y + 1 < h)]:
                if allowed:
                    edges[m['bankId']][(tile, direction, graphics[index + offset])] += 1
        map_records.append({
            'mapId': mid, 'bankId': m['bankId'], 'widthCells': w, 'heightCells': h,
            'originalImage': maps[mid]['image'], 'originalImageSha256': maps[mid]['sha256'],
            'graphicsSha256': stable_hash(graphics), 'logicSha256': stable_hash(logic),
            'sourceData': f'tile-rules.json#/maps/{mid}',
            'hiddenRewardCount': sum(r['mapId'] == mid for r in hidden),
            'acceptance': {'reassembledAllStyles': False, 'entryAndExitReviewed': False,
                           'blockedCellsReviewed': False, 'hiddenRewardsReviewed': False,
                           'dynamicStoryChangesReviewed': False, 'battleMovementReviewed': False},
        })
    bank_records = []
    first_banks = [rules['maps'][m]['bankId'] for m in ('0106', '0100')]
    ordered_banks = sorted(banks, key=lambda b: (first_banks.index(b) if b in first_banks else 2,
                                                -banks[b]['mapCount'], b))
    for order, bid in enumerate(ordered_banks):
        b = banks[bid]
        path = DIST / b['image']
        assert digest(path.read_bytes()) == b['sha256'], f'Original changed: {bid}'
        width, height = image_size(path)
        assert width % SOURCE_CELL == height % SOURCE_CELL == 0
        cols = width // SOURCE_CELL
        blocks = []
        for tile_string, expected in sorted(rules['banks'][bid].items(), key=lambda p: int(p[0])):
            tile = int(tile_string)
            placements = usage[(bid, tile)]
            assert placements
            assert Counter(str(p['logic']) for p in placements) == Counter(expected['values'])
            assert set(p['mapId'] for p in placements) == set(expected['maps'])
            x, y = tile % cols * SOURCE_CELL, tile // cols * SOURCE_CELL
            assert x + SOURCE_CELL <= width and y + SOURCE_CELL <= height
            block_id = f'{bid}/block-{tile:04d}'
            codes = sorted({p['logic'] for p in placements})
            blocks.append({
                'id': block_id, 'graphicId': tile,
                'sourceRect': {'x': x, 'y': y, 'width': SOURCE_CELL, 'height': SOURCE_CELL},
                'targetRect': {'x': x * 4, 'y': y * 4, 'width': TARGET_CELL, 'height': TARGET_CELL},
                'anchor': 'top-left', 'rotationAllowed': False, 'placementCount': len(placements),
                'mapIds': sorted({p['mapId'] for p in placements}), 'placements': placements,
                'observedLogicCodes': codes,
                'mixedWalkability': any(c < 0x50 for c in codes) and any(c >= 0x50 for c in codes),
                'logicPolicy': 'read-per-map-cell-never-infer-from-image',
                'textReview': {'status': 'required-unclassified', 'containsText': None,
                               'verifiedOriginalText': None, 'renderingPolicy': 'verify-source-then-separate-text-layer-no-AI-guesses'},
                'crossBlockObjectReview': {'status': 'required-unclassified', 'objectGroupIds': [],
                                          'reason': '邻接只能证明拼接关系，不能证明物件边界，需人工圈定完整陶罐、屋顶、门窗等跨格物件。'},
                'deliverables': {style: {'status': 'not_started',
                    'plannedPath': f'art/{style}/{bid}/block-{tile:04d}.png',
                    'width': TARGET_CELL, 'height': TARGET_CELL,
                    'outputSha256': None, 'reviewEvidence': None} for style in STYLES},
            })
        assert len(blocks) == b['details']['metatileCount'], bid
        bank_records.append({
            'id': bid, 'productionOrder': order + 1,
            'batch': '01-opening-room' if order == 0 else '02-opening-town' if order == 1 else '03-shared-banks' if b['mapCount'] > 1 else '04-single-map-banks',
            'sourceAtlas': b['image'], 'sourceSha256': b['sha256'],
            'sourceAtlasSize': [width, height], 'targetAtlasSize': [width * 4, height * 4],
            'atlasColumns': cols, 'mapIds': b['mapIds'], 'blocks': blocks,
            'seamPairs': [{'fromGraphicId': a, 'direction': direction, 'toGraphicId': other,
                           'occurrences': count, 'status': 'pending-review'}
                          for (a, direction, other), count in sorted(edges[bid].items())],
            'textReview': {'status': 'required-unclassified', 'rule': '全组逐块检查招牌和文字；未核对不得ready，不猜测哪些块含字。'},
            'objectGroups': [], 'objectGroupPolicy': '人工确认跨格对象后填入；整组重绘、原边界切回、所有复用场景验收。',
        })
    other = []
    for i in catalog['items']:
        if i['category'] in ('maps', 'map-banks'):
            continue
        other.append({'id': i['id'], 'category': i['category'], 'sourceImage': i['image'],
                      'sourceSha256': i['sha256'], 'sourceSize': [i['width'], i['height']],
                      'status': 'inventoried-not-produced',
                      'policy': 'Unicode文字不作AI字库重绘，原字形留作校对证据' if i['category'] == 'fonts'
                                else '独立生产阶段，人物保持逐帧锚点与动画帧序，界面保持交互区域',
                      'styles': list(STYLES)})
    block_count = sum(len(b['blocks']) for b in bank_records)
    return {
        'schemaVersion': 1, 'title': '水浒传三画风正式素材生产清单',
        'status': 'inventory-only-no-production-assets-approved',
        'styles': [{'id': s, 'label': label} for s, label in zip(STYLES, ['原版高清像素', '虚幻质感', '吉卜力手绘'])],
        'coordinateContract': {'sourceCellPixels': SOURCE_CELL, 'targetCellPixels': TARGET_CELL,
                               'scale': 4, 'worldCellPixels': SOURCE_CELL,
                               'rule': '仅视觉分辨率提升；世界坐标、碰撞、事件、隐藏物品及寻路格不缩放。'},
        'inputs': {'catalogSha256': digest(catalog_path.read_bytes()),
                   'tileRulesSha256': digest(rules_path.read_bytes()),
                   'hiddenItemsSha256': digest(hidden_path.read_bytes())},
        'counts': {'maps': len(map_records), 'banks': len(bank_records), 'uniqueBlocks': block_count,
                   'styleBlockDeliverables': block_count * len(STYLES),
                   'placements': sum(len(v) for v in usage.values()),
                   'seamPairs': sum(len(b['seamPairs']) for b in bank_records),
                   'mixedWalkabilityBlocks': sum(b['mixedWalkability'] for bank in bank_records for b in bank['blocks']),
                   'hiddenRewards': len(hidden), 'otherCatalogAssets': len(other), 'readyDeliverables': 0},
        'excludedConceptSamples': [{'directory': f'samples/{name}', 'status': 'concept-only-not-ready'}
                                  for name in ['jrpg-v1', 'styles-v1', 'town-styles-v1']],
        'acceptanceGates': ['固定图块编号、尺寸、槽位和透明区域', '完整跨格物件分组审核并一同替换',
                            '全组图块文字审核：原招牌文字逐字核对，独立文字层渲染，禁止AI猜字改写',
                            '全部实际相邻边无断裂或色差', '全部复用地图按原图块编号重组',
                            '地图逻辑数组与隐藏点、领取状态不因换肤改变',
                            '门口、通路视觉与实际可通行区域一致', '手机实际显示尺寸可辨认',
                            '动态剧情和兵种地形规则独立验证，未验证不得宣称与原版完全一致'],
        'limitations': ['地图尺寸多数来自静态推断，仍需逐图运行验证。',
                        '战斗兵种与水面通行尚未完全逆向；不可由图片颜色推导规则。',
                        '整图AI输出再切片不能自动保证原位置、边界、跨图复用一致性。',
                        '本文件可重复构建；正式审核状态应存独立制品登记表，不能修改本清单伪装完成。'],
        'banks': bank_records, 'maps': map_records, 'otherAssets': other,
    }


if __name__ == '__main__':
    result = build()
    out = DIST / 'data/art-production.json'
    out.write_text(json.dumps(result, ensure_ascii=False, separators=(',', ':')) + '\n')
    print(json.dumps({'output': str(out), **result['counts']}, ensure_ascii=False))
