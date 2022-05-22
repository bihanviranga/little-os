char* frame_buffer = (char *)0x000B8000;

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
void fb_write_string(unsigned int start, unsigned int size, char* string,
    unsigned char bg, unsigned char fg) {
  for (unsigned int i = 0; i < size; i+=2) {
    fb_write_cell(start + i, string[i], fg, bg);
  }
}

int kmain() {
  fb_write_cell(0, 0x48, 0, 4);
  fb_write_cell(2, 0x65, 0, 4);
  fb_write_cell(4, 0x6c, 0, 4);
  fb_write_cell(6, 0x6c, 0, 4);
  fb_write_cell(8, 0x6f, 0, 4);
  return 0xdeadface;
}
