/**  @file   cannon.h
     @author Yeni Choi
     @date   14 Oct 2023
     @brief  LED driver.

    @defgroup LED LED driver
       
    This module implements the firing of the cannon

    Here's an example application that turns on a LED:

    @code
    #include "led.h"

    void main (void)
    {
        system_init ();
        led_init ();

        led_set (LED1, 1);

        while (1)
        {
        }
    }
    @endcode
*/

#ifndef CANNON_H
#define CANNON_H

#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "display.h"
#include "timer.h"

void fire_cannon(void);

#endif 

