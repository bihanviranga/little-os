#include "serial.h"

#include "io.h"

/**
 * Sets the speed of the data being sent.
 * The default speed of a serial port is 115200 bits/s. This gets divided by the
 * value of the `divisor` argument. The configured speed becomes
 * (115200 / divisor) bits/s.
 *
 * @param com     COM port to configure
 * @param divisor divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor) {
  outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
  outb(SERIAL_DATA_PORT(com), (divisor >> 4) & 0x00ff); // NOTE: shift by 4 or 8?
  outb(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

/**
 * Configures the line of the given serial port.
 * The configuration values are set as follows:
 *
 * Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
 * Content: | d | b | parity| s |  dl |
 * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
 *
 * dl:      data length, value of 11 sets it to 8 bits.
 * s:       number of stop bits. s = 0 means 1 stop bit.
 * parity:  number of parity bits to use.
 * b:       break control. b = 0 means its disabled.
 * d:       DLAB control. d = 1 means its enabled.
 */
void serial_configure_line(unsigned short com) {
  outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/**
 * Initializes the serial port for communcation.
 * Uses the base port defined for COM1 in serial.h.
 */
void serial_initialize() {
  serial_configure_baud_rate(SERIAL_COM1_BASE, 4);
  serial_configure_line(SERIAL_COM1_BASE);
}

/**
 * Checks whether the transmit FIFO queue is empty for the given COM port.
 *
 * @param com the COM port
 * @return  0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com) {
  /**
   * 0x20 = 0010 0000
   * This reads the 5th byte which is set if the transmission buffer is empty.
   */
  return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/**
 * Writes a byte to the given COM port.
 * Waits until the FIFO queue is empty.
 *
 * @param com   the COM port
 * @param byte  the byte to write
 */
void serial_write_byte(unsigned int com, char byte) {
  while(serial_is_transmit_fifo_empty(SERIAL_COM1_BASE) == 0);
  outb(SERIAL_DATA_PORT(com), byte);
}

/**
 * Writes to the given COM port.
 *
 * @param com   the COM port to use
 * @param start points to the start of the content to be written
 * @param size  size of the content
 */
void serial_write(unsigned int com, char *start, unsigned int size) {
  for (unsigned int i = 0; i < size; i++) {
    serial_write_byte(com, start[i]);
  }
}
