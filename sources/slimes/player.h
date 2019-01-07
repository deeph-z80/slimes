#include <Gamebuino-Meta.h>
#include "constants.h"

class player_ {
  public:
    uint8_t x, y, direction, animation, scrolling;
    int8_t x_velocity, y_velocity, x_offset, y_offset;
    boolean is_moving;
    void draw(), update();
};

extern player_ player;
