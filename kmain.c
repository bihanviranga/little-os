#include "frame_buffer.h"
#include "io.h"
#include "serial.h"

int kmain() {
  serial_initialize();
  serial_write(SERIAL_COM1_BASE, "Hello world!", 12);

  return 0xdeadface;
}
