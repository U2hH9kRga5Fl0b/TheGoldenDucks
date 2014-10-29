
#include "tab.hpp"

#include "writable.hpp"
#include "common.hpp"


#include <thread>
#include <mutex>
#include <iomanip>
#include <vector>
#include <set>

Tab::Tab(const std::string name_) :
		name{name_},

		displaying_lines{},
		displaying_atts{},
		maxcol{0},

		nextlines{},
		next_atts{},

		buffer_mutex{},
		buffer{},

		rowoffset{0},
		coloffset{0}
{
	displaying_lines.push_back("");
	nextlines.push_back("");
}

Tab::~Tab() {}

std::ostream& Tab::input()
{
	return buffer;
}
std::recursive_mutex& Tab::get_mutex()
{
	return buffer_mutex;
}

void Tab::setColors(int foreground, int background)
{
	std::lock_guard<std::recursive_mutex> locb{buffer_mutex};
}

void Tab::delim()
{
	std::lock_guard<std::recursive_mutex> locb{buffer_mutex};
	flush();
	displaying_lines = nextlines;
	displaying_atts = next_atts;
	nextlines.clear();
	nextlines.push_back("");
	next_atts.clear();

	int numrows = displaying_lines.size();
	maxcol = -1;
	for (int i = 0; i < numrows; i++)
	{
		maxcol = std::max(maxcol, (int) displaying_lines.at(i).size());
	}
	rowoffset = std::min(rowoffset, (int) displaying_lines.size());
	coloffset = std::min(coloffset, maxcol);
}

bool Tab::flush()
{
	std::lock_guard<std::recursive_mutex> locb{buffer_mutex};

	std::string str;
	{
		str = buffer.str();
		buffer.str("");
	}
	if (str.size() == 0)
	{
		return false;
	}

	for (int i = 0; i < (int) str.size(); i++)
	{
		if (str.at(i) == '\n')
		{
			nextlines.back() += str.substr(0, i);
			str = str.substr(i+1, std::string::npos);
			i = 0;
			nextlines.push_back("");
		}
	}

	nextlines.back() += str;
	return true;
}


void Tab::display(WINDOW* window, Location&& start, Location&& end)
{
	std::lock_guard<std::recursive_mutex> locb{buffer_mutex};

	wattron(window, COLOR_PAIR(DISPLAY_COLOR));

	int numrows = displaying_lines.size();
	for (int row = 0; row < end.line - start.line; row++)
	{
		int rowidx = row + rowoffset;
		if (rowidx + 1>= numrows)
		{
			break;
		}

		int numcols = displaying_lines.at(rowidx).size();
		for (int col = 0; col < end.column - start.column; col++)
		{
			int colidx = col + coloffset;
			if (colidx >= numcols)
			{
				break;
			}

			mvwaddch(get_curses_window(), start.line + row, start.column + col, displaying_lines.at(rowidx).at(colidx));
		}
	}

	std::stringstream ss;
	ss << "[row: " << std::setw(5) << rowoffset << "][col: " << std::setw(5) << coloffset << "]";

	wattron(window, COLOR_PAIR(META_COLOR));
	mvwaddstr(get_curses_window(), end.line, start.column, ss.str().c_str());
}

void Tab::write_tab(Writable& w)
{
	std::lock_guard<std::recursive_mutex> locb{buffer_mutex};
	buffer << w;
	delim();
}

const std::string& Tab::get_name()
{
	return name;

}

void Tab::left()
{
	if (coloffset > 0)
	{
		coloffset--;
	}
}

void Tab::right()
{
	if (coloffset <= maxcol)
	{
		coloffset++;
	}
}

bool Tab::up()
{
	if (rowoffset > 0)
	{
		rowoffset--;
		return true;
	}
	else
	{
		return false;
	}
}

void Tab::down()
{
	if (rowoffset <= (int) displaying_lines.size())
	{
		rowoffset++;
	}
}
