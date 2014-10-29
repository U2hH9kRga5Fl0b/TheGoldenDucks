/*
 * listenthread.cpp
 *
 *  Created on: Oct 27, 2014
 *      Author: thallock
 */

#include "listenthread.hpp"

#include "common.hpp"
#include "tabbed_window.hpp"
#include "util.hpp"

#include <thread>

void listen_for_input()
{
	TabbedWindow& window = get_tabbed_window();

	do
	{
		int num_tabs = window.get_num_tabs();
		for (int i = 0; i < num_tabs; i++)
		{
			Tab& t = window.get_tab(i);
			std::lock_guard < std::recursive_mutex > locb { t.get_mutex() };
			t.flush();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1500));
	}
	while (!stop_now);
}
