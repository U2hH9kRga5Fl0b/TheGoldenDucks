
#include "tabbed_window.hpp"

#include "tab.hpp"
#include "common.hpp"

#include <algorithm>
#include <curses.h>


TabbedWindow::TabbedWindow(const std::string& name_) :
		name{name_},
		tabs{},
		focus{-1},
		focus_on_panel{false} {}

TabbedWindow::~TabbedWindow()
{
	std::for_each(tabs.begin(), tabs.end(), [](const Tab* t){ delete t;});
}

int TabbedWindow::create_tab(const std::string& name)
{
	int size = tabs.size();
	for (int i = 0; i < size; i++)
	{
		if (tabs.at(i)->get_name() == name)
		{
			return i;
		}
	}
	tabs.push_back(new Tab { name });
	return focus = tabs.size() - 1;
}

bool TabbedWindow::destroy_tab(const std::string& name)
{
	auto end = tabs.end();
	for (auto it = tabs.begin(); it != end; ++it)
	{
		if ((*it)->get_name() != name)
		{
			continue;
		}
		delete *it;

		tabs.erase(it);
		return true;
	}
	return false;
}

Tab& TabbedWindow::get_tab(int index)
{
	return *tabs.at(index);
}

Tab& TabbedWindow::get_tab(const std::string& name)
{
	auto end = tabs.end();
	for (auto it = tabs.begin(); it != end; ++it)
	{
		if ((*it)->get_name() == name)
		{
			return **it;
		}
	}
	return *tabs.at(-1);
}

void TabbedWindow::display()
{
	int nh, nw;
	getmaxyx(stdscr, nh, nw);
	WINDOW* win = get_curses_window();

	werase(win);

	wresize(win, nh-2, nw);
	mvwin(win, 0, 0);

	wattron(win, COLOR_PAIR(BACKGROUND_COLOR));
	wbkgd(win, COLOR_PAIR(BACKGROUND_COLOR));
	box(win, 0, 0);

	wattron(win, COLOR_PAIR(META_COLOR));
	mvwprintw(win, 1, 1, name.c_str());

	int current_column = 1;

	mvwprintw(win, 2, current_column, " | ");
	current_column += 3;

	int index = 0;
	auto end = tabs.end();
	for (auto it = tabs.begin(); it != end; ++it, index++)
	{
		if (!focus_on_panel && index == focus)
		{
			wattron(win, A_UNDERLINE);
		}
		mvwaddstr(win, 2, current_column, (*it)->get_name().c_str());
		current_column += (*it)->get_name().size();
		if (!focus_on_panel && index == focus)
		{
			wattroff(win, A_UNDERLINE);
		}

		mvwaddstr(win, 2, current_column, " | ");
		current_column += 3;
	}

	if (focus >= 0)
	{
		tabs.at(focus)->display(win, Location{3, 1}, Location{nh-5, nw-2});
	}


	wattron(win, COLOR_PAIR(META_COLOR));
	mvwaddstr(win, nh-4, 1, statusstr.c_str());

	wrefresh(win);

}

void TabbedWindow::status(const std::string& status_string)
{
	statusstr = status_string;
	display();
}

bool TabbedWindow::capture()
{
	int ch = wgetch(get_curses_window());

	switch(ch)
	{
		case 52: // KEY_LEFT
			if (focus_on_panel && focus >= 0)
			{
				tabs.at(focus)->left();
			}
			else
			{
				focus = (focus-1) % tabs.size();
			}
			display();
			break;
		case 54: // KEY_RIGHT
			if (focus_on_panel && focus >= 0)
			{
				tabs.at(focus)->right();
			}
			else
			{
				focus = (focus+1) % tabs.size();
			}
			display();
			break;
		case 50: // DOWN
			if (focus_on_panel && focus >= 0)
			{
				tabs.at(focus)->down();
			}
			else
			{
				focus_on_panel = true;
			}
			display();
			break;
		case 56: // UP
			if (focus_on_panel && focus >= 0)
			{
				if (!tabs.at(focus)->up())
				{
					focus_on_panel = false;
				}
			}
			display();
			break;
		case 113: // KEY q
			return false;
		default:
			std::stringstream ss;
			ss << "Unrecognized key: " << ch;
			status(ss.str());
	}
	return true;
}

int TabbedWindow::get_num_tabs()
{
	return tabs.size();
}
