/*
 * common.h
 *
 *  Created on: Oct 27, 2014
 *      Author: thallock
 */

#ifndef COMMON_H_
#define COMMON_H_


#include <curses.h>

void die_now();
WINDOW* get_curses_window();
extern bool stop_now;




#define BACKGROUND_COLOR        1
#define META_COLOR              2
#define DISPLAY_COLOR           3



#endif /* COMMON_H_ */
