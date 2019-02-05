#include <Gamebuino-Meta.h>

class map_ {
  public:
    uint8_t id, width, height, tileset_id, tiles_amount, tiles_block_id, tiles_anim_start_id, tiles_anim_end_id, music_id = -1, events_amount, objects_amount, npc_amount;
    uint8_t map_buffer[MAP_BUFFER_SIZE];
    uint8_t events_buffer[MAX_EVENTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
    uint8_t objects_buffer[MAX_OBJECTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
    uint8_t npc_buffer[MAX_NPC_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
    uint32_t events_position, objects_position, npc_position;
    File file;
    char file_name[FILE_NAME_BUFFER_SIZE];
    void draw(), load(uint8_t map_id), get_data(uint8_t id);
};

extern map_ current_map;
extern uint8_t music;
