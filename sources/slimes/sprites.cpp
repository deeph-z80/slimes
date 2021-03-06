#include "sprites.h"

const uint8_t player_sprites[] = {
  8, 8,   // sprites width & height
  12, 0,  // sprites amount lower & upper 8-bit
  0,      // frames loop (0 = no animation)
  14,     // transparent color (14 = pink)
  1,      // color mode (1 = indexed)
  0xee,0x00,0x00,0xee,
  0xe0,0x68,0x88,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x4f,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xee,0x0f,0x0e,0xee,
  0xee,0x00,0x00,0xee,
  0xee,0x00,0x00,0xee,
  0xe0,0x68,0x88,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x4f,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0x00,0xf0,0xee,
  0xe0,0x00,0x00,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0x68,0x88,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x4f,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0xf0,0x00,0xee,
  0xe0,0x00,0x00,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0x44,0x44,0x40,
  0xe0,0xff,0xff,0xf0,
  0xee,0x00,0x00,0x0e,
  0xe0,0xf0,0x00,0xf0,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0x44,0x44,0x40,
  0xe0,0x0f,0xff,0xf0,
  0xe0,0xf0,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0x44,0x44,0x40,
  0xe0,0xff,0xff,0x00,
  0xe0,0x00,0x00,0xf0,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0x08,0x88,0x60,
  0xe0,0x00,0x00,0x00,
  0xee,0x0f,0x0f,0x40,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xee,0x0f,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0x08,0x88,0x60,
  0xe0,0x00,0x00,0x00,
  0xee,0x0f,0x0f,0x40,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0xf0,0x00,
  0xee,0x00,0x00,0x00,
  0xee,0xe0,0x00,0x0e,
  0xee,0x08,0x88,0x60,
  0xe0,0x00,0x00,0x00,
  0xee,0x0f,0x0f,0x40,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0x00,0xf0,
  0xee,0x00,0x00,0x00,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0xff,0xff,0xf0,
  0xee,0x00,0x00,0x0e,
  0xe0,0xf0,0x00,0xf0,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0x0f,0xff,0xf0,
  0xe0,0xf0,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x88,0x88,0x80,
  0xe0,0x00,0x00,0x00,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0xff,0xff,0x00,
  0xe0,0x00,0x00,0xf0,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e
};
Image player_sprite_set(player_sprites);

const uint8_t objects_sprites[]={
  8, 8, // sprites width & height
  2, 0, // sprites amount lower & upper 8-bit
  0,    // frames loop (0 = no animation)
  14,   // transparent color (14 = pink)
  1,    // color mode (1 = indexed)
  0xee,0x00,0x00,0xee,
  0xe0,0x88,0x88,0x0e,
  0x08,0x78,0x88,0x80,
  0x08,0x88,0x88,0x80,
  0x07,0x88,0x88,0x70,
  0x07,0x77,0x77,0x70,
  0xe0,0x77,0x77,0x0e,
  0xee,0x00,0x00,0xee,
  0x00,0x00,0x00,0x00,
  0x07,0x77,0x77,0x70,
  0x07,0x77,0x77,0x70,
  0x07,0x77,0x77,0x70,
  0x07,0x77,0x77,0x70,
  0x07,0x77,0x77,0x70,
  0x07,0x77,0x77,0x70,
  0x00,0x00,0x00,0x00
};
Image objects_sprite_set(objects_sprites);

const uint8_t npc_sprites[]={
  8, 8,   // sprites width & height
  12, 0,  // sprites amount lower & upper 8-bit
  0,      // frames loop (0 = no animation)
  14,     // transparent color (14 = pink)
  1,      // color mode (1 = indexed)
  0xee,0x00,0x00,0xee,
  0xe0,0x00,0x00,0x0e,
  0xe0,0x0f,0xff,0x0e,
  0xe0,0xff,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xee,0x0f,0x0e,0xee,
  0xee,0x00,0x00,0xee,
  0xee,0x00,0x00,0xee,
  0xe0,0x00,0x00,0x0e,
  0xe0,0x0f,0xff,0x0e,
  0xe0,0xff,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0x00,0xf0,0xee,
  0xe0,0x00,0x00,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0x00,0x00,0x0e,
  0xe0,0x0f,0xff,0x0e,
  0xe0,0xff,0x0f,0x0e,
  0xe0,0xff,0xff,0x0e,
  0xee,0x00,0x00,0xee,
  0xe0,0xf0,0x00,0xee,
  0xe0,0x00,0x00,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0xff,0xff,0xf0,
  0xee,0x00,0x00,0x0e,
  0xe0,0xf0,0x00,0xf0,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0x0f,0xff,0xf0,
  0xe0,0xf0,0x00,0x00,
  0xe0,0x00,0x05,0x50,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xe0,0xff,0xff,0x00,
  0xe0,0x00,0x00,0xf0,
  0xe0,0x55,0x00,0x00,
  0xee,0x00,0xe0,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0x00,0x00,0x00,
  0xee,0x0f,0xff,0x00,
  0xee,0x0f,0x0f,0xf0,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xee,0x0f,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0x00,0x0e,
  0xee,0x00,0x00,0x00,
  0xee,0x0f,0xff,0x00,
  0xee,0x0f,0x0f,0xf0,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0xf0,0x00,
  0xee,0x00,0x00,0x00,
  0xee,0xe0,0x00,0x0e,
  0xee,0x00,0x00,0x00,
  0xee,0x0f,0xff,0x00,
  0xee,0x0f,0x0f,0xf0,
  0xee,0x0f,0xff,0xf0,
  0xee,0xe0,0x00,0x0e,
  0xee,0xe0,0x00,0xf0,
  0xee,0x00,0x00,0x00,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0xff,0xff,0xf0,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0xff,0xff,0xf0,
  0xee,0x00,0x00,0x0e,
  0xe0,0xf0,0x00,0xf0,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0xff,0xff,0xf0,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0x0f,0xff,0xf0,
  0xe0,0xf0,0x00,0x00,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e,
  0xee,0x00,0x00,0x0e,
  0xe0,0x00,0x00,0x00,
  0xe0,0xff,0xff,0xf0,
  0xe0,0xf0,0xf0,0xf0,
  0xe0,0xff,0xff,0x00,
  0xe0,0x00,0x00,0xf0,
  0xe0,0x00,0x00,0x00,
  0xee,0x00,0xe0,0x0e
};
Image npc_sprite_set(npc_sprites);

Image tileset;
