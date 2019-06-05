#include <Gamebuino-Meta.h>

void draw_frame(uint8_t x, uint8_t y, uint8_t w, uint8_t h);
uint8_t slimes_menu();

class menu_ {
  public:
    uint8_t x, y, cursor_pos, entries_number;
    const MultiLang** entries;
    uint8_t handle(), handle_vertical_cursor();
};

extern menu_ create_menu(uint8_t x, uint8_t y, uint8_t cursor_pos, uint8_t entries_number, const MultiLang** entries);
