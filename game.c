#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "../fonts/font5x7_1.h"
#include "navswitch.h"
#include "timer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "move.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"


#define PACER_RATE 500
#define MESSAGE_RATE 20

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
static const uint8_t bitmap3[] = {0, 0, 0, 16, 16, 0};


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

void user_select(void)
{
    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
    }
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

    for (int i = 0; i < 4; i++) {
        flashing_display();
    }
}

    


int main(void) 
{

    /* Initialise libraries*/
    system_init();
    ir_uart_init();
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
    int select_char = 0;
  

    while (1) {
        pacer_wait();
        display_column(bitmap1[current_column], current_column);
        current_column++;
    
        if (current_column > (LEDMAT_COLS_NUM - 1)) {
            current_column = 0;
        }  

        if (navswitch_push_event_p(NAVSWITCH_NORTH)){
            select_char = 1;
            break;
        }
        if (navswitch_push_event_p(NAVSWITCH_SOUTH)){
            select_char = 2;
            break;
        }   

        navswitch_update(); 
    }    

    character_select();
    flashing_display();
    tinygl_clear();
    // uint16_t game_over_ticks = 5000;

    if (select_char == 1){
        while (1) {
            move_bird();
            tinygl_update();
            navswitch_update();
            pacer_wait();


            // game_over_ticks--;

            // if (game_over_ticks == 0) {
            //     break;
            // }
        }
    }

    if (select_char == 2){
        while (1) {
            move_cannon();
            tinygl_update();
            navswitch_update();
            pacer_wait();
            // game_over_ticks--;

            // if (game_over_ticks == 0) {
            //     break;
            // }
        }
    }

    // tinygl_text("GAME OVER");

    // while(1) {
    //     game_over_ticks++;
    //     pacer_wait(); 
    //     tinygl_update();

    //     if (game_over_ticks == 5500) {
    //         break;
    //     }
    // }
    // display_clear();
    return 0;

}



