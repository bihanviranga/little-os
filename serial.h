#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/* All the I/O ports are calculated relative to the data port. */
#define SERIAL_COM1_BASE                0x3f8
#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* Tells the serial port to expect the highest 8 bits first, and the lower bits next*/
#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_configure_baud_rate(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
void serial_initialize();
int serial_is_transmit_fifo_empty(unsigned int com);
void serial_write_byte(unsigned int com, char byte);
void serial_write(unsigned int com, char* start, unsigned int size);

#endif
