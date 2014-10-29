
#include "util.hpp"

#include <unistd.h>
#include <thread>

void something_in_background()
{
	TabbedWindow& window = get_tabbed_window();

	for (int i = 0; !stop_now; i++)
	{
		int numcols = rand() % 50;
		int numrows = rand() % 50;
		for (int i = 0; i < numrows; i++)
		{
			std::lock_guard < std::recursive_mutex > locb { window.get_tab("first").get_mutex() };
			for (int j = 0; j < numcols; j++)
			{
				window.get_tab("first").input() << rand() << ' ';
			}

			window.get_tab("first").input() << '\n';
		}

		{
			std::lock_guard<std::recursive_mutex> locb{window.get_tab("first").get_mutex()};
			window.get_tab("first").delim();
		}

		window.display();

		std::stringstream ss;
		ss << "wrote strings " << i << " with " << numrows << ", " << numcols << " rows and columns.";
		window.status(ss.str());

		sleep(rand() % 10);
	}
}


int main(int argc, char **argv)
{
	init("foobar");

	TabbedWindow& window = get_tabbed_window();

	window.create_tab("first");
	window.create_tab("another");


	{
		std::lock_guard<std::recursive_mutex> locb{window.get_tab("first").get_mutex()};

		window.get_tab("first").input() << "here is some text.";
		window.get_tab("first").delim();
	}

	window.display();

	std::thread t{something_in_background};

	event_loop();
}
