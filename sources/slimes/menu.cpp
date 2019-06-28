#include "constants.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "stats.h"

void draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h){
  gb.display.setColor(WHITE);
  gb.display.fillRect(x, y, w, h);
  gb.display.setColor(BLACK);
  gb.display.drawRect(x, y, w, h);
}

uint8_t menu_::handle() {
  for (uint8_t i = 0; i < entries_number; i++) {
    gb.display.setCursor(x + 4, y + 6 * i);
    gb.display.print(entries[i]);
  }
  return handle_vertical_cursor();
}

uint8_t menu_::handle_vertical_cursor() {
  uint8_t prev_pos = (cursor_pos == 0);
  do {
    if (gb.update()) {
      if (cursor_pos != prev_pos) {
        //gb.sound.playTick();
        gb.display.setColor(WHITE);
        gb.display.drawChar(x, y + 6 * (prev_pos), 16, 1);
        gb.display.setColor(BLACK);
        gb.display.drawChar(x, y + 6 * (cursor_pos), 16, 1);
        prev_pos = cursor_pos;
      }
      cursor_pos -= gb.buttons.repeat(BUTTON_UP, ARROW_DELAY) * (cursor_pos > 0) - (entries_number - 1) * (gb.buttons.repeat(BUTTON_UP, ARROW_DELAY) && cursor_pos == 0);
      cursor_pos += gb.buttons.repeat(BUTTON_DOWN, ARROW_DELAY) * (cursor_pos < entries_number - 1) - (entries_number - 1) * (gb.buttons.repeat(BUTTON_DOWN, ARROW_DELAY) && cursor_pos == entries_number - 1);;
      if (gb.buttons.pressed(BUTTON_B)) {
        //gb.sound.playCancel();
        return CANCEL;
      }
    }
  } while (!gb.buttons.pressed(BUTTON_A));
  //gb.sound.playOK();
  return cursor_pos;
}

uint8_t slimes_menu(){
  draw_frame(2, 0, 78, 57);
  for(uint8_t i = 0; i < MAX_HELD_SLIMES; i++){
    if (player.slimes_held[i].id == NO_DATA) break;
    String("sprites/slimes/" + String(player.slimes_held[i].id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
    Image temp(file_name);
    gb.display.drawImage(8, i*9+2, temp, 8, 8);
    gb.display.setCursor(17, i*9+2);
    gb.display.setColor(BLACK);
    gb.display.print(slimes[player.slimes_held[i].id]->name);
    gb.display.fillRect(17, i*9+8, 43, 2);
    gb.display.setColor(WHITE);
    gb.display.drawFastHLine(18, i*9+8, 41);
  }
  do{
    gb.waitForUpdate();
  }while (!gb.buttons.pressed(BUTTON_A));
}
