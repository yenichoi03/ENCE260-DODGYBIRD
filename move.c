#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "pio.h"
#include "ledmat.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

/* Define PIO pins driving LED matrix rows. */
static const pio_t rows[] =
{
    LEDMAT_ROW1_PIO, LEDMAT_ROW2_PIO, LEDMAT_ROW3_PIO, 
    LEDMAT_ROW4_PIO, LEDMAT_ROW5_PIO, LEDMAT_ROW6_PIO,
    LEDMAT_ROW7_PIO
};

/* Define PIO pins driving LED matrix columns. */
static const pio_t cols[] =
{
    LEDMAT_COL1_PIO, LEDMAT_COL2_PIO, LEDMAT_COL3_PIO,
    LEDMAT_COL4_PIO, LEDMAT_COL5_PIO
};


static void display_column(uint8_t row_pattern, uint8_t current_column)
{
    static uint8_t prev_col = 0;
    pio_config_set(cols[prev_col], PIO_OUTPUT_HIGH);

    for (uint8_t current_row = 0; current_row < LEDMAT_ROWS_NUM; current_row++) {

        if ((row_pattern >> current_row) & 1) {
            pio_output_low(rows[current_row]);
        } else {
            pio_output_high(rows[current_row]);
        }
    }

    prev_col = current_column;
    pio_config_set(cols[current_column], PIO_OUTPUT_LOW);
}


void move_bird(void)
{

    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    ledmat_init();
 
    uint8_t current_row = 2;
    uint8_t current_column =  0b0010000;
    uint8_t current_column2 = 0b0011000;
    uint8_t current_column3 = 0b0010000;
    uint8_t x = 3
    uint8_t y = 4;
    int time = 0;

    while (1)
    {
       
        if (time >= 1666){
        break;
}
        pacer_wait();
        navswitch_update();
        
        if ((navswitch_push_event_p(NAVSWITCH_EAST)) && (current_row + 1 < 4)){
                current_row++;
        }
        if ((navswitch_push_event_p(NAVSWITCH_WEST)) && (current_row - 1 > 0)){
                current_row--;    
        }

        if ((navswitch_push_event_p(NAVSWITCH_NORTH)) && (current_column != (2<<0))){
                current_column = (current_column>>1);
                current_column2 = (current_column2>>1);
                current_column3 = (current_column3>>1);
        }
       if ((navswitch_push_event_p(NAVSWITCH_SOUTH)) && (current_column != (1<<5))){
                current_column = (current_column<<1);
                current_column2 = (current_column2<<1);
                current_column3 = (current_column3<<1);

        }           
        
        display_column(current_column, current_row - 1);
        pacer_wait();
        display_column(current_column2, current_row);
        pacer_wait();
        display_column(current_column3, current_row + 1);
        time += 1;
     

    }

}

void move_cannon(void)
{
    system_init();
    navswitch_init();
    pacer_init(PACER_RATE);
    ledmat_init();
    uint8_t current_column = 3;
    uint8_t current_column3 = 0b0001000;
    uint8_t current_column4 = 0b0001000;
    int time = 0;
    while (1)
    {
         if (time >= 1666){
        break;
}
        navswitch_update();

        if (navswitch_push_event_p(NAVSWITCH_NORTH) && (current_column3 != (1<<0))){
            current_column3 = current_column3 >> 1;
            current_column4 = current_column4 >> 1;
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH) && (current_column3 != (1<<5))){
            current_column3 = current_column3 << 1;
            current_column4 = current_column4 << 1;
        }           
 
        display_column(current_column3, current_column);
        pacer_wait();
        display_column(current_column4, current_column + 1);
        pacer_wait();
        time += 1;

    }
}

