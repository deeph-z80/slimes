#include <Gamebuino-Meta.h>

#include "camera.h"
#include "constants.h"
#include "map.h"
#include "menu.h"
#include "npc.h"
#include "player.h"
#include "scripts.h"
#include "sprites.h"
#include "stats.h"
#include "strings.h"

void setup() {
  gb.begin();
  gb.setFrameRate(FPS);
  player.x = 7;
  player.y = 4;
  player.direction = DOWN;
  player.animation = 0;
  player.is_moving = false;

  // debug
  player.slimes_held[0] = slime{1, 1, 10, 0, 0, {
    { 0, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime }
  }};
  player.slimes_held[1] = slime{0, 1, 4, 0, 0, {
    { 0, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime },
    { NO_DATA, TYPE_GRASS, 10, 1, 0, n_plantslime }
  }};
  player.slimes_held[2].free();
  player.slimes_held[3].free();
  player.slimes_held[4].free();
  player.slimes_held[5].free();

  music = -1;
  current_map.load(0);
}

void loop() {
  while (true) {
    player.update();
    for (byte i = 0; i < current_map.npc_amount; i++) npc[i].update();
    camera.update();
    current_map.draw();
    player.draw();

    // debug
    gb.display.setColor(WHITE);
    gb.display.setCursor(0, 0);
    gb.display.println(gb.getFreeRam());
    gb.display.println(gb.getCpuLoad());
 
    gb.waitForUpdate();
  }
}
