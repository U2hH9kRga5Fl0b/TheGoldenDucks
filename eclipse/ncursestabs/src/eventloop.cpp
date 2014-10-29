/*
 * eventloop.cpp
 *
 *  Created on: Oct 28, 2014
 *      Author: thallock
 */

#include "eventloop.hpp"

#include "common.hpp"
#include "tabbed_window.hpp"
#include "util.hpp"

void event_loop()
{
	while(get_tabbed_window().capture() && !stop_now)
		;

	close();
}
