/**  @file   move.h
     @author Yeni Choi, Mukhriz Khairudin
     @date   14 Oct 2023
     @brief  Implements the movement of the bird and cannon characters 

*/

#ifndef MOVE_H
#define MOVE_H

#include "system.h"
#include "tinygl.h"

/** Defines PIO pins driving LED matrix rows.  */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/** Defines PIO pins driving LED matrix columns.  */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};

/** Move the cannon character vertically.
   pos_cannon1 Pointer to the starting position of the cannon.
   pos_cannon2 Pointer to the ending position of the cannon.
*/
void move_cannon(tinygl_point_t* pos_cannon1, tinygl_point_t* pos_cannon2);

/* moves the bird character around the screen */
void move_bird(void);


#endif 
