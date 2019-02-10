#include "menu.h"
#include "constants.h"

uint8_t menu_::handle() {
  for (uint8_t i = 0; i < entries_number; i++) {
    gb.display.setCursor(x + 4, y + 6 * i);
    gb.display.print(entries[i]);
  }
  uint8_t option = handle_vertical_cursor();
  if (option == CANCEL) return CANCEL;
  //return data[4 + option];
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
