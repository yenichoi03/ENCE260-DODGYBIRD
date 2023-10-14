#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "display.h"
#include "timer.h"
#include "ledmat.h"
#include "move.h"

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

static const uint8_t bitmap1[] = {0, 4, 38, 36, 0};
static const uint8_t bitmap2[] = {0, 16, 24, 16, 0};
static const uint8_t bitmap3[] = {0, 0, 8, 8, 0, 0};

void user_select(void)
{
    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
    }
}

static void display_column(uint8_t row_pattern, uint8_t current_column)
{
    static int prev_col = 0;
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

void character_select(void) 
{
    tinygl_init(PACER_RATE);

    uint8_t current_column = 0;
    uint16_t count = 0;

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {

        tinygl_text("  BIRD   ");
        timer_get();

        while (count < 2500) {

            pacer_wait(); // Wait until next pacer tick.  
            tinygl_update();  // Update display (refresh display and update message).  
            count++;
        }
        
        count = 0;
        while (count < 1000) {
            pacer_wait();
            display_column(bitmap2[current_column], current_column);
            current_column++;
    
            if (current_column > (LEDMAT_COLS_NUM - 1)) {
                current_column = 0;
            }
            count++;  
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {

        tinygl_text("  CANNON   ");
    
        while (count < 3000) {

            pacer_wait(); // Wait until next pacer tick.  
            tinygl_update();  // Update display (refresh display and update message).  
            count++;
        }

        count = 0;
        while (count < 1000) {
            pacer_wait();
            display_column(bitmap3[current_column], current_column);
            current_column++;
    
            if (current_column > (LEDMAT_COLS_NUM - 1)) {
                current_column = 0;
            }
            count++;  
        }
    }

    tinygl_font_set(&font5x7_1);
    tinygl_text("  3  2  1  GO!");
    
    while (count < 5250) {
        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        count++;
    }
}

void flashing_display(void) 
{
    uint8_t current_row;
    uint8_t current_column;

    for (int i = 0; i < 4; i++) {

        uint16_t count = 0;

        for (current_row = 0; current_row < LEDMAT_ROWS_NUM; current_row++) {
            /* The rows are active low so configure PIO as an initially high output.  */
            pio_config_set(rows[current_row], PIO_OUTPUT_LOW);
        }

        for (current_column = 0; current_column < LEDMAT_COLS_NUM; current_column++) {
            /* The columns are active low so configure PIO as an initially high output.  */
            pio_config_set (cols[current_column], PIO_OUTPUT_LOW);
        }

        
        while (count < 50) {
            pacer_wait();
            count++;
        }

        ledmat_init();

        count = 0;

        while (count < 80) {
            pacer_wait();
            count++;
        }
        
    }

}




int main(void)
{
    /* Initialise libraries*/
    system_init();
    pacer_init(PACER_RATE);
    display_init();
    timer_init();

    /* Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);


    /* Set the message using tinygl_text().  */
    tinygl_text("CHOOSE CHARACTER ");
    
    while (navswitch_up_p(NAVSWITCH_PUSH)) {

        user_select();

        /* Call the tinygl update function. */
        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        navswitch_update();
    }
    
    ledmat_init();
    uint8_t current_column = 0;

    while (1) {

        pacer_wait();
        display_column(bitmap1[current_column], current_column);
        current_column++;
    
        if (current_column > (LEDMAT_COLS_NUM - 1)) {
            current_column = 0;
        }  

        if (navswitch_push_event_p(NAVSWITCH_NORTH) || navswitch_push_event_p(NAVSWITCH_SOUTH)) {
            break;
        }

        navswitch_update();         
    }

    character_select();
    flashing_display();
    move_bird();

    return 0;

}