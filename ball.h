/**  @file   move.h
     @author Yeni Choi, Mukhriz Khairudin 
     @date   14 Oct 2023
     @brief  Cannon ball driver and reader
    
*/

#ifndef BALL_H
#define BALL_H

#include "system.h"
#include "tinygl.h"

/** Allows cannon ball to fire from cannon and sets ir sensor to transmit data */
void cannonball_fire(tinygl_point_t pos_cannon1);

/** Allows funkit to read the recieved data from ir sensor and ball is recieved */
void ball_incoming(void);


#endif 