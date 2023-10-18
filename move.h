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
#include "tinygl.h"

/** Define PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Define PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

void display_character(char character);
/* A character buffer */

void move_cannon(tinygl_point_t* pos_cannon1);
/* moves the cannon character vertically */

void cannonball_fire(tinygl_point_t pos_cannon1);

void move_bird(void);
/* moves the bird character around the screen */

void flashing_display(void);

void ball_incoming(void);


#endif 
