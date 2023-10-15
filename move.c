#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "pio.h"
#include "tinygl.h"

// void move_bird(void)
// {

//     system_init();
//     navswitch_init();
//     pacer_init(PACER_RATE);
//     ledmat_init();
 
//     uint8_t current_row = 2;
//     uint8_t current_column =  0b0010000;
//     uint8_t current_column2 = 0b0011000;
//     uint8_t current_column3 = 0b0010000;
//     uint8_t x = 3
//     uint8_t y = 4;
//     int time = 0;

//     while (1)
//     {
       
//         if (time >= 1666){
//         break;
// }
//         pacer_wait();
//         navswitch_update();
        
//         if ((navswitch_push_event_p(NAVSWITCH_EAST)) && (current_row + 1 < 4)){
//                 current_row++;
//         }
//         if ((navswitch_push_event_p(NAVSWITCH_WEST)) && (current_row - 1 > 0)){
//                 current_row--;    
//         }

//         if ((navswitch_push_event_p(NAVSWITCH_NORTH)) && (current_column != (2<<0))){
//                 current_column = (current_column>>1);
//                 current_column2 = (current_column2>>1);
//                 current_column3 = (current_column3>>1);
//         }
//        if ((navswitch_push_event_p(NAVSWITCH_SOUTH)) && (current_column != (1<<5))){
//                 current_column = (current_column<<1);
//                 current_column2 = (current_column2<<1);
//                 current_column3 = (current_column3<<1);

//         }           
        
//         display_column(current_column, current_row - 1);
//         pacer_wait();
//         display_column(current_column2, current_row);
//         pacer_wait();
//         display_column(current_column3, current_row + 1);
//         time += 1;
     

//     }

// }



void move_cannon(void) {

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
        }
    }
}

