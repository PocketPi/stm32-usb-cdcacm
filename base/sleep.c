#include "sleep.h"
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>

/* monotonically increasing number of milliseconds from reset
 * overflows every 49 days if you're wondering
 */
static volatile uint32_t system_millis;

/* Called when systick fires */
void sys_tick_handler(void) {
    system_millis++;
}

/* sleep for delay milliseconds */
void msleep(uint32_t delay) {
    uint32_t wake = system_millis + delay;
    while (wake > system_millis)
        ;
}