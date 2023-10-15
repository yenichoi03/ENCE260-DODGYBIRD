#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "navswitch.h"
#include "ledmat.h"
#include "move.h"
#include "timer.h"
#include "led.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10


void timer_delay_ms(uint16_t milliseconds)
{
    uint16_t value = (milliseconds * 7810) ;

    /* Calculates the timer/counter value needed for the given number of milliseconds. */

    while (TCNT1 < value) {   
        continue;
    }
    TCNT1 = 0;
} 


void fire_cannon(int* led_on_ticks)
{
    navswitch_update();

    if (navswitch_down_p(NAVSWITCH_PUSH)) {

        led_set(LED1, 1);
        *led_on_ticks = 900;
    } else {
        led_set(LED1, 0);
    }

}



int main(void) 
{
    /* Initialise */

    system_init();
    navswitch_init();
    led_init();
    timer_init();

    int led_on_ticks = 0;
    int fire_held_down_for = 0;
    while (1) {
        if (led_on_ticks == 0) {
            led_set(LED1, 0);
        }
        pacer_wait();
        fire_cannon(&led_on_ticks, &fire_held_down_for);
        # other functions (ir, move_ball functions)
        led_on_ticks--;
    }


}



