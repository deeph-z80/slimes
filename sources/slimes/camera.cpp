#include "camera.h"
#include "map.h"
#include "player.h"

void camera_::update() {
  x = player.x * TILE_SIZE - gb.display.width() / 2 + TILE_WIDTH / 2 + player.x_offset;
  x = camera.x * (x > 0) + (current_map.width * TILE_WIDTH - gb.display.width() - x) * (x > current_map.width * TILE_WIDTH - gb.display.width());
  y = player.y * TILE_SIZE - gb.display.height() / 2 + TILE_HEIGHT / 2 + player.y_offset;
  y = camera.y * (y > 0) + (current_map.height * TILE_HEIGHT - gb.display.height() - y) * (y > current_map.height * TILE_HEIGHT - gb.display.height());
};

camera_ camera;
