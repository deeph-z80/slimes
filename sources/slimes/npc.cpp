#include "constants.h"
#include "map.h"
#include "npc.h"

void npc_::update() {
  // penser à checker movement
  if (!is_moving) {
    if(gb.frameCount % NPC_MOVE_FREQUENCY == 0){
      x_velocity = y_velocity = 0;
      x_velocity = random(-1, 2) * (x > 0) * (x < current_map.width - 1);
      y_velocity = random(-1, 2) * (y > 0) * (y < current_map.height - 1);
      if (!x_velocity != !y_velocity) {
        direction = (1 + x_velocity) * (x_velocity != 0);
        direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);
        // tester aussi s'il y a un évènement ou le joueur
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
