#include "system.h"
#include "pacer.h"
#include "tinygl.h"
#include "../fonts/font3x5_1.h"
#include "navswitch.h"
#include "display.h"

#define PACER_RATE 500
#define MESSAGE_RATE 10

void user_select(void)
{
    if (navswitch_release_event_p(NAVSWITCH_PUSH)) {
        tinygl_clear();
    }
}

// void character_select(void)
// {

// }


int main(void)
{
    /* Initialise */
    system_init();
    pacer_init(PACER_RATE);
    display_init();

    /* Initialise tinygl. */
    tinygl_init(PACER_RATE);
    tinygl_font_set(&font3x5_1);
    tinygl_text_speed_set(MESSAGE_RATE);
    tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);


    /* Set the message using tinygl_text().  */
    tinygl_text("CHOOSE CHARACTER ");
    
    while (1) {
        user_select();
        /* Call the tinygl update function. */
        pacer_wait(); // Wait until next pacer tick.  
        tinygl_update();  // Update display (refresh display and update message).  
        navswitch_update();

    }
    
    return 0;

}