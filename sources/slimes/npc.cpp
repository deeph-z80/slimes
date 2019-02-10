#include "constants.h"
#include "map.h"
#include "npc.h"
#include "player.h"

void npc_::update() {
  // penser à checker movement (si le npc est static ou pas) & le flag
  if (!is_moving) {
    if(gb.frameCount % NPC_MOVE_FREQUENCY == 0){
      x_velocity = y_velocity = 0;
      x_velocity = random(-1, 2) * (x > 0) * (x < current_map.width - 1);
      y_velocity = random(-1, 2) * (y > 0) * (y < current_map.height - 1);
      if (!x_velocity != !y_velocity) {
        direction = (1 + x_velocity) * (x_velocity != 0);
        direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);

        // check for the player to collide
        if (x + x_velocity == player.x + player.x_velocity * player.is_moving & y + y_velocity ==  player.y + player.y_velocity * player.is_moving) return;

        // check for walk-triggered events to collide
        for (uint8_t i = 0; i < current_map.events_amount; i++) {
          if (x + x_velocity == current_map.events_buffer[i * LENGTH_TABLE_SIZE + X] & y + y_velocity == current_map.events_buffer[i * LENGTH_TABLE_SIZE + Y]
              & player.get_flag(current_map.events_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
             ) return;
        }

        // check for objects to collide
        for (uint8_t i = 0; i < current_map.objects_amount; i++) {
          if (x + x_velocity == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + X] & y + y_velocity == current_map.objects_buffer[i * LENGTH_TABLE_SIZE + Y]
              & player.get_flag(current_map.objects_buffer[i * LENGTH_TABLE_SIZE + FLAG]) == false
             ) return;
        }
  
        // check for other npc to collide
        for (uint8_t i = 0; i < current_map.npc_amount; i++) {
          if (x + x_velocity == npc[i].x + npc[i].x_velocity * npc[i].is_moving & y + y_velocity ==  npc[i].y + npc[i].y_velocity * npc[i].is_moving
              & player.get_flag(current_map.npc_buffer[i * LENGTH_TABLE_SIZE + FLAG]
              & id != npc[i].id) == false
             ) return;
        }

        // check for tiles to collide
        if (current_map.map_buffer[(y + y_velocity) * current_map.width + x + x_velocity] < current_map.tiles_block_id) is_moving = true;
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
    }
  }
}

npc_ npc[MAX_NPC_AMOUNT];
