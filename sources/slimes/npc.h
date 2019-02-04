#include <Gamebuino-Meta.h>

class npc_ {
  public:
    uint8_t id, x, y, sprite_id, direction, movement, animation, scrolling;
    int8_t x_velocity, y_velocity, x_offset, y_offset;
    boolean flag, is_moving;
    void update();
};

extern npc_ npc[MAX_NPC_AMOUNT];
