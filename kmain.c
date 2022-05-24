#include "frame_buffer.h"
#include "io.h"
#include "serial.h"

int kmain() {
  fb_write_cell(0, 0x48, 2, 0);
  fb_write_cell(2, 0x65, 2, 0);
  fb_write_cell(4, 0x6c, 2, 0);
  fb_write_cell(6, 0x6c, 2, 0);
  fb_write_cell(8, 0x6f, 2, 0);
  fb_move_cursor(13);
  serial_configure_baud_rate(SERIAL_COM1_BASE, 4);
  serial_configure_line(SERIAL_COM1_BASE);
  return 0xdeadface;
}
