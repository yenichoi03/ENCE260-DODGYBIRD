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

#ifndef MOVE_H
#define MOVE_H

#include "system.h"



static void display_column(uint8_t row_pattern, uint8_t current_column);

void move_bird(void);




#endif 