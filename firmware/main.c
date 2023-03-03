#include "hw_init.h"
#include "sleep.h"
#include <libopencm3/stm32/gpio.h>
#include <stdio.h>

int main(void) {
    hw_init();
    size_t i = 0;

    /* Blink the LED (PC13) on the board with every transmitted byte. */
    while (1) {
        printf("Hello world: %d\n", i++);

        gpio_toggle(GPIOC, GPIO13); /* LED on/off */
        msleep(50);
    }
    return 0;
}
