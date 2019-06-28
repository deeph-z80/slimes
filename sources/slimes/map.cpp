#include "camera.h"
#include "constants.h"
#include "map.h"
#include "npc.h"
#include "player.h"
#include "sprites.h"

uint8_t music;

void map_::draw() {
  for (uint8_t x = 0; x <= gb.display.width() / TILE_WIDTH + 1; x++) {
    for (uint8_t y = 0; y <= gb.display.height() / TILE_HEIGHT + 1; y++) {
      int8_t tile_x = camera.x / TILE_WIDTH + x;
      int8_t tile_y = camera.y / TILE_HEIGHT + y;
      byte tile_id = map_buffer[tile_y * width + tile_x];
      tile_id += (tile_id >= tiles_anim_start_id && tile_id <= tiles_anim_end_id) * gb.frameCount / TILE_ANIMATION_FREQUENCY % 2;
      gb.display.drawImage(x * TILE_WIDTH - camera.x % TILE_WIDTH, y * TILE_HEIGHT - camera.y % TILE_HEIGHT, tileset, 0, tile_id * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
    }
  }

  // check for objects to draw
  for (uint8_t i = 0; i < objects_amount; i++) {
    if (player.get_flag(objects_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false) {
      file.seek(objects_position);
      get_data(objects_buffer[i * LENGTH_TABLE_SIZE + ID_]);
      file.read(); // skip length
      objects_sprite_set.setFrame(file.read());
      gb.display.drawImage(objects_buffer[i * LENGTH_TABLE_SIZE + X] * TILE_WIDTH - camera.x, objects_buffer[i * LENGTH_TABLE_SIZE + Y] * TILE_HEIGHT - camera.y, objects_sprite_set);
    }
  }

  // check for npc to draw
  for (uint8_t i = 0; i < npc_amount; i++) {
    if (player.get_flag(npc[i].flag) == false) {
    npc_sprite_set.setFrame(npc[i].sprite_id * NPC_SPRITES_LENGTH + (npc[i].direction * 3 + npc[i].animation));
    gb.display.drawImage(npc[i].x * TILE_WIDTH - camera.x + npc[i].x_offset, npc[i].y * TILE_HEIGHT - camera.y + npc[i].y_offset, npc_sprite_set);
    }
  }
}

void map_::load(uint8_t map_id) {
  uint8_t last_music = music_id;
  String("maps/" + String(map_id) + ".map").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  file = SD.open(file_name, O_RDWR);
  id = map_id;
  width = file.read();
  height = file.read();
  tileset_id = file.read();
  tiles_amount = file.read();
  tiles_block_id = file.read();
  tiles_anim_start_id = file.read();
  tiles_anim_end_id = file.read();
  music_id = file.read();
  file.read(map_buffer, width * height);
  events_amount = file.read();
  if (events_amount > 0) {
    file.read(events_buffer, events_amount * LENGTH_TABLE_SIZE);
    events_position = file.position();
    get_data(events_amount);
  }
  objects_amount = file.read();
  if (objects_amount > 0) {
    file.read(objects_buffer, objects_amount * LENGTH_TABLE_SIZE);
    objects_position = file.position();
    get_data(objects_amount);
  }
  npc_amount = file.read();
  if (npc_amount > 0) {
    file.read(npc_buffer, npc_amount * LENGTH_TABLE_SIZE);
    npc_position = file.position();
    for (byte i = 0; i < npc_amount; i++) {
      npc[i].id = npc_buffer[i * LENGTH_TABLE_SIZE + ID_];
      npc[i].flag = npc_buffer[i * LENGTH_TABLE_SIZE + FLAG];
      npc[i].x = npc_buffer[i * LENGTH_TABLE_SIZE + X];
      npc[i].y = npc_buffer[i * LENGTH_TABLE_SIZE + Y];
      file.seek(npc_position);
      get_data(npc[i].id);
      file.read(); // skip length
      npc[i].sprite_id = file.read();
      npc[i].direction = file.read();
      npc[i].animation = 0;
      npc[i].is_moving = false;
    }
  }
  //file.close();
  String("sprites/" + String(tileset_id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  tileset.init(TILE_WIDTH, TILE_HEIGHT * tiles_amount, file_name, 0);
  if (last_music != music_id) {
    // todo : add fading
    String("musics/" + String(music_id) + ".wav").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
    gb.sound.stop(music);
    music = gb.sound.play(file_name, true);
  }
}

void map_::get_data(uint8_t id) {
  for (byte i = 0; i < id; i++) {
    uint8_t length = file.read();
    file.seek(file.position() + length);
  }
}

map_ current_map;
