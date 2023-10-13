#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "navswitch.h"
#include "display.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10


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

static const uint8_t bitmap[] =
{
    0, 4, 38, 36, 0
};


void user_select(void)
{
    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
    }
}

static void display_column(uint8_t row_pattern, uint8_t current_column)
{

    uint8_t current_row;
    static int prev_col = 0;
    pio_config_set(cols[current_column], PIO_OUTPUT_LOW);
    
    for (current_row = 0; current_row < LEDMAT_ROWS_NUM; current_row++) {

        if ((row_pattern >> current_row) & 1) {
            pio_output_low(rows[current_row]);
        } else {
            pio_output_high(rows[current_row]);
        }
    }

    pio_config_set(cols[prev_col], PIO_OUTPUT_HIGH);
    prev_col = current_column;
}



int main(void)
{
    /* Initialise */
    system_init();
    pacer_init(PACER_RATE);
    display_init();

    /* Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);

    /* Initialise LED matrix pins.  */
    uint8_t current_row;
    uint8_t current_column;


    /* Set the message using tinygl_text().  */
    tinygl_text("CHOOSE CHARACTER ");
    
    while (navswitch_up_p(NAVSWITCH_PUSH)) {

        user_select();

        /* Call the tinygl update function. */

        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        navswitch_update();

    }
    


    for (current_row = 0; current_row < LEDMAT_ROWS_NUM; current_row++) {
        /* The rows are active low so configure PIO as an initially high output.  */
        pio_config_set(rows[current_row], PIO_OUTPUT_HIGH);
    }

    for (current_column = 0; current_column < LEDMAT_COLS_NUM; current_column++) {
        /* The columns are active low so configure PIO as an initially high output.  */
        pio_config_set (cols[current_column], PIO_OUTPUT_HIGH);
    }


    while (1)
    {
        pacer_wait();
        display_column(bitmap[current_column], current_column);
        current_column++;
    
        if (current_column > (LEDMAT_COLS_NUM - 1)) {
            current_column = 0;
        }           
    }

    return 0;

}