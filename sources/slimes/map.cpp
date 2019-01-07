#include "camera.h"
#include "map.h"
#include "sprites.h"

uint8_t map_buffer[MAP_BUFFER_SIZE];
uint8_t events_buffer[MAX_EVENTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
uint8_t objects_buffer[MAX_OBJECTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
uint8_t npc_buffer[MAX_NPC_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
char file_name[FILE_NAME_BUFFER_SIZE];

void map_::draw() {
  for (byte x = 0; x <= gb.display.width() / TILE_WIDTH + 1; x++) {
    for (byte y = 0; y <= gb.display.height() / TILE_HEIGHT + 1; y++) {
      int8_t tile_x = camera.x / TILE_WIDTH + x;
      int8_t tile_y = camera.y / TILE_HEIGHT + y;
      //if (tile_x >= 0 && tile_x < width && tile_y >= 0 && tile_y < height) {
      byte tile_id = data[tile_y * width + tile_x];
      tile_id += (tile_id >= tiles_anim_start_id && tile_id <= tiles_anim_end_id) * millis() / TILE_ANIMATION_FREQUENCY % 2;
      gb.display.drawImage(x * TILE_WIDTH - camera.x % TILE_WIDTH, y * TILE_HEIGHT - camera.y % TILE_HEIGHT, tileset, 0, tile_id * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

      // check for objects to draw
      for (byte i = 0; i < current_map.objects_amount; i++) {
        if (tile_x == current_map.objects[i * LENGTH_TABLE_SIZE + X] && tile_y == current_map.objects[i * LENGTH_TABLE_SIZE + Y]
        //&& flag(current_map.objects[i * LENGTH_TABLE_SIZE + FLAG]) == FALSE) {
        ){
          seek_table(current_map.objects[i * LENGTH_TABLE_SIZE + ID]);
          file.read(); // skip length
          objects_sprite_set.setFrame(file.read());
          gb.display.drawImage(x * TILE_WIDTH - camera.x % TILE_WIDTH, y * TILE_HEIGHT - camera.y % TILE_HEIGHT, objects_sprite_set);
          break;
        }
      }
      //}
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
  data = map_buffer;
  events_amount = file.read();
  if (events_amount > 0) {
    file.read(events_buffer, events_amount * LENGTH_TABLE_SIZE);
    events = events_buffer;
    events_position = file.position();
    seek_table(events_amount);
  }
  objects_amount = file.read();
  if (objects_amount > 0) {
    file.read(objects_buffer, objects_amount * LENGTH_TABLE_SIZE);
    objects = objects_buffer;
    objects_position = file.position();
  }
  npc_amount = file.read();
  if (npc_amount > 0) {
    file.read(npc_buffer, npc_amount * LENGTH_TABLE_SIZE);
    npc = npc_buffer;
    npc_position = file.position();
  }
  file.close();
  String("sprites/" + String(tileset_id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  tileset.init(TILE_WIDTH, TILE_HEIGHT * tiles_amount, file_name, 0);
  if (last_music != music_id) {
    // todo : add fading
    String("musics/" + String(music_id) + ".wav").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
    gb.sound.stop(music);
    music = gb.sound.play(file_name, true);
  }
}

void map_::seek_table(uint8_t times) {
  for (byte i = 0; i < times; i++) {
    uint8_t length = file.read();
    file.seek(file.position() + length);
  }
}

map_ current_map;
