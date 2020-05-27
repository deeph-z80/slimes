#include <Gamebuino-Meta.h>
#include "stats.h"

void draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
uint8_t slimes_menu();
void draw_slime_hp_info(slime slime, uint8_t x, uint8_t y);
void draw_hp_box(slime slime, uint8_t x, uint8_t y);

class menu_ {
  public:
    uint8_t x, y, cursor_pos, entries_number, x_offset, y_increase;
    const MultiLang* entries[MAX_MENU_ENTRIES];
    uint8_t handle(), handle_vertical_cursor();
};
