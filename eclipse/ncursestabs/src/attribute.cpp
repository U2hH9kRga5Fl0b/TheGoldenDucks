#include "attribute.hpp"
#include "location.hpp"

#include <iostream>

Attribute::Attribute(int line, int column, bool on_, AttributeType type_) :
		Location{line, column},
		on(on_),
		type(type_) {}

Attribute::~Attribute() {}

void Attribute::apply(WINDOW* window)
{
	switch(type)
	{
		case SET_COLOR:
			std::cerr << "colors not implemented!" << std::endl;
			break;
		default:
			std::cerr << "unrecognized attribute type: " << type << std::endl;
	}
}
