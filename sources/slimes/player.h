#include <Gamebuino-Meta.h>
#include "stats.h"

class player_ {
  public:
    uint8_t x, y, direction, animation, scrolling, flags[FLAGS_BUFFER_SIZE/8];
    int8_t x_velocity, y_velocity, x_offset, y_offset;
    bool is_moving, get_flag(uint8_t id);
    void draw(), update(), set_flag(uint8_t id, bool value);
    slime slimes_held[MAX_HELD_SLIMES];
    slime slimes_stored[MAX_STORED_SLIMES];
};

extern player_ player;
