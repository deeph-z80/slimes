#include <Gamebuino-Meta.h>

#define FPS 30
#define FILE_NAME_BUFFER_SIZE     30

#define TILE_SIZE                 8
#define TILE_WIDTH                TILE_SIZE
#define TILE_HEIGHT               TILE_SIZE
#define TILE_ANIMATION_FREQUENCY  500 // ms
#define MAP_BUFFER_SIZE           50*50
#define MAX_EVENTS_AMOUNT         10
#define MAX_OBJECTS_AMOUNT        10
#define MAX_NPC_AMOUNT            10
#define LENGTH_TABLE_SIZE         4

#define WARP    0
#define MESSAGE 1
#define SCRIPT  2

#define RIGHT 0
#define UP    1
#define LEFT  2
#define DOWN  3

#define FLAG  0
#define X     1
#define Y     2
#define ID    3

#define NO_FLAG 255

#define OBJECTS_SPRITE_ID 0
#define OBJECTS_DATA      1

#define NPC_SPRITE_ID 0
#define NPC_DIRECTION 1
#define NPC_MOVEMENT  2
#define NPC_DATA      3

#include "sprites.h"

File file;
Image tileset;
int music = -1;
uint8_t map_buffer[MAP_BUFFER_SIZE];
uint8_t events_buffer[MAX_EVENTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
uint8_t objects_buffer[MAX_OBJECTS_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
uint8_t npc_buffer[MAX_NPC_AMOUNT * LENGTH_TABLE_SIZE]; // flag, x, y, id
char file_name[FILE_NAME_BUFFER_SIZE];

class camera_ {
  public:
    int16_t x, y;
    void update();
};
camera_ camera;

class map_ {
  public:
    uint8_t id, width, height, tileset_id, tiles_amount, tiles_block_id, tiles_anim_start_id, tiles_anim_end_id, music_id = -1, *data, events_amount, *events, objects_amount, *objects, npc_amount, *npc;
    uint32_t events_position, objects_position, npc_position;
    void draw();
};
map_ current_map;

class player_ {
  public:
    uint8_t x, y, direction, animation, scrolling;
    int8_t x_velocity, y_velocity, x_offset, y_offset;
    boolean is_moving;
    void draw(), update();
};
player_ player;

void seek_table(uint8_t times) {
  for (byte i = 0; i < times; i++) {
    uint8_t length = file.read();
    file.seek(file.position() + length);
  }
}
void camera_::update() {
  x = player.x * TILE_SIZE - gb.display.width() / 2 + TILE_WIDTH / 2 + player.x_offset;
  x = camera.x * (x > 0) + (current_map.width * TILE_WIDTH - gb.display.width() - x) * (x > current_map.width * TILE_WIDTH - gb.display.width());
  y = player.y * TILE_SIZE - gb.display.height() / 2 + TILE_HEIGHT / 2 + player.y_offset;
  y = camera.y * (y > 0) + (current_map.height * TILE_HEIGHT - gb.display.height() - y) * (y > current_map.height * TILE_HEIGHT - gb.display.height());
};

void map_::draw() {
  for (byte x = 0; x <= gb.display.width() / TILE_WIDTH + 1; x++) {
    for (byte y = 0; y <= gb.display.height() / TILE_HEIGHT + 1; y++) {
      int8_t tile_x = camera.x / TILE_WIDTH + x;
      int8_t tile_y = camera.y / TILE_HEIGHT + y;
      //if (tile_x >= 0 && tile_x < width && tile_y >= 0 && tile_y < height) {
      byte tile_id = data[tile_y * width + tile_x];
      tile_id += (tile_id >= tiles_anim_start_id && tile_id <= tiles_anim_end_id) * millis() / TILE_ANIMATION_FREQUENCY % 2;
      gb.display.drawImage(x * TILE_WIDTH - camera.x % TILE_WIDTH, y * TILE_HEIGHT - camera.y % TILE_HEIGHT, tileset, 0, tile_id * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);

      // check for objects to draw
      for (byte i = 0; i < current_map.objects_amount; i++) {
        if (tile_x == current_map.objects[i * LENGTH_TABLE_SIZE + X] && tile_y == current_map.objects[i * LENGTH_TABLE_SIZE + Y]
        //&& flag(current_map.objects[i * LENGTH_TABLE_SIZE + FLAG]) == FALSE) {
        ){
          seek_table(current_map.objects[i * LENGTH_TABLE_SIZE + ID]);
          file.read(); // skip length
          objects_sprite_set.setFrame(file.read());
          gb.display.drawImage(x * TILE_WIDTH - camera.x % TILE_WIDTH, y * TILE_HEIGHT - camera.y % TILE_HEIGHT, objects_sprite_set);
          break;
        }
      }
      //}
    }
  }
}

void player_::draw() {
  player_sprite_set.setFrame(direction * 3 + animation);
  gb.display.drawImage(x * TILE_WIDTH - camera.x + x_offset, y * TILE_HEIGHT - camera.y + y_offset, player_sprite_set);
}

void load_map(uint8_t map_id) {
  uint8_t last_music = current_map.music_id;
  String("maps/" + String(map_id) + ".map").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  file = SD.open(file_name, O_RDWR);
  current_map.id = map_id;
  current_map.width = file.read();
  current_map.height = file.read();
  current_map.tileset_id = file.read();
  current_map.tiles_amount = file.read();
  current_map.tiles_block_id = file.read();
  current_map.tiles_anim_start_id = file.read();
  current_map.tiles_anim_end_id = file.read();
  current_map.music_id = file.read();
  file.read(map_buffer, current_map.width * current_map.height);
  current_map.data = map_buffer;
  current_map.events_amount = file.read();
  if (current_map.events_amount > 0) {
    file.read(events_buffer, current_map.events_amount * LENGTH_TABLE_SIZE);
    current_map.events = events_buffer;
    current_map.events_position = file.position();
    seek_table(current_map.events_amount);
  }
  current_map.objects_amount = file.read();
  if (current_map.objects_amount > 0) {
    file.read(objects_buffer, current_map.objects_amount * LENGTH_TABLE_SIZE);
    current_map.objects = objects_buffer;
    current_map.objects_position = file.position();
  }
  current_map.npc_amount = file.read();
  if (current_map.npc_amount > 0) {
    file.read(npc_buffer, current_map.npc_amount * LENGTH_TABLE_SIZE);
    current_map.npc = npc_buffer;
    current_map.npc_position = file.position();
  }
  file.close();
  String("sprites/" + String(current_map.tileset_id) + ".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  tileset.init(TILE_WIDTH, TILE_HEIGHT * current_map.tiles_amount, file_name, 0);
  if (last_music != current_map.music_id) {
    // todo : add fading
    String("musics/" + String(current_map.music_id) + ".wav").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
    gb.sound.stop(music);
    music = gb.sound.play(file_name, true);
  }
}

void player_::update() {
  if (!is_moving) {
    x_velocity = y_velocity = 0;
    x_velocity = -gb.buttons.repeat(BUTTON_LEFT, 1) * (x > 0) + gb.buttons.repeat(BUTTON_RIGHT, 1) * (x < current_map.width - 1);
    y_velocity = -gb.buttons.repeat(BUTTON_UP, 1) * (y > 0) + gb.buttons.repeat(BUTTON_DOWN, 1) * (y < current_map.height - 1);
    if (!x_velocity != !y_velocity) {
      direction = (1 + x_velocity) * (x_velocity != 0);
      direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);
      if (current_map.data[(y + y_velocity) * current_map.width + x + x_velocity] < current_map.tiles_block_id) is_moving = true;
    }
  } else {
    scrolling++;
    animation += scrolling % 2;
    animation *= animation < 3 && scrolling < TILE_SIZE;
    x_offset += x_velocity;
    y_offset += y_velocity;
    if (scrolling == TILE_SIZE) {
      scrolling = x_offset = y_offset = 0;
      is_moving = false;
      x += x_velocity;
      y += y_velocity;

      // check for walk-triggered events
      for (byte i = 0; i < current_map.events_amount; i++) {
        if (x == current_map.events[i * LENGTH_TABLE_SIZE + X] && y == current_map.events[i * LENGTH_TABLE_SIZE + Y]) {
          String("maps/" + String(current_map.id) + ".map").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
          file = SD.open(file_name, O_RDWR);
          file.seek(current_map.events_position);
          seek_table(current_map.events[i * LENGTH_TABLE_SIZE + ID]);
          file.read(); // skip length
          switch (file.read()) {
            case WARP:
              //fade.in
              player.x = file.read();
              player.y = file.read();
              player.direction = file.read();
              player.animation = 0;
              player.is_moving = false;
              load_map(file.read());
              //fade.out
              break;
            default:
              gb.display.clear();
              gb.display.setCursor(0, 0);
              gb.display.println(file.position());
              delay(10000);
          }
          file.close();
          break;
        }
      }
    }
  }
}

void setup() {
  gb.begin();
  gb.setFrameRate(FPS);
  player.x = 7;
  player.y = 4;
  player.direction = DOWN;
  player.animation = 0;
  player.is_moving = false;
  load_map(0);
}

void loop() {
  while (true) {
    player.update();
    camera.update();
    current_map.draw();
    player.draw();

    // debug
    gb.display.setColor(WHITE);
    gb.display.setCursor(0, 0);
    gb.display.println(gb.getFreeRam());
    gb.display.println(gb.getCpuLoad());

    while (!gb.update());
  }
}
