#include <Gamebuino-Meta.h>
#include "constants.h"

class camera_ {
  public:
    int16_t x, y;
    void update();
};

extern camera_ camera;
