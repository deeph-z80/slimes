#include <Gamebuino-Meta.h>

class slime {
  public:
    uint8_t id, element, base, attack, defense, speed, xp_curve, catch_rate;
};

extern slime create_slime(uint8_t id, uint8_t element, uint8_t base, uint8_t attack, uint8_t defense, uint8_t speed, uint8_t xp_curve, uint8_t catch_rate);
extern slime plantslime;
