#include <Gamebuino-Meta.h>
#include "constants.h"

class map_ {
  public:
    uint8_t music, id, width, height, tileset_id, tiles_amount, tiles_block_id, tiles_anim_start_id, tiles_anim_end_id, music_id = -1, *data, events_amount, *events, objects_amount, *objects, npc_amount, *npc;
    uint32_t events_position, objects_position, npc_position;
    File file;
    void draw(), load(uint8_t map_id), seek_table(uint8_t times);
};

extern map_ current_map;
extern uint8_t map_buffer[MAP_BUFFER_SIZE];
extern uint8_t events_buffer[MAX_EVENTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
extern uint8_t objects_buffer[MAX_OBJECTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
extern uint8_t npc_buffer[MAX_NPC_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
extern char file_name[FILE_NAME_BUFFER_SIZE];
