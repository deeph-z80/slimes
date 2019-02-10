#include <Gamebuino-Meta.h>

class menu_ {
  public:
    uint8_t x, y, cursor_pos, entries_number;
    const MultiLang** entries;
    uint8_t handle(), handle_vertical_cursor();
};
