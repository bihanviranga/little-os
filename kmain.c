#include "io.h"

/* I/O ports */
#define FB_COMMAND_PORT 0x3d4
#define FB_DATA_PORT    0x3d5

/* I/O port commands */
#define FB_HIGH_BYTE_COMMAND  14
#define FB_LOW_BYTE_COMMAND   15

char* frame_buffer = (char *)0x000B8000;

/**
 * Moves the cursor of the framebuffer to the given position.
 *
 * @param pos new position of the cursor
 */
void fb_move_cursor(unsigned short pos) {
  outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
  outb(FB_DATA_PORT, ((pos >> 4) & 0x00ff)); // NOTE: shift by 4 or 8?
  outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
  outb(FB_DATA_PORT, pos & 0x00ff);
}

/**
 * Writes a character with the given foreground and background to position i
 * in the framebuffer.
 *
 * @param i location in the framebuffer
 * @param c character
 * @param fg foreground color
 * @param bg background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  frame_buffer[i] = c;
  frame_buffer[i + 1] = ((bg & 0x0f) << 4 ) | (fg & 0x0f);
}

// FIXME compiles but doesn't work on the VM. Stack issue?
/*
void fb_write_string(unsigned int start, unsigned int size, char* string,
    unsigned char bg, unsigned char fg) {
  for (unsigned int i = 0; i < size; i+=2) {
    fb_write_cell(start + i, string[i], fg, bg);
  }
}
*/

int kmain() {
  fb_write_cell(0, 0x48, 2, 0);
  fb_write_cell(2, 0x65, 2, 0);
  fb_write_cell(4, 0x6c, 2, 0);
  fb_write_cell(6, 0x6c, 2, 0);
  fb_write_cell(8, 0x6f, 2, 0);
  fb_move_cursor(13);
  return 0xdeadface;
}
