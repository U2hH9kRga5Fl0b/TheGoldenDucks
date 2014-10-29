
#include "util.hpp"

#include "common.hpp"
#include "tabbed_window.hpp"
#include "listenthread.hpp"

#include <curses.h>
#include <thread>
#include <iostream>

extern WINDOW* ncurses_window;

namespace
{
	bool initialized;
	TabbedWindow *window;

	void* resizeHandler(int sig)
	{
		if (window != nullptr)
		{
			window->display();
		}
		return nullptr;
	}
}

void init(const std::string& name)
{
	if (initialized)
	{
		std::cerr << "Cannot initialize twice!" << std::endl;
		die_now();
	}

	initialized = true;
	window = new TabbedWindow(name);

	// fire up curses
	initscr();
	start_color();
	noecho();

	init_pair(1, COLOR_GREEN, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);
	init_pair(3, COLOR_MAGENTA, COLOR_WHITE);

	keypad (stdscr, TRUE);

	cbreak();
	refresh();

	ncurses_window = newwin(10, 40, 0, 0);
}

void close()
{
	if (!initialized)
	{
		return;
	}
	stop_now = true;

	// wait for listen thread to die. (Not actually running.)
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	delete window;
	window = nullptr;
	initialized = false;
	endwin();
}

TabbedWindow& get_tabbed_window()
{
	if (window == nullptr)
	{
		std::cerr << "Must call initialize!" << std::endl;
		die_now();
	}
	return *window;
}
