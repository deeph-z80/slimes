#include <Gamebuino-Meta.h>

#ifndef STATS
#define STATS
class slime_stat {
  public:
    uint8_t id, element, base, attack, defense, speed, xp_curve, catch_rate;
    const MultiLang* name;
};

class slime_move {
  public:
    uint8_t id, element, pp, base, state_change;
    const MultiLang* name;
};

class slime {
  public:
    uint8_t id, level, current_hp, hp_bonus;
    uint16_t xp;
    slime_move moves[4];
    void free();
};

extern slime_stat plantslime, fireslime, nodataslime;

extern slime_stat* slimes[];

uint8_t compute_hp(slime slime);
#endif
