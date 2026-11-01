// Enemy and ally AI after the cartridge (enemy 0x7E98-0x9C44, ally copy 0xDBF0-0xE8B8, curses 0xD3D2-0xD8F0). Each unit
// carries its behaviour in its own record: +0x20 the AI mode, +0x22/+0x23 a home cell, +0x26 the weapon it strikes with,
// +0x27 its second item (a heal or a curse for healers and casters) and +0x30.. a list of slots to go after (0xFF ends it).
//   mode 0: walk to the home cell          mode 1: walk after the first living slot on the list
//   mode 2/3: fight; with nobody in reach this turn, 2 goes home (often its own cell: it guards) and 3 follows the list
//   mode 4/5: heal the wounded of its side; with nobody to heal, 4 goes home and 5 follows the list
//   mode 6/7: cures (no unit in the data uses them; they fight instead)
//   mode 8/9: cast its curse; with nobody to curse, 8 goes home and 9 follows the list, striking only what is then in reach
// A list with no living slot left makes the unit keep to its own cell (0x92C2). Before any of that a unit with
// floor(HP*100/max) <= 30 that is not poisoned (the ally copy skips that check) and carries no heal rests for
// floor(maxHP/8) instead (0x7F48), and a confused unit loses its turn (0x7F1C). AI blows spend no uses and earn no
// experience; heals and curses are free too.

const HEAL_AMOUNT = {96: 50, 97: 100};   // 0xA8A0: the AI's own heal by its +0x27 item, anything else heals in full
const STEPS = [[0, -1], [-1, 0], [0, 1], [1, 0]];   // up, left, down, right (0x6986 / 0x9516)

export function runAI(e, id, {hitSuccess}) {
  const u = e.unit(id);
  if (!e._ready(u)) return;
  const raw = u.raw ?? [], mode = raw[0x20] ?? 3, ally = u.team !== 'enemy';
  const done = events => { u.acted = true; u.moved = true; e._checkResult(events); e._emit(events); };
  const pass = () => { if (!u.acted) done([{type: 'wait', unitId: id}]); };   // turn over, no rest heal
  if (u.status[0]) { pass(); return; }
  const second = e.skill(u.equipment[1]);
  if ((ally || !u.status[1]) && Math.floor(u.hp * 100 / u.maxHp) <= 30 && second?.effect_type !== 2) {
    const before = u.hp; u.hp = Math.min(u.maxHp, u.hp + Math.floor(u.maxHp / 8));
    done([{type: 'wait', unitId: id}, ...(u.hp > before ? [{type: 'heal', unitId: id, targetId: id, amount: u.hp - before, targetHp: u.hp, rest: true}] : [])]);
    return;
  }

  const foes = () => e.alive().filter(t => e.side(t) !== e.side(u)).sort((a, b) => a.slot - b.slot);
  const friends = () => e.alive().filter(t => e.side(t) === e.side(u)).sort((a, b) => a.slot - b.slot);
  const spots = () => e.reachable(u.id);   // flood order, own cell first
  const goTo = cell => { if (cell && (cell.x !== u.x || cell.y !== u.y)) e.move(u.id, cell.x, cell.y); };
  const key = c => `${c.x},${c.y}`;

  // Distance field toward a cell over the terrain this unit may cross, ignoring people (0x9516). A cell none of whose
  // neighbours the unit could enter is expanded with the widest terrain limit instead (0x971C).
  const field = goal => {
    const d = new Map([[key(goal), 0]]), q = [goal], wide = {...u, passive: 119};
    const open = (x, y, who) => x >= 0 && y >= 0 && x < e.width && y < e.height && e.passable(x, y, who);
    for (let i = 0; i < q.length; i++) {
      const p = q[i], k = d.get(key(p));
      const who = STEPS.some(([dx, dy]) => open(p.x + dx, p.y + dy, u)) ? u : wide;
      for (const [dx, dy] of STEPS) {
        const x = p.x + dx, y = p.y + dy;
        if (d.has(`${x},${y}`) || !open(x, y, who)) continue;
        d.set(`${x},${y}`, k + 1); q.push({x, y});
      }
    }
    return d;
  };
  // The first cell in flood order holding the highest / lowest value; cells the field does not reach are skipped.
  const pick = (cells, value, high) => {
    let best = null, top = high ? -Infinity : Infinity;
    for (const c of cells) { const v = value(c); if (v == null) continue; if (high ? v > top : v < top) { top = v; best = c; } }
    return best;
  };
  const approach = goal => {
    const d = field(goal), at = pick(spots(), c => d.get(key(c)), false);
    if (at && (d.get(key(at)) ?? Infinity) < (d.get(key(u)) ?? Infinity)) goTo(at);
  };
  const home = () => ({x: raw[0x22] ?? u.x, y: raw[0x23] ?? u.y});
  const chased = () => {
    for (let i = 0x30; i < 0x40; i++) {
      const slot = raw[i];
      if (slot == null || slot === 0xff) break;
      const t = e.slotUnit(slot);
      if (t && t.hp > 0) return {x: t.x, y: t.y};
    }
    return {x: u.x, y: u.y};
  };
  const wander = odd => approach(odd ? chased() : home());

  // Attack choice (0x9192): ((maxHP-HP)*10/maxHP) + class bonus (0x91FE) + 10 when the estimated blow kills
  // + 2 * (blow*10/maxHP) + 5 for slot 0, compared as signed bytes, the first best kept (slot 0 when none beats -1). The
  // estimate (0x920E) is attack + weapon power, scaled by the class matrix and less defence; the cartridge reads the
  // matrix row of slot 0's class (FFE780+0x21) rather than the attacker's.
  const weapon = () => { const s = e.skill(u.equipment[0]); return s && e._kind(s) === 'damage' ? s : null; };
  const slot0 = e.units.find(v => v.slot === 0) ?? u;
  const score = (s, t) => {
    const m1 = s.effect_type === 0 ? 0 : 1, m = e.data.matrix[slot0.classId]?.[t.classId] ?? 0;
    let blow = u.attack[m1] + s.power_or_quantity;
    if (m) blow = Math.floor(blow * m / 10);
    blow = Math.max(0, blow - t.defense[m1]);
    const v = Math.floor((t.maxHp - t.hp) * 10 / t.maxHp) + (e.data.aiClassBonus?.[t.classId] ?? 0) + (blow > t.hp ? 10 : 0)
      + 2 * Math.floor(blow * 10 / t.maxHp) + (t.slot === 0 ? 5 : 0);
    return ((v & 255) ^ 128) - 128;
  };
  const choose = (s, list) => {
    let best = null, top = -1;
    for (const t of list) { const v = score(s, t); if (v > top) { top = v; best = t; } }
    return best ?? list.find(t => t.slot === 0) ?? null;
  };
  const strikeHere = () => {
    const s = weapon(); if (!s) return false;
    const t = choose(s, e.targets(u.id, s.id).sort((a, b) => a.slot - b.slot));
    if (!t) return false;
    return e.useSkill(u.id, s.id, t.id, {ai: true}).ok;
  };
  // Fight (0x82A6 / 0x99FA): pick a target this turn's move can strike; stand on the covering cell with the highest
  // field-from-target + 19, or + 0 when inside the target's own reach (away from its counter, then as far as allowed);
  // then choose again from there. Nobody left in reach after the move: the turn simply ends.
  const fight = () => {
    const s = weapon(); if (!s) return false;
    const cells = spots(), canHit = (c, t) => e.inReach({...u, x: c.x, y: c.y}, t);
    const t = choose(s, foes().filter(t => cells.some(c => canHit(c, t))));
    if (!t) return false;
    const d = field({x: t.x, y: t.y});
    goTo(pick(cells.filter(c => canHit(c, t)), c => { const f = d.get(key(c)); return f == null ? null : f + (e.inReach(t, c) ? 0 : 19); }, true));
    if (!strikeHere()) pass();
    return true;
  };

  // Heal (0x8EEC / 0x9912 / 0x972E): the wounded of its side it can reach a cell to cover this turn, lowest HP first (ties to
  // the later slot); walk to the reachable cell nearest the patient, then heal the lowest in reach from there. Nobody in
  // reach after all: strike if it can, without moving again (0xA718 -> 0xD78E).
  const lowest = list => list.reduce((a, t) => !a || t.hp < a.hp || t.hp === a.hp && t.slot > a.slot ? t : a, null);
  const heal = odd => {
    const pat = e.supportPattern(u); if (!pat) return finish(odd);
    const cells = spots(), wounded = () => friends().filter(t => t.hp < t.maxHp);
    const patient = lowest(wounded().filter(t => cells.some(c => e.covers(pat, c, t))));
    if (!patient) return finish(odd);
    const d = field({x: patient.x, y: patient.y});
    goTo(pick(cells, c => d.get(key(c)), false));
    const t = lowest(wounded().filter(t => e.covers(pat, u, t)));
    if (!t) { if (!strikeHere()) pass(); return; }
    const before = t.hp; t.hp = Math.min(t.maxHp, t.hp + (HEAL_AMOUNT[u.equipment[1]] ?? t.maxHp));
    done([{type: 'heal', unitId: u.id, targetId: t.id, skillId: u.equipment[1], amount: t.hp - before, targetHp: t.hp}]);
  };

  // Curse (0xD3D2 / 0xD688): its +0x27 item's state on a foe that does not already suffer it and scores above 0 — 中毒
  // the highest max HP, 混乱 by the subtype table 0xD46E (0 for 刀客 and a few others: they are never chosen), 虚弱 the
  // highest attack sum, 破甲 the highest defence sum (byte sums) — cast from the reachable cell farthest from it by the
  // terrain field (0xD59C); 平安符 (passive 121) wards it off. Nobody to curse: 8 goes home, 9 follows its list, then it
  // strikes only what is in reach.
  const curse = odd => {
    const s = second, pat = e.cursePattern(u);
    if (!s || s.effect_type < 3 || s.effect_type > 6 || !pat) return false;
    const f = s.effect_type - 3, cells = spots();
    const value = [t => e.data.aiConfuseScore?.[t.subtype - 1] ?? 0, t => t.maxHp, t => (t.attack[0] + t.attack[1]) & 255, t => (t.defense[0] + t.defense[1]) & 255][f];
    let t = null, top = 0;
    for (const c of foes()) if (!c.status[f] && cells.some(p => e.covers(pat, p, c))) { const v = value(c); if (v > top) { top = v; t = c; } }
    if (!t) { finish(odd); return true; }
    const d = field({x: t.x, y: t.y});
    goTo(pick(cells.filter(c => e.covers(pat, c, t)), c => d.get(key(c)), true));
    const hit = t.passive !== 121 && hitSuccess(u, t, s, e.rng);
    if (hit) t.status[f] = 3;
    done([{type: 'status', unitId: u.id, targetId: t.id, skillId: s.id, field: f, duration: 3, hit}]);
    return true;
  };

  // A walk (home, after the list, nobody to heal or curse), then a blow at whatever is in reach; the ally copy does not
  // strike after a mode 0 / 1 walk (0xDFF4).
  function finish(odd) {
    wander(odd);
    if (!(ally && mode <= 1) && strikeHere()) return;
    pass();
  }

  if (mode === 0 || mode === 1) { finish(mode === 1); return; }
  if (mode === 4 || mode === 5) { heal(mode === 5); return; }
  if ((mode === 8 || mode === 9) && curse(mode === 9)) return;
  if (fight()) return;
  finish(mode % 2 === 1);
}
