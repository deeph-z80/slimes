#include "constants.h"
#include "stats.h"

slime create_slime(uint8_t id, uint8_t element, uint8_t base, uint8_t attack, uint8_t defense, uint8_t speed, uint8_t xp_curve, uint8_t catch_rate){
  slime temp;
  temp.id = id;
  temp.element = element;
  temp.base = base;
  temp.attack = attack;
  temp.defense = defense;
  temp.speed = speed;
  temp.xp_curve = xp_curve;
  temp.catch_rate = catch_rate;
  return temp;
}

slime plantslime = create_slime(0, TYPE_GRASS, 64, 49, 49, 49, 1, 200);
