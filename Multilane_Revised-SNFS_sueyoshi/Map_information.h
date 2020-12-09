#ifndef MAPINFORMATION_H
#define MAPINFORMATION_H
#include <vector>
class Map_information {
private:
	struct CurrentandPreviousbool {
		std::vector<std::vector<bool> > current;
		std::vector<std::vector<bool> > previous;
	};
	struct CurrentandPreviousint {
		std::vector<std::vector<int> > current;
		std::vector<std::vector<int> > previous;
	};
	struct map_information {
		CurrentandPreviousbool existence;
		CurrentandPreviousint ID;
	};
	struct update_information {
		std::vector<std::vector<bool> > existence;
		std::vector<std::vector<int> > ID;
	};
public:
	int lanevelocity;
	map_information recorded;
	update_information updated;
	std::vector<int> NumberofCars_at_thislane;
	void initialize(int lanelength,int NumberofLanes);
	void Fromcurrent_toprevious();
};

#endif // !MAPINFORMATION_H
