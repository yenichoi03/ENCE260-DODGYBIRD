#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "pio.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "timer.h"
#include "usart1.h"
#include "ledmat.h"



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

void move_cannon(void) 
{
    /* Can only shoot from rows 0-5*/
    
    static tinygl_point_t pos1 = {4, 3};
    static tinygl_point_t pos2 = {3, 3};
    static tinygl_point_t pos_ball = {0, 0}; 

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if (pos1.y > 0) {
            tinygl_draw_line(pos1, pos2, 0);
            pos1.y--;
            pos2.y--;
            tinygl_draw_line(pos1, pos2, 1);
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if (pos1.y < LEDMAT_ROWS_NUM - 2) {
            tinygl_draw_line(pos1, pos2, 0);
            pos1.y++;
            pos2.y++;
            tinygl_draw_line(pos1, pos2, 1);
        }
    }

    static int count = 0;
    static bool is_ball = false;

    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        is_ball = true;
    }

    if (is_ball) {
        count++;

        if (count == 50) {
            pos_ball.x = 2;
            pos_ball.y = pos1.y;
            tinygl_draw_point(pos_ball, 1);

        }

        if (count == 150) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x--;
            tinygl_draw_point(pos_ball, 1);
        }

        if (count == 250) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x--;
            tinygl_draw_point(pos_ball, 1);
        }

        if (count == 350) {
            tinygl_draw_point(pos_ball, 0);
            is_ball = false;
            count = 0;

            if (ir_uart_write_ready_p()) {
                ir_uart_putc(pos_ball.y);
            }
        }
    }

}


void move_bird(void)
{
    /* Can only dodge from rows 1-6 */
    static tinygl_point_t pos1 = {1, 4};
    static tinygl_point_t pos2 = {3, 4};
    static tinygl_point_t pos_tip = {2, 3}; 
    static tinygl_point_t life_pos1 = {2, 0};
    static tinygl_point_t life_pos2 = {5, 0};
    static tinygl_point_t life_pos3 = {2, 0};
    static tinygl_point_t life_pos4 = {4, 0};
    tinygl_draw_line(life_pos1, life_pos2, 1);
 

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if (pos1.y > 2) {
            tinygl_draw_point(pos_tip, 0);
            tinygl_draw_line(pos1, pos2, 0);
            pos1.y--;
            pos2.y--;
            pos_tip.y--;
            tinygl_draw_line(pos1, pos2, 1);
            tinygl_draw_point(pos_tip, 1);

        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if (pos1.y < LEDMAT_ROWS_NUM - 1) {
            tinygl_draw_point(pos_tip, 0);
            tinygl_draw_line(pos1, pos2, 0);
            pos1.y++;
            pos2.y++;
            pos_tip.y++;
            tinygl_draw_line(pos1, pos2, 1);
            tinygl_draw_point(pos_tip, 1);

        }
    }

    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        if (pos2.x < LEDMAT_COLS_NUM - 1) {
            tinygl_draw_point(pos_tip, 0);
            tinygl_draw_line(pos1, pos2, 0);
            pos1.x++;
            pos2.x++;
            pos_tip.x++;
            tinygl_draw_line(pos1, pos2, 1);
            tinygl_draw_point(pos_tip, 1);

        }
    }

    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        if (pos1.x > LEDMAT_COLS_NUM - 5) {
            tinygl_draw_point(pos_tip, 0);
            tinygl_draw_line(pos1, pos2, 0);
            pos1.x--;
            pos2.x--;
            pos_tip.x--;
            tinygl_draw_line(pos1, pos2, 1);
            tinygl_draw_point(pos_tip, 1);
        }
    }

    
    static int count = 0;
    static bool is_ball = false;
    static tinygl_point_t pos_ball = {0, 0}; 
    static uint8_t row = 0;
    uint8_t row_num[LEDMAT_ROWS_NUM - 1] = {6, 5, 4, 3, 2, 1};
    bool flash = false; 

    if (ir_uart_read_ready_p()) {
        row = ir_uart_getc(); 
        if (row < LEDMAT_ROWS_NUM) {
            is_ball = true;
        }
    }

    if (is_ball) {
        count++;

        if (count == 50) {
            pos_ball.x = 0;
            pos_ball.y = row_num[row]; // this has to be the position where the cannon fires
            tinygl_draw_point(pos_ball, 1);
        }

        if (count == 150) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x++;

            if (tinygl_pixel_get(pos_ball) == 1) { 
                flash = true;
            }

            tinygl_draw_point(pos_ball, 1);

        }

        if (count == 250) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x++;

            if (tinygl_pixel_get(pos_ball) == 1) { 
                flash = true;
            }

            tinygl_draw_point(pos_ball, 1);

        }

        if (count == 350) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x++;
            
            if (tinygl_pixel_get(pos_ball) == 1) { 
                flash = true;
            }

            tinygl_draw_point(pos_ball, 1);
        }

        if (count == 450) {
            tinygl_draw_point(pos_ball, 0);
            pos_ball.x++;
            tinygl_draw_point(pos_ball, 1);
        }

        if (count == 550) {
            tinygl_draw_point(pos_ball, 0);
            is_ball = false;
            count = 0;
        }
        
        
        if (flash) {
            flashing_display();
            /*Will need to create a struct*/
            tinygl_draw_line(life_pos1, life_pos2, 0);
            life_pos1.x++;
            tinygl_draw_line(life_pos1, life_pos2, 1);
            if (life_pos1.x >= 4 ) {
                tinygl_draw_line(life_pos3, life_pos4, 0);
            }
            
        }
    
    }
}



