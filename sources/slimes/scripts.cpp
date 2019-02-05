#include "constants.h"
#include "scripts.h"

void run_script(uint8_t script_size) {
  for (uint8_t pos = 0; pos < script_size; pos++) {
    switch (scripts_buffer[pos]) {
      case STRING:
        pos++;
        File strings_file = SD.open("strings/strings.str", O_RDWR);
        uint8_t length = strings_file.read();
        for (uint8_t i = 0; i < scripts_buffer[pos]; i++) {
          strings_file.seek(strings_file.position() + length);
          length = strings_file.read();
        }
        strings_file.read(strings_buffer, length);
        strings_file.close();
        text((char*) strings_buffer);
        break;
    }
  }
}

byte text(const char string[]) {
  text_frame();
  for (byte i = 0; i < strlen(string); i++) {
    char c = (char) string[i];
    switch ((byte) c) {
      case 10:
        gb.display.setCursor(2, gb.display.getCursorY() + 6);
        break;
      case 112:
        text_pause();
        text_frame();
        break;
      default:
        gb.display.print(c);
        while (!gb.update());
        break;
    }
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
    if (gb.update()) {
      if (gb.frameCount % 2) gb.display.setColor(WHITE);
      gb.display.drawChar(gb.display.getCursorX(), gb.display.getCursorY(), 21, 1);
      gb.display.setColor(BLACK);
      while (!gb.update());
      //delay(TEXT_BLINK_DELAY);
      if (gb.buttons.pressed(BUTTON_A)) break;
    }
  }
}

uint8_t scripts_buffer[SCRIPTS_BUFFER_SIZE];
uint8_t strings_buffer[STRINGS_BUFFER_SIZE];
