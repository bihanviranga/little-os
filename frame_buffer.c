#include "frame_buffer.h"

#include "io.h"

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
 * @param i   location in the framebuffer
 * @param c   character
 * @param fg  foreground color
 * @param bg  background color
 */
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg) {
  frame_buffer[i] = c;
  frame_buffer[i + 1] = ((bg & 0x0f) << 4 ) | (fg & 0x0f);
}

/**
 * The driver interface.
 * FIXME - this does not work.
 */
int fb_write(char* buf, unsigned int len) {
  for (unsigned int i = 0; i < len; i++) {
    fb_write_cell(i, buf[i], 7, 0);
  }
  return 0;
}
