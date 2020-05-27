#include "constants.h"
#include "stats.h"
#include "strings.h"

void slime::free() {
  memset(this, NO_DATA, sizeof(this));
}

slime_stat plantslime = { 0, TYPE_GRASS, 64, 49, 49, 49, 1, 200, n_plantslime };
slime_stat fireslime = { 1, TYPE_FIRE, 64, 49, 49, 49, 1, 200, n_fireslime };
slime_stat nodataslime = { 20, NO_DATA, NO_DATA, NO_DATA, NO_DATA, NO_DATA, NO_DATA, NO_DATA, n_nodataslime };

slime_stat* slimes[] = { &plantslime, &fireslime, &fireslime, &fireslime, &fireslime,
                         &fireslime, &fireslime, &fireslime, &fireslime, &fireslime,
                         &fireslime, &fireslime, &fireslime, &fireslime, &fireslime,
                         &fireslime, &fireslime, &fireslime, &fireslime, &fireslime,
                         &nodataslime };

uint8_t compute_hp(slime slime){
  return ((2*slimes[slime.id]->base+(slime.hp_bonus/4))*slime.level)/100+slime.level+10;
}
