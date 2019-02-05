#include <Gamebuino-Meta.h>

void run_script(uint8_t script_size);
byte text(const char string[]);
void text_frame();
void text_pause();

extern uint8_t scripts_buffer[SCRIPTS_BUFFER_SIZE];
extern uint8_t strings_buffer[STRINGS_BUFFER_SIZE];
