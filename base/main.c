#include "hw_init.h"
#include "sleep.h"
#include <libopencm3/stm32/gpio.h>

int main(void) {
	hw_init();

    /* Blink the LED (PC13) on the board with every transmitted byte. */
    while (1) {
        gpio_toggle(GPIOC, GPIO13); /* LED on/off */
        msleep(500);
    }
    return 0;
}
