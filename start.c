#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "ledmat.h"
#include "move.h"
#include "tinygl.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "timer.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "start.h"


void flashing_display(void) 
{
    uint8_t current_row;
    uint8_t current_column;
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


void display_column(uint8_t row_pattern, uint8_t current_column)
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

void user_select(void)
{
    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
    }
}

void sync(void) 
{
    tinygl_font_set(&font3x5_1);
    tinygl_text("PUSH TO START ");
    while (1) {
         /* Call the tinygl update function. */
        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        navswitch_update();
        if (navswitch_push_event_p(NAVSWITCH_NORTH) || navswitch_push_event_p(NAVSWITCH_EAST) || navswitch_push_event_p(NAVSWITCH_SOUTH) || navswitch_push_event_p(NAVSWITCH_WEST)) {
          ir_uart_putc ('S');
          break;
            }
        else if (ir_uart_read_ready_p ())
        {
            if (ir_uart_getc() == 'S'){
                break;
            }
        }
    }
}

void character_select(void) 
{
    // tinygl_init(PACER_RATE);

    uint8_t current_column = 0;
    uint16_t count = 0;

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {

        tinygl_text("  BIRD   ");
        // timer_get();

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
    sync();
    tinygl_font_set(&font5x7_1);
    tinygl_text("  3  2  1  GO!");
    
    while (count < 5250) {
        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        count++;
    }

    for (int i = 0; i < 4; i++) {
        flashing_display();
    }
}
