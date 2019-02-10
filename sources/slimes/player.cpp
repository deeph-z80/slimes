#include "camera.h"
#include "constants.h"
#include "map.h"
#include "npc.h"
#include "player.h"
#include "scripts.h"
#include "sprites.h"

void player_::draw() {
  player_sprite_set.setFrame(direction * 3 + animation);
  gb.display.drawImage(x * TILE_WIDTH - camera.x + x_offset, y * TILE_HEIGHT - camera.y + y_offset, player_sprite_set);
}

void player_::update() {
  uint8_t temp;
  if (!is_moving) {
    x_velocity = y_velocity = 0;
    x_velocity = -gb.buttons.repeat(BUTTON_LEFT, 1) * (x > 0) + gb.buttons.repeat(BUTTON_RIGHT, 1) * (x < current_map.width - 1);
    y_velocity = -gb.buttons.repeat(BUTTON_UP, 1) * (y > 0) + gb.buttons.repeat(BUTTON_DOWN, 1) * (y < current_map.height - 1);
    if (!x_velocity != !y_velocity) {
      direction = (1 + x_velocity) * (x_velocity != 0);
      direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);

      // check for objects to collide
      for (uint8_t i = 0; i < current_map.objects_amount; i++) {
        if (x + x_velocity == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + X] & y + y_velocity == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + Y]
            & get_flag(current_map.objects_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
           ) return;
      }

      // check for npc to collide
      for (uint8_t i = 0; i < current_map.npc_amount; i++) {
        if (x + x_velocity == npc[i].x + npc[i].x_velocity * npc[i].is_moving & y + y_velocity ==  npc[i].y + npc[i].y_velocity * npc[i].is_moving
            & get_flag(current_map.npc_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
           ) return;
      }

      // check for tiles to collide
      if (current_map.map_buffer[(y + y_velocity) * current_map.width + x + x_velocity] < current_map.tiles_block_id) is_moving = true;
    } else if (gb.buttons.pressed(BUTTON_A)) {

      // check for objects to interact
      for (uint8_t i = 0; i < current_map.objects_amount; i++) {
        if (x + (direction == 0) - (direction == 2) == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + X] & y + (direction == 3) - (direction == 1) == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + Y]
            & get_flag(current_map.objects_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
           ) {
          current_map.file.seek(current_map.objects_position);
          current_map.get_data(current_map.objects_buffer[i * LENGTH_TABLE_SIZE + ID_]);
          temp = current_map.file.read() - 1; // skip sprite
          current_map.file.read(); // skip sprite id
          current_map.file.read(scripts_buffer, temp);
          run_script(temp);
          return;
        }
      }

      // check for npc to interact
      for (uint8_t i = 0; i < current_map.npc_amount; i++) {
        if (x + (direction == 0) - (direction == 2) == npc[i].x + npc[i].x_velocity * npc[i].is_moving & y + (direction == 3) - (direction == 1) ==  npc[i].y + npc[i].y_velocity * npc[i].is_moving
            & get_flag(current_map.npc_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
           ) {
          current_map.file.seek(current_map.npc_position);
          current_map.get_data(current_map.npc_buffer[i * LENGTH_TABLE_SIZE + ID_]);
          temp = current_map.file.read() - 3; // skip sprite id, direction & movement
          current_map.file.read(); // skip sprite id
          current_map.file.read(); // skip direction
          current_map.file.read(); // skip movement
          current_map.file.read(scripts_buffer, temp);
          run_script(temp);
          return;
        }
      }
    }
  } else {
    scrolling++;
    animation += scrolling % 2;
    animation *= animation < 3 && scrolling < TILE_SIZE;
    x_offset += x_velocity;
    y_offset += y_velocity;
    if (scrolling == TILE_SIZE) {
      scrolling = x_offset = y_offset = 0;
      is_moving = false;
      x += x_velocity;
      y += y_velocity;

      // check for walk-triggered events
      for (byte i = 0; i < current_map.events_amount; i++) {
        if (x == current_map.events_buffer[i * LENGTH_TABLE_SIZE + X] && y == current_map.events_buffer[i * LENGTH_TABLE_SIZE + Y]
            & get_flag(current_map.events_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false) {
          current_map.file.seek(current_map.events_position);
          current_map.get_data(current_map.events_buffer[i * LENGTH_TABLE_SIZE + ID_]);
          temp = current_map.file.read();
          current_map.file.read(scripts_buffer, temp);
          run_script(temp);
          return;
        }
      }
    }
  }
}

bool player_::get_flag(uint8_t id) {
  if (id == NO_FLAG) return false;
  return (bool)flags[id / 8] & (1 << (id % 8));
}

void player_::set_flag(uint8_t id, bool value) {
  if (id == NO_FLAG) return;
  flags[id / 8] |= value << (id % 8);
}

player_ player;
