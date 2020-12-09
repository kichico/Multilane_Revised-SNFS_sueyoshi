#include "Map_information.h"

void Map_information::initialize(int lanelength, int NumberofLanes) {
	recorded.existence.current = recorded.existence.previous = updated.existence = std::vector<std::vector<bool> >(NumberofLanes, std::vector<bool>(lanelength, false));
	recorded.ID.current = recorded.ID.previous = updated.ID = std::vector<std::vector<int> >(NumberofLanes, std::vector<int>(lanelength, 0));
	NumberofCars_at_thislane = std::vector<int>(NumberofLanes, 0);
}

void Map_information::Fromcurrent_toprevious() {
	recorded.existence.previous = recorded.existence.current;
	recorded.ID.previous = recorded.ID.current;
}