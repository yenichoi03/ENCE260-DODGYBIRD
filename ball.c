#include "system.h"
#include "navswitch.h"
#include "tinygl.h"
#include "ir_uart.h"
#include "usart1.h"
#include "start.h"

/*fires ball from cannon*/
void cannonball_fire(tinygl_point_t pos_cannon1)
{
    static int count = 0;
    static bool is_ball = true;
    static tinygl_point_t pos_ball = {0, 0}; 

    if (navswitch_push_event_p(NAVSWITCH_PUSH)) {
        is_ball = false;
    }
    /*Ball is fired*/
    if (!is_ball) {
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
            is_ball = true;
            count = 0;

            if (ir_uart_write_ready_p()) {
                ir_uart_putc(pos_ball.y);
            }
        }
    }
}

/*Recieves ball from cannon*/
void ball_incoming(void)
{
    static tinygl_point_t life_pos1 = {2, 0};
    static tinygl_point_t life_pos2 = {5, 0};
    static tinygl_point_t pos_ball = {0, 0}; 

    static int count = 0;
    static uint8_t row = 0;
    static bool is_ball = false;
    bool flash = false; 

    uint8_t row_num[LEDMAT_ROWS_NUM - 1] = {6, 5, 4, 3, 2, 1};

    /*This draws the healthline*/
    tinygl_draw_line(life_pos1, life_pos2, 1); 


    if (ir_uart_read_ready_p()) {
        row = ir_uart_getc(); 
        if (row < LEDMAT_ROWS_NUM) {
            is_ball = true;
        }
    }
    /*ball is fired*/
    if (is_ball) {
        count++;

        if (count == 50) {
            pos_ball.x = 0;
            pos_ball.y = row_num[row]; 
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
            tinygl_draw_line(life_pos1, life_pos2, 0);
            life_pos1.x++;
            tinygl_draw_line(life_pos1, life_pos2, 1);
            if (life_pos1.x >= 4 ) {
                tinygl_clear();
            }
        }
    }
}  


