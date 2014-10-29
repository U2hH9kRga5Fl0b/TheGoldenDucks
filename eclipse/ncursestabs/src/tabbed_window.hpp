
#ifndef TABBED_WINDOW_H_
#define TABBED_WINDOW_H_

class Tab;

#include <vector>
#include <string>

class TabbedWindow
{
private:
	std::string name;
	std::vector<Tab*> tabs;
	int focus;
	bool focus_on_panel;
	std::string statusstr;
public:
	TabbedWindow(const std::string& name);
	~TabbedWindow();
	
	int  create_tab(const std::string& name);
	bool destroy_tab(const std::string& name);
	
	Tab& get_tab(int index);
	Tab& get_tab(const std::string& name);

	void display();
	bool capture();
	int get_num_tabs();

	void status(const std::string& status_string);

};


#endif
