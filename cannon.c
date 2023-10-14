#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "display.h"
#include "timer.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

void fire_cannon(void)
{
    system_init();
    led_init();

    /* Initialise port to drive LED 1.  */
    DDRC|=(1<<2);
    DDRD &= ~(1<<7);


    if (navswitch_down_p(NAVSWITCH_PUSH)) {

        while (1) {
            if ((PIND & (1<<7)) != 0) {
                PORTC |= (1<<2); 
            } else {
                PORTC |= (0<<2);   
            }
        }
    }
}



