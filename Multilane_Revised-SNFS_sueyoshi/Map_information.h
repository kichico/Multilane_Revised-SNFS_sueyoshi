#ifndef MAP_INFORMATION.H
#define MAP_INFORMATION.H
#include <vector>
class Map_information {
private:
	struct map_information {
		std::vector<bool> existence;
		std::vector<int> ID;
	};
public:
	map_information map, update;
	void initialize(int lanelength);
};

#endif // !MAP_INFORMATION.H
