#include "constants.h"
#include "map.h"
#include "menu.h"
#include "player.h"
#include "stats.h"
#include "strings.h"

void draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h){
  gb.display.setColor(WHITE);
  gb.display.fillRect(x, y, w, h);
  gb.display.setColor(BLACK);
  gb.display.drawRect(x, y, w, h);
}

uint8_t menu_::handle() {
  gb.display.setColor(BLACK);
  for (uint8_t i = 0; i < entries_number; i++) {
    gb.display.setCursor(x + 4 + x_offset, y + y_increase * i);
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
        gb.display.drawChar(x, y + y_increase * (prev_pos), 16, 1);
        gb.display.setColor(BLACK);
        gb.display.drawChar(x, y + y_increase * (cursor_pos), 16, 1);
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
  uint8_t i;
  for(i = 0; i < MAX_HELD_SLIMES; i++){
    if (player.slimes_held[i].id == NO_DATA) break;
    String("sprites/slimes/" + String(player.slimes_held[i].id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
    temp.init(file_name);
    gb.display.drawImage(8, i*9+2, temp, 8, 8);
    draw_hp_box(player.slimes_held[i], 17, i*9+7);
    gb.display.setColor(WHITE);
    gb.display.drawFastHLine(18, i*9+7, 41);
  }

  menu_ temp2 = menu_{4, 2, 0, i, 8, 9, {
    slimes[player.slimes_held[0].id]->name,
    slimes[player.slimes_held[1].id]->name,
    slimes[player.slimes_held[2].id]->name,
    slimes[player.slimes_held[3].id]->name,
    slimes[player.slimes_held[4].id]->name,
    slimes[player.slimes_held[5].id]->name}};
  gb.waitForUpdate();
  i = temp2.handle();
  if (i == CANCEL) return CANCEL;

  gb.waitForUpdate();
  draw_frame(53, 49, 27, 15);
  #define STATS 0
  #define ORDER 1
  temp2 = menu_{55, 51, 0, 2, 0, 6, {e_stats, e_order}};
  switch(temp2.handle()){
    case STATS:
      draw_frame(0, 2, 36, 62);
      draw_frame(0, 12, 80, 52);
      gb.display.setColor(WHITE);
      gb.display.fillRect(1, 3, 34, 60);
      String("sprites/slimes/" + String(player.slimes_held[i].id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
      temp.init(file_name);
      gb.display.drawImage(2, 4, temp, 32, 32);
      draw_slime_hp_info(player.slimes_held[i], 35, 14);
      do{
        gb.waitForUpdate();
      }while (!gb.buttons.pressed(BUTTON_A));
      break;
    case ORDER:
      break;
  }
//  do{
//    gb.waitForUpdate();
//  }while (!gb.buttons.pressed(BUTTON_A));
}

void draw_slime_hp_info(slime slime, uint8_t x, uint8_t y){
  gb.display.setColor(BLACK);
  gb.display.setCursor(x, y);
  gb.display.print(slimes[slime.id]->name);
  draw_hp_box(slime, x+1, y+6);
  gb.display.setColor(BLACK);
  gb.display.setCursor(x, y+10);
  gb.display.print(e_level);
  gb.display.setCursor(x+3, y+10);
  gb.display.print(":");
  gb.display.setCursor(x+6, y+10);
  gb.display.print(slime.level);
  String(String(slime.current_hp) + "/" + String(compute_hp(slime))).toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  gb.display.setCursor(x+16, y+10);
  gb.display.print(file_name);
}

void draw_hp_box(slime slime, uint8_t x, uint8_t y){
  draw_frame(x+1, y, 41, 3);
  gb.display.drawPixel(x, y+1);
  gb.display.drawPixel(x+42, y+1);
  gb.display.setColor(WHITE);
  gb.display.drawFastHLine(x+1, y+1, 41);
  float temp = (float)slime.current_hp/compute_hp(slime);
  if(temp > 0.6){
    gb.display.setColor(GREEN);
  }else if(temp > 0.3){
    gb.display.setColor(ORANGE);
  }else{
    gb.display.setColor(RED);
  }
  gb.display.drawFastHLine(x+1, y+1, temp*41);
}
