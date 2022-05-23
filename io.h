#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/**
 * Sends given data to the given I/O port.
 *
 * @param port I/O port to send the data to
 * @param data data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

#endif
