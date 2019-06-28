#include "constants.h"
#include "stats.h"
#include "strings.h"

void slime::free() {
  memset(this, NO_DATA, sizeof(this));
}

slime_stat plantslime = { 0, TYPE_GRASS, 64, 49, 49, 49, 1, 200, n_plantslime };
slime_stat fireslime = { 1, TYPE_FIRE, 64, 49, 49, 49, 1, 200, n_fireslime };

slime_stat* slimes[] = { &plantslime, &fireslime };
