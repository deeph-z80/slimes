#include <Gamebuino-Meta.h>

#define TILE_SIZE             8
#define TILE_WIDTH            TILE_SIZE
#define TILE_HEIGHT           TILE_SIZE
#define MAP_BUFFER_SIZE       100*100
#define FILE_NAME_BUFFER_SIZE 30

#include "sprites.h"

File file;
Image tile_set;
int music = -1;
uint8_t map_buffer[MAP_BUFFER_SIZE];
char file_name[FILE_NAME_BUFFER_SIZE];

class camera_ {
  public:
    int16_t x, y;
    void update();
};
camera_ camera;

class map_ {
  public:
    uint8_t width, height, tile_blocking_limit, tile_set_id, tile_set_tiles_amount, music_id, *data;
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

void camera_::update() {
  x = player.x * TILE_SIZE - gb.display.width() / 2 + TILE_WIDTH / 2 + player.x_offset;
  x = camera.x * (x > 0) + (current_map.width * TILE_WIDTH - gb.display.width() - x) * (x > current_map.width * TILE_WIDTH - gb.display.width());
  y = player.y * TILE_SIZE - gb.display.height() / 2 + TILE_HEIGHT / 2 + player.y_offset;
  y = camera.y * (y > 0) + (current_map.height * TILE_HEIGHT - gb.display.height() - y) * (y > current_map.height * TILE_HEIGHT - gb.display.height());
};

void map_::draw() {
  for (byte x = 0; x <= gb.display.height() / TILE_WIDTH + 2; x++) { // +2 idk why
    for (byte y = 0; y <= gb.display.width() / TILE_HEIGHT + 1; y++) {
      int8_t tile_x = camera.x / TILE_WIDTH + x;
      int8_t tile_y = camera.y / TILE_HEIGHT + y;
      //if (tile_x >= 0 && tile_x < width && tile_y >= 0 && tile_y < height) {
      //tile_set.setFrame(data[tile_y * width + tile_x]);
      byte tile_id = data[tile_y * width + tile_x];
      tile_x = x * TILE_WIDTH - camera.x % TILE_WIDTH;
      tile_y = y * TILE_HEIGHT - camera.y % TILE_HEIGHT;
      gb.display.drawImage(tile_x, tile_y, tile_set, 0, tile_id*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT);
      //}
    }
  }
}

void player_::draw() {
  player_sprite_set.setFrame(direction * 3 + animation);
  gb.display.drawImage(x * TILE_WIDTH - camera.x + x_offset, y * TILE_HEIGHT - camera.y + y_offset, player_sprite_set);
}

void player_::update() {
  if (!is_moving) {
    x_velocity = y_velocity = 0;
    x_velocity = -gb.buttons.repeat(BUTTON_LEFT, 1) * (x > 0) + gb.buttons.repeat(BUTTON_RIGHT, 1) * (x < current_map.width - 1);
    y_velocity = -gb.buttons.repeat(BUTTON_UP, 1) * (y > 0) + gb.buttons.repeat(BUTTON_DOWN, 1) * (y < current_map.height - 1);
    if (!x_velocity != !y_velocity) {
      direction = (1 + x_velocity) * (x_velocity != 0);
      direction = (2 + y_velocity) * (y_velocity != 0 || direction == 0);
      if (current_map.data[(y + y_velocity) * current_map.width + x + x_velocity] < current_map.tile_blocking_limit) is_moving = true;
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
    }
  }
}

void setup() {
  gb.begin();
  gb.setFrameRate(50);

  file = SD.open("maps/test.map", O_RDWR);
  current_map.width = file.read();
  current_map.height = file.read();
  current_map.tile_blocking_limit = file.read();
  current_map.tile_set_id = file.read();
  current_map.tile_set_tiles_amount = file.read();
  current_map.music_id = file.read();
  file.read(map_buffer, current_map.width*current_map.height);
  current_map.data = map_buffer;
  file.close();

  player.x = player.y = 4;
  player.direction = player.animation = 0;
  player.is_moving = false;
  String("sprites/"+String(current_map.tile_set_id)+".bmp").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  tile_set.init(TILE_WIDTH, TILE_HEIGHT*current_map.tile_set_tiles_amount, file_name, 0);
}

void loop() {
  String("musics/"+String(current_map.music_id)+".wav").toCharArray(file_name, FILE_NAME_BUFFER_SIZE);
  music = gb.sound.play(file_name, true);
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
