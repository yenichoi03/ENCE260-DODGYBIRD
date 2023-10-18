#include "system.h"
#include "navswitch.h"
#include "pio.h"
#include "tinygl.h"
#include "ledmat.h"
#include "move.h"

#define ON 1
#define OFF 0


void move_cannon(tinygl_point_t *pos_cannon1, tinygl_point_t* pos_cannon2) 
{
    /* Can only shoot from rows 0-5*/

    // Check for North button press
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        // Ensure the cannon position is within bounds
        if ((*pos_cannon1).y > 0) {
            // Clear the previous cannon position
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, OFF);
            // Move the cannon up
            (*pos_cannon1).y--;
            (*pos_cannon2).y--;
            // Draw the cannon in its new position
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, ON);
        }
    }

    // Check for South button press
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        // Ensure the cannon position is within bound
        if ((*pos_cannon1).y < LEDMAT_ROWS_NUM - 2) {
            // Clear the previous cannon position
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, OFF);
            // Move the cannon down
            (*pos_cannon1).y++;
            (*pos_cannon2).y++;
            tinygl_draw_line(*pos_cannon1, *pos_cannon2, ON);
        }
    }

}


void move_bird(void)
{
    /* Can only dodge from rows 1-6 */
    static tinygl_point_t pos1 = {1, 4};
    static tinygl_point_t pos2 = {3, 4};
    static tinygl_point_t pos_tip = {2, 3}; 

    // Draw the initial bird position
    tinygl_draw_line(pos1, pos2, ON);
    tinygl_draw_point(pos_tip, ON);

    // Check for North button press
    if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
        // Ensure the bird position is within bounds
        if (pos1.y > 2) {
            // Clear the previous bird position
            tinygl_draw_point(pos_tip, OFF);
            tinygl_draw_line(pos1, pos2, ON);
            // Move the bird up
            pos1.y--;
            pos2.y--;
            pos_tip.y--;
            // Draw the bird in its new position
            tinygl_draw_line(pos1, pos2, ON);
            tinygl_draw_point(pos_tip, ON);
            
        }
    }

    // Check for South button press
    if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
        // Ensure the bird position is within bounds
        if (pos1.y < LEDMAT_ROWS_NUM - 1) {
            // Clear the previous bird position
            tinygl_draw_point(pos_tip, OFF);
            tinygl_draw_line(pos1, pos2, OFF);
            // Move the bird down
            pos1.y++;
            pos2.y++;
            pos_tip.y++;
            tinygl_draw_line(pos1, pos2, ON);
            tinygl_draw_point(pos_tip, ON);

        }
    }

    // Check for East button press
    if (navswitch_push_event_p(NAVSWITCH_EAST)) {
        // Clear the previous bird position
        if (pos2.x < LEDMAT_COLS_NUM - 1) {
            tinygl_draw_point(pos_tip, OFF);
            tinygl_draw_line(pos1, pos2, OFF);
            // Move the bird to the right
            pos1.x++;
            pos2.x++;
            pos_tip.x++;
            tinygl_draw_line(pos1, pos2, ON);
            tinygl_draw_point(pos_tip, ON);

        }
    }

    // Check for West button press
    if (navswitch_push_event_p(NAVSWITCH_WEST)) {
        // Ensure the bird position is within bounds
        if (pos1.x > LEDMAT_COLS_NUM - 5) {
            // Clear the previous bird position
            tinygl_draw_point(pos_tip, OFF);
            tinygl_draw_line(pos1, pos2, OFF);
            // Move the bird to the left
            pos1.x--;
            pos2.x--;
            pos_tip.x--;
            tinygl_draw_line(pos1, pos2, ON);
            tinygl_draw_point(pos_tip, ON);
        }
    }
}
    



    










