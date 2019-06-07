#include <Gamebuino-Meta.h>

void draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
uint8_t slimes_menu();

class menu_ {
  public:
    uint8_t x, y, cursor_pos, entries_number;
    const MultiLang* entries[MAX_MENU_ENTRIES];
    uint8_t handle(), handle_vertical_cursor();
};
