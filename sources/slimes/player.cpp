#include "camera.h"
#include "constants.h"
#include "map.h"
#include "player.h"
#include "sprites.h"

void player_::draw() {
  player_sprite_set.setFrame(direction * 3 + animation);
  gb.display.drawImage(x * TILE_WIDTH - camera.x + x_offset, y * TILE_HEIGHT - camera.y + y_offset, player_sprite_set);
}

void player_::update() {
  if (!is_moving) {
    x_velocity = y_velocity = 0;
    x_velocity = -gb.buttons.repeat(BUTTON_LEFT, 1) * (x > 0) + gb.buttons.repeat(BUTTON_RIGHT, 1) * (x < current_map.width - 1);
    y_velocity = -gb.buttons.repeat(BUTTON_UP, 1) * (y > 0) + gb.buttons.repeat(BUTTON_DOWN, 1) * (y < current_map.height - 1);
    if (!x_velocity != !y_velocity) {
      direction = (1 + x_velocity) * (x_velocity != 0);
      direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);
      if (current_map.data[(y + y_velocity) * current_map.width + x + x_velocity] < current_map.tiles_block_id) is_moving = true;
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
        if (x == current_map.events[i * LENGTH_TABLE_SIZE + X] && y == current_map.events[i * LENGTH_TABLE_SIZE + Y]) {
          String("maps/" + String(current_map.id) + ".map").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
          current_map.file = SD.open(file_name, O_RDWR);
          current_map.file.seek(current_map.events_position);
          current_map.seek_table(current_map.events[i * LENGTH_TABLE_SIZE + ID_]);
          current_map.file.read(); // skip length
          switch (current_map.file.read()) {
            case WARP:
              //fade.in
              player.x = current_map.file.read();
              player.y = current_map.file.read();
              player.direction = current_map.file.read();
              player.animation = 0;
              player.is_moving = false;
              current_map.load(current_map.file.read());
              //fade.out
              break;
            default:
              gb.display.clear();
              gb.display.setCursor(0, 0);
              gb.display.println(current_map.file.position());
              delay(10000);
          }
          current_map.file.close();
          break;
        }
      }
    }
  }
}

player_ player;
