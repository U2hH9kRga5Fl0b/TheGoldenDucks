
#ifndef WRITABLE_H_
#define WRITABLE_H_

#include <iostream>

class Writable
{
public:
	Writable();
	virtual ~Writable();
	
	friend std::ostream& operator<<(std::ostream& out, const Writable& w);
};


#endif
