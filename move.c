#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "pio.h"

#define ROW1 PIO_DEFINE(PORT_B, 0)
#define ROW2 PIO_DEFINE(PORT_B, 1)
#define ROW3 PIO_DEFINE(PORT_B, 2)
#define ROW4 PIO_DEFINE(PORT_B, 3)
#define ROW5 PIO_DEFINE(PORT_B, 4)
#define ROW6 PIO_DEFINE(PORT_B, 5)
#define ROW7 PIO_DEFINE(PORT_B, 6)
#define COL1 PIO_DEFINE(PORT_C, 5) 
#define COL2 PIO_DEFINE(PORT_C, 7) 
#define COL3 PIO_DEFINE(PORT_C, 4) 
#define COL4 PIO_DEFINE(PORT_B, 7) 
#define COL5 PIO_DEFINE(PORT_C, 6) 

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

static uint8_t prev_col = 0;

static void display_column(uint8_t row_pattern, uint8_t current_column)
{
    /* TODO */
   
    pio_output_high(cols[prev_col]);
    int current_row = 0;

    for (int i = 0; i < 7; i++) {
        current_row = i; 
    if ((row_pattern >> current_row) & 1) {
        pio_output_low(rows[current_row]);
    } else {
        pio_output_high(rows[current_row]);
        }
    }
    prev_col = current_column;
    pio_output_low(cols[current_column]);
}


int main (void)
{

    system_init ();
    navswitch_init ();

    /* TODO: Initialise IR driver.  */


    pacer_init (PACER_RATE);
    uint8_t current_column = (3);
    uint8_t current_row = (1<<4);
    uint8_t current_row2 = (3<<3);
    uint8_t current_row3 = (1<<4);
    int count = 0;
  
    system_init ();
    pacer_init (500);
    pio_config_set( ROW7 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW1 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW2 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW3 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW4 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW5 , PIO_OUTPUT_HIGH);
    pio_config_set( ROW6 , PIO_OUTPUT_HIGH);
    
    pio_config_set( COL1 , PIO_OUTPUT_HIGH);
    pio_config_set( COL2 , PIO_OUTPUT_HIGH);
    pio_config_set( COL3 , PIO_OUTPUT_HIGH);
    pio_config_set( COL4 , PIO_OUTPUT_HIGH);
    pio_config_set( COL5 , PIO_OUTPUT_HIGH);
 


    while (1)
    {
        pacer_wait ();
        navswitch_update ();
        
        if ((navswitch_push_event_p (NAVSWITCH_EAST))&&(current_column+1 < 4)){
                current_column++;      
                count++;   
        }
        if ((navswitch_push_event_p (NAVSWITCH_WEST))&&(current_column-1 > 0)){
                current_column--;    
                count++;
        }
        if ((navswitch_push_event_p (NAVSWITCH_NORTH))&&(current_row != (2<<0))){
                current_row = (current_row>>1);
                current_row2 = (current_row2>>1);
                current_row3 = (current_row3>>1);
                count++;
        }
       if ((navswitch_push_event_p (NAVSWITCH_SOUTH))&&(current_row != (1<<5))){
                current_row = (current_row<<1);
                current_row2 = (current_row2<<1);
                current_row3 = (current_row3<<1);
                count++;
        }           
        

        
        display_column(current_row, current_column-1);
        pacer_wait();
        display_column(current_row2, current_column);
        pacer_wait();
        display_column(current_row3, current_column+1);
        
    }

    return 0;
}
