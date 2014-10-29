

#ifndef TAB_H_
#define TAB_H_

#include "attribute.hpp"

#include <iostream>
#include <mutex>
#include <vector>
#include <set>
#include <sstream>

class Writable;

class Tab
{
private:
	std::string name;

	std::vector<std::string>	displaying_lines;
	std::set<Attribute>		displaying_atts;
	int				maxcol;

	std::vector<std::string>	nextlines;
	std::set<Attribute>		next_atts;

	std::recursive_mutex            buffer_mutex;
	std::ostringstream              buffer;

	int				rowoffset, coloffset;
public:
	Tab(const std::string name);
	~Tab();

	Tab& operator=(const Tab& other) = delete;
	Tab(const Tab& other) = delete;

	const std::string& get_name();

	std::recursive_mutex& get_mutex();
	std::ostream& input();
	void setColors(int foreground, int background);
	void delim();

	bool flush();
	
	void display(WINDOW* window, Location&& start, Location&& end);
	void write_tab(Writable& w);

	void left();
	void right();
	bool up();
	void down();
};


#endif
