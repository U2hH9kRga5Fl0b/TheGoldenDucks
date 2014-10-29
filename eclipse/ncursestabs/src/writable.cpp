
#include "writable.hpp"

std::ostream& operator<<(std::ostream& out, const Writable& w)
{
	return out << "This is a default implementation." << std::endl;
}
