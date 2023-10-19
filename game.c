/**  @file   game.c
     @author Yeni Choi, Mukhriz Khairudin 
     @date   14 Oct 2023
     @brief  Main game component
    
*/
#include "system.h"
#include "pacer.h"
#include "pio.h"
#include "tinygl.h"
#include "navswitch.h"
#include "timer.h"
#include "ledmat.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "move.h"
#include "ir_uart.h"
#include "usart1.h"
#include "timer0.h"
#include "start.h"
#include "ball.h"


/* Allows gameplayt for both cannon and bird characters*/
int main(void) 
{

    system_init();
    ir_uart_init();
    pacer_init(PACER_RATE);
    display_init();

    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
  
    tinygl_text("CHOOSE CHARACTER ");
    
    while (navswitch_up_p(NAVSWITCH_PUSH)) {
        user_select();
        pacer_wait();  
        tinygl_update(); 
        navswitch_update();
    }
    
    ledmat_init();
    uint8_t current_column = 0;
    int select_char = 0;
  
    /* Character selection loop */
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

    /* Character selection is complete, move to the game */
    character_select();
    tinygl_clear();

    int32_t game_ticks = 10000;

    if (select_char == 1){
        while (1) {
            move_bird();
            ball_incoming();
            tinygl_update();
            navswitch_update();
            pacer_wait();
            game_ticks--;

            if (game_ticks <= 0) {
                break;
            }
        }
    }

    if (select_char == 2) {
        /* Initialize cannon position */
        tinygl_point_t pos_cannon1 = {4, 5};
        tinygl_point_t pos_cannon2 = {3, 5};
        tinygl_draw_line(pos_cannon1, pos_cannon2, 1);

        while (1) {
            move_cannon(&pos_cannon1, &pos_cannon2);
            cannonball_fire(pos_cannon1);
            tinygl_update();
            navswitch_update();
            pacer_wait();
            game_ticks--;

            if (game_ticks <= 0) {
                break;
            }

        }

    }
    
    tinygl_clear();
    display_clear();
    ledmat_init();

    return 0;

}

