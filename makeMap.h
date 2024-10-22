#include <fstream>
#include <ncurses.h>
#include <string>
#include <vector>
#include <ctime>
class makeMap{
	public:
		int createMap(std::string pathToMap);
		std::vector<int> initializeConditions();
};

