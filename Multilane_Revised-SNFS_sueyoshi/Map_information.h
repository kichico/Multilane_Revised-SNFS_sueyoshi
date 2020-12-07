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
	struct update_information {
		std::vector<bool> existence;
		std::vector<int> ID;
	};
public:
	int lanevelocity;
	map_information recorded;
	update_information updated;
	void initialize(int lanelength);
	void Fromcurrent_toprevious();
};

#endif // !MAPINFORMATION_H
