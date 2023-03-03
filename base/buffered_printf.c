#include "buffered_printf.h"

DEFINE_FIFO(USB_TX_FIFO, char)
static USB_TX_FIFO usb_tx_fifo;
static bool fifo_initialized = false;

int _write(int fd, char *ptr, int len);

/*
 * Called by libc stdio fwrite functions
 */
int _write(int fd, char *ptr, int len) {
    int i = 0;
    char carrigereturn = '\r';

    if (fifo_initialized == false) {
        USB_TX_FIFO_init(&usb_tx_fifo);
    }

    /*
     * Write "len" of char from "ptr" to file id "fd"
     * Return number of char written.
     *
     * Only work for STDOUT, STDIN, and STDERR
     */
    if (fd > 2) {
        return -1;
    }
    while (*ptr && (i < len)) {
        USB_TX_FIFO_put(&usb_tx_fifo, ptr);
        if (*ptr == '\n') {
            USB_TX_FIFO_put(&usb_tx_fifo, &carrigereturn);
        }
        i++;
        ptr++;
    }
    return i;
}

FIFO_Result usb_fifo_get(char *c) {
    return USB_TX_FIFO_get(&usb_tx_fifo, c);
}

bool usb_fifo_is_empty(void) {
    return USB_TX_FIFO_is_empty(&usb_tx_fifo);
}
