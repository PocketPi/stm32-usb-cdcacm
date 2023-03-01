#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include <stddef.h>


static void clock_setup(void)
{
	/* Enable GPIOD clock for LED & USARTs. */
	rcc_periph_clock_enable(RCC_GPIOC);
}

static void gpio_setup(void)
{
	/* Setup GPIO pin GPIO5 on GPIO port A for LED. */
	gpio_mode_setup(GPIOC, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13);
}

int main(void)
{
	clock_setup();
	gpio_setup();

	/* Blink the LED (PC13) on the board with every transmitted byte. */
	while (1) {
		gpio_toggle(GPIOC, GPIO13);	/* LED on/off */
		for (size_t i = 0; i < 1000000; i++) {	/* Wait a bit. */
				__asm__("NOP");
		}
	}
	return 0;
}
