#include "location.hpp"

Location::Location(int line_, int column_) :
	line{line_},
	column{column_} {}

Location::~Location() {}

bool Location::operator <(const Location& other)
{
	if (line == other.line)
	{
		return column < other.column;
	}
	return line < other.line;
}
