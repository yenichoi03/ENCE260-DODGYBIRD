#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "pio.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "timer.h"
#include "usart1.h"
#include "ledmat.h"
#include "move.h"




void move_cannon(tinygl_point_t *pos_cannon1) 
{
    /* Can only shoot from rows 0-5*/
    
    static tinygl_point_t pos_cannon2 = {3, 5};

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if ((*pos_cannon1).y > 0) {
            tinygl_draw_line(*pos_cannon1, pos_cannon2, 0);
            (*pos_cannon1).y--;
            pos_cannon2.y--;
            tinygl_draw_line(*pos_cannon1, pos_cannon2, 1);
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if ((*pos_cannon1).y < LEDMAT_ROWS_NUM - 2) {
            tinygl_draw_line(*pos_cannon1, pos_cannon2, 0);
            (*pos_cannon1).y++;
            pos_cannon2.y++;
            tinygl_draw_line(*pos_cannon1, pos_cannon2, 1);
        }
    }

}

void cannonball_fire(tinygl_point_t pos_cannon1)
{
    static int count = 0;
    static bool is_ball = false;
    static tinygl_point_t pos_ball = {0, 0}; 

    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        is_ball = true;
    }

    if (is_ball) {
        count++;

        if (count == 50) {
            pos_ball.x = 2;
            pos_ball.y = pos_cannon1.y;
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

    tinygl_draw_line(pos1, pos2, 1);
    tinygl_draw_point(pos_tip, 1);


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
}
    
void ball_incoming(void)
{
    static tinygl_point_t life_pos1 = {2, 0};
    static tinygl_point_t life_pos2 = {5, 0};
    static tinygl_point_t life_pos3 = {2, 0};
    static tinygl_point_t life_pos4 = {4, 0};
    tinygl_draw_line(life_pos1, life_pos2, 1);
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



    










