#include <Gamebuino-Meta.h>

class player_ {
  public:
    uint8_t x, y, direction, animation, scrolling, flags[FLAGS_BUFFER_SIZE/8];
    int8_t x_velocity, y_velocity, x_offset, y_offset;
    bool is_moving, get_flag(uint8_t id);
    void draw(), update(), set_flag(uint8_t id, bool value);
};

extern player_ player;
