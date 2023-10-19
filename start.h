/**  @file   move.h
     @author Yeni Choi, Mukhriz Khairudin
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

#ifndef START_H
#define START_H

#include <stdint.h>

// Constants for game control
#define PACER_RATE 500
#define MESSAGE_RATE 20

static const uint8_t bitmap1[] = {0, 4, 38, 36, 0};
static const uint8_t bitmap2[] = {0, 16, 24, 16, 0};
static const uint8_t bitmap3[] = {0, 0, 0, 16, 16, 0};


void flashing_display(void);

/* Function to display a specific column of the LED matrix. */
void display_column(uint8_t row_pattern, uint8_t current_column);

/* Function for user selection. Clears the TinyGL display on push. */
void user_select(void);

/* Synchronization function to wait for a push event. */
void sync(void);

/* Function for character selection based on NavSwitch input. */
void character_select(void);

#endif 