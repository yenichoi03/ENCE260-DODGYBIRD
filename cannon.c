#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
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
        PORTC |= (1<<2); 
    } else {
        PORTC |= (0<<2);   
    }
}



