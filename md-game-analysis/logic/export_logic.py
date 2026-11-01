from pathlib import Path
import struct,json,csv
r=Path(__file__).resolve().parents[1]; b=next((r/'baseline').glob('*.md')).read_bytes();o=r/'logic';u16=lambda p:int.from_bytes(b[p:p+2],'big');u32=lambda p:int.from_bytes(b[p:p+4],'big')
ops=[]
names={0:'dialogue_by_id',3:'initialize_12_plus_18_units',4:'pause_for_flag_6019_bit2',5:'spawn_64_byte_unit',6:'camera_follow_spawned_unit',7:'set_spawned_unit_type',8:'camera_follow_selected_unit',16:'pause_for_transition_flag0',17:'pause_for_transition_flag1',18:'set_map_and_spawn_ids',19:'load_map_resources',21:'wait_counter',78:'return_noop',79:'return_noop'}
names.update({24:'set_FF6194_and_call_1AB3E',27:'camera_to_xy_bytes',28:'scripted_movement_xy_speed_flags',29:'dialogue_by_id_at_player',30:'set_animation_speed_word',31:'set_exploration_entity_animation',32:'move_player_direction_word',33:'set_persistent_flag_E200',34:'clear_persistent_flag_E200',35:'load_exploration_entities_variable_records',36:'remove_exploration_entity',37:'battle_map_explicit_dimensions',38:'append_party_member_id',39:'return_from_battle_save_party_fields',40:'set_display_flags_bytes'})
for i in range(80):ops.append({'opcode':i,'hex':f'{i:04x}','handler':f'{u32(0xfd46+4*i):06x}','semantic':names.get(i,'unresolved')})
(o/'script_opcodes.json').write_text(json.dumps(ops,indent=2))
(o/'class_multiplier_15x15.csv').write_text('\n'.join(','.join(map(str,b[0x611e+i*15:0x611e+(i+1)*15])) for i in range(15)))
# Script bank boundaries follow monotonic pointers; shared bank0/1. Relative entry table first offset establishes table size.
banks=[u32(0xe2de2+4*i) for i in range(13)];res=[]
for g,base in enumerate(banks):
 first=u16(base);count=first//2
 entries=[{'index':i,'relative_signed':struct.unpack_from('>h',b,base+2*i)[0],'address':base+struct.unpack_from('>h',b,base+2*i)[0]} for i in range(count)]
 res.append({'group':g,'base':base,'count_inferred_first_offset':count,'entries':entries})
(o/'script_entrypoints.json').write_text(json.dumps(res,indent=2))
# Candidate map-switch patterns bounded to script data banks, not code. Verification is by dimensions and known ids; not fully parsed reachability.
maps=json.loads((o/'maps/maps.json').read_text());ids={int(m['id'],16):m for m in maps};spawns=json.loads((o/'maps/spawn_records.json').read_text());ss={int(s['id'],16):s for s in spawns};c=[]
for p in range(min(banks),0x100000-6,2):
 if u16(p)!=18:continue
 mid,sid=u16(p+2),u16(p+4)
 if mid in ids and sid in ss and ss[sid]['width']*ss[sid]['height']==ids[mid]['layers'][2]['size'] and ss[sid]['width']>0:
  c.append({'script_rom_candidate':p,'map_id':f'{mid:04x}','spawn_id':f'{sid:04x}','width':ss[sid]['width'],'height':ss[sid]['height'],'evidence':'pattern candidate; dimensions corroborated; execution reachability unverified'})
(o/'maps/map_dimensions_candidates.json').write_text(json.dumps(c,indent=2));print('entrypoints',[(x['group'],x['count_inferred_first_offset']) for x in res]);print('map dimension candidates',len(c),len(set(x['map_id'] for x in c)))
# Battle loader opcode 0x25 (handler 0x10A32) carries explicit dimensions rather than spawn ID.
battle=[]
for p in range(min(banks),0x100000-8,2):
 if u16(p)!=0x25:continue
 mid=u16(p+2);w,h=b[p+4:p+6]
 if mid in ids and w*h==ids[mid]['layers'][2]['size'] and w>0:
  battle.append({'script_rom_candidate':p,'map_id':f'{mid:04x}','width':w,'height':h,'camera_x':b[p+6],'camera_y':b[p+7],'evidence':'opcode0025 explicit dimensions, area corroborated, full script reachability unverified'})
(o/'maps/battle_map_dimensions.json').write_text(json.dumps(battle,indent=2));print('battle dimension references',len(battle))
# Additional handler semantics established by focused disassembly. Payload size excludes opcode word.
extra={
0xfe86:('dialogue_id',2),0x1009e:('reset_battle_phase_units',0),0x1011e:('spawn_unit_record',66),0x101ee:('set_spawned_unit_type',2),
0x1051a:('set_map_and_spawn_ids',4),0x1053a:('load_map_resources',0),0x10606:('wait_frames_counter',2),
0x107ee:('camera_to_xy',2),0x10824:('scripted_move_parameters',4),0x10858:('dialogue_at_player',2),0x1093c:('set_animation_speed',2),
0x1094c:('set_exploration_entity_animation',2),0x1097e:('move_player_direction',2),0x10996:('set_persistent_bit',2),0x109bc:('clear_persistent_bit',2),
0x109e2:('load_exploration_entities_until_index_gt15',None),0x10a12:('remove_exploration_entity',2),0x10a32:('load_battle_map_with_dimensions',6),
0x10aa0:('append_party_member',2),0x10ace:('return_to_exploration_and_persist_party',0),0x10b40:('set_display_flags',2),
0x11574:('increment_persistent_counter_E300',2),0x11588:('set_persistent_byte_E600',2),0x11e2a:('spawn_unit_record_alt_faction',66),
0x11ed6:('set_first_party_identity_1515',0),0x11fd2:('play_and_remember_music',2),0x12002:('play_sound_command',2),0x12018:('noop',0)}
for row in ops:
 a=int(row['handler'],16)
 if a in extra:row['semantic'],row['payload_bytes']=extra[a]
(o/'script_opcodes.json').write_text(json.dumps(ops,indent=2))
