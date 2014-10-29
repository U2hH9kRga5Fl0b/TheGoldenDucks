
#include <string>
#include "tabbed_window.hpp"
#include "tab.hpp"
#include "eventloop.hpp"

extern bool stop_now;

// Call this before anything else
void init(const std::string& name);

// Call this to write something to the screen
TabbedWindow& get_tabbed_window();

// Call this when you are done
void close();

