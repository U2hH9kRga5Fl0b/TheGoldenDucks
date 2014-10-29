/*
 * common.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: thallock
 */


#include "common.hpp"

#include <iostream>

bool stop_now;
WINDOW* ncurses_window;

void die_now()
{
	std::cerr << "leaving because of previous errors..." << std::endl;
	exit(-1);
}

WINDOW* get_curses_window()
{
	return ncurses_window;
}
