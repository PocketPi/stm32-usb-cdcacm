#ifndef USB_PRINTF_H
#define USB_PRINTF_H

#include "queue.h"

#define USB_FIFO_SIZE 1024

DECLARE_FIFO(USB_TX_FIFO, char, USB_FIFO_SIZE)

FIFO_Result usb_fifo_get(char *c);
bool usb_fifo_is_empty(void);

#endif