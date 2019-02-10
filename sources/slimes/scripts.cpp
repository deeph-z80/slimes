#include "constants.h"
#include "map.h"
#include "player.h"
#include "scripts.h"

void run_script(uint8_t script_size) {
  uint8_t temp;
  for (uint8_t pos = 0; pos < script_size; pos++) {
    switch (scripts_buffer[pos]) {
      case WARP:
        //fade_in();
        pos++; player.x = scripts_buffer[pos];
        pos++; player.y = scripts_buffer[pos];
        pos++; player.direction = scripts_buffer[pos];
        player.animation = 0;
        player.is_moving = false;
        pos++; temp = scripts_buffer[pos];
        current_map.file.close();
        current_map.load(temp);
        //fade_out();
        break;
      case STRING:
        pos++;
        switch (gb.language.getCurrentLang()) {
          case LANG_FR:
            strings_file = SD.open("strings/fr.str", O_RDWR);
            break;
          default:
            strings_file = SD.open("strings/en.str", O_RDWR);
            break;
        }
        uint8_t length;
        for (uint8_t i = 0; i < scripts_buffer[pos]; i++) {
          length = strings_file.read();
          strings_file.seek(strings_file.position() + length);
        }
        length = strings_file.read();
        memset(strings_buffer, 0, sizeof(strings_buffer));
        strings_file.read(strings_buffer, length);
        strings_file.close();
        text((char*) strings_buffer);
        break;
      case SETFLAG:
        pos++;
        player.set_flag(scripts_buffer[pos], true);
        break;
      case RESFLAG:
        pos++;
        player.set_flag(scripts_buffer[pos], false);
        break;
    }
  }
}

byte text(const char string[]) {
  boolean delay = false;
  text_frame();
  for (byte i = 0; i < strlen(string); i++) {
    char c = (char) string[i];
    switch ((byte) c) {
      case 0x0a: // new line
        gb.display.setCursor(2, gb.display.getCursorY() + 6);
        break;
      case 0x7c: // pause
        text_pause();
        text_frame();
        break;
      case 0x7b: // slow down
        delay = true;
        break;
      case 0x7d: // restore speed
        delay = false;
        break;
      default:
        gb.display.print(c);
        while (!gb.update());
        break;
    }
    if (delay) while (!(gb.update() & (gb.frameCount % TEXT_SLOW_SPEED_FREQUENCY == 0)));
  }
  text_pause();
}

void text_frame() {
  gb.display.setColor(WHITE);
  gb.display.fillRect(0, 37, 80, 27);
  gb.display.setColor(BLACK);
  gb.display.drawRect(0, 37, 80, 27);
  gb.display.setCursor(2, 39);
}

void text_pause() {
  while (true) {
    if (gb.frameCount / TEXT_CURSOR_FREQUENCY % 2) gb.display.setColor(WHITE);
    gb.display.drawChar(gb.display.getCursorX(), gb.display.getCursorY(), 21, 1);
    gb.display.setColor(BLACK);
    if (gb.buttons.pressed(BUTTON_A)) break;
    while (!gb.update());
  }
}

File strings_file;
uint8_t scripts_buffer[SCRIPTS_BUFFER_SIZE];
uint8_t strings_buffer[STRINGS_BUFFER_SIZE];
