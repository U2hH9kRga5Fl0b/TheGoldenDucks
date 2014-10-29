
#ifndef LOCATION_H_
#define LOCATION_H_


class Location
{
public:
	int line;
	int column;

	Location(int line, int column);
	~Location();

	bool operator<(const Location& other);
};


#endif
