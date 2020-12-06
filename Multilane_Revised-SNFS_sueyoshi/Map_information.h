#ifndef MAPINFORMATION_H
#define MAPINFORMATION_H
#include <vector>
class Map_information {
private:
	struct CurrentandPreviousbool {
		std::vector<bool> current;
		std::vector<bool> previous;
	};
	struct CurrentandPreviousint {
		std::vector<int> current;
		std::vector<int> previous;
	};
	struct map_information {
		CurrentandPreviousbool existence;
		CurrentandPreviousint ID;
	};
public:
	map_information recorded, updated;
	void initialize(int lanelength);
};

#endif // !MAPINFORMATION_H
