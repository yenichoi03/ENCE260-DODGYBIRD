/**  @file   move.c
     @author Yeni Choi, Mukhriz Khairudin 
     @date   14 Oct 2023
     @brief  Moves Bird and Cannon
    
*/
#include "system.h"
#include "navswitch.h"
#include "pio.h"
#include "tinygl.h"
#include "ledmat.h"
#include "move.h"


/* Allows movement of the cannon character in the vertical direction using the North and South navigation switches. */
void move_cannon(tinygl_point_t *pos_cannon1, tinygl_point_t* pos_cannon2) 
{

    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        if ((*pos_cannon1).y > 0) {
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, 0);
            (*pos_cannon1).y--;
            (*pos_cannon2).y--;
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, 1);
        }
    }

    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        if ((*pos_cannon1).y < LEDMAT_ROWS_NUM - 2) {
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, 0);
            (*pos_cannon1).y++;
            (*pos_cannon2).y++;
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, 1);
        }
    }

}

/* Allows movement of the bird character in all directions using the North, East, South, West navigation switches. */
void move_bird(void)
{
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
    



    










