

#ifndef ATTRIBUTE_H_
#define ATTRIBUTE_H_

#include "location.hpp"

#include <curses.h>

typedef enum
{
	SET_COLOR,
} AttributeType;


class Attribute : public Location
{
private:
	bool on;
	AttributeType type;

public:
	Attribute(int line, int column, bool on, AttributeType type);
	~Attribute();
	
	void apply(WINDOW* window);
};


#endif
