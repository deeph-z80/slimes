#define FPS 30
#define FILE_NAME_BUFFER_SIZE     30

#define TILE_SIZE                 8
#define TILE_WIDTH                TILE_SIZE
#define TILE_HEIGHT               TILE_SIZE
#define TILE_ANIMATION_FREQUENCY  20 // frame
#define MAP_BUFFER_SIZE           50*50
#define MAX_EVENTS_AMOUNT         10
#define MAX_OBJECTS_AMOUNT        10
#define MAX_NPC_AMOUNT            10
#define LENGTH_TABLE_SIZE         4
#define NPC_SPRITES_LENGTH        3 * 4
#define NPC_MOVE_FREQUENCY        30 // frame
#define SCRIPTS_BUFFER_SIZE       255
#define STRINGS_BUFFER_SIZE       50 // à ajuster selon le nombre de caractères affichable simultanément
#define TEXT_CURSOR_FREQUENCY     10 // frame
#define TEXT_SLOW_SPEED_FREQUENCY 5
#define FLAGS_BUFFER_SIZE         104

#define WARP    0
#define STRING  1
#define SETFLAG 2
#define RESFLAG 3
#define NO_FLAG 255

#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

#define STILL 0
#define MOVE  1

#define FLAG  0
#define X     1
#define Y     2
#define ID_   3

#define OBJECTS_SPRITE_ID 0
#define OBJECTS_DATA      1

#define NPC_SPRITE_ID 0
#define NPC_DIRECTION 1
#define NPC_MOVEMENT  2
#define NPC_DATA      3
