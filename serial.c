#include "io.h"

/* All the I/O ports are calculated relative to the data port. */
#define SERIAL_COM1_BASE                0x3f8
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* Tells the serial port to expect the highest 8 bits first, and the lower bits next*/
#define SERIAL_LINE_ENABLE_DLAB         0x80

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
