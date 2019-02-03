#include <Gamebuino-Meta.h>

class camera_ {
  public:
    int16_t x, y;
    void update();
};

extern camera_ camera;
