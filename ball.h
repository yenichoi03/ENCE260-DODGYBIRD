/**  @file   move.h
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

#ifndef BALL_H
#define BALL_H


#include "system.h"
#include "tinygl.h"

void cannonball_fire(tinygl_point_t pos_cannon1);

void ball_incoming(void);


#endif 