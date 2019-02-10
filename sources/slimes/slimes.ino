#include <Gamebuino-Meta.h>

#include "camera.h"
#include "constants.h"
#include "map.h"
#include "menu.h"
#include "npc.h"
#include "player.h"
#include "scripts.h"
#include "sprites.h"
#include "strings.h"

void setup() {
  gb.begin();
  gb.setFrameRate(FPS);
  player.x = 7;
  player.y = 4;
  player.direction = DOWN;
  player.animation = 0;
  player.is_moving = false;
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
 
    while (!gb.update());
  }
}
