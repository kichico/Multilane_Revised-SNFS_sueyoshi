#include "Map_information.h"

void Map_information::initialize(double lanelength) {
	recorded.existence.current = recorded.existence.previous = updated.existence = std::vector<bool>(lanelength, false);
	recorded.ID.current = recorded.ID.previous = updated.ID = std::vector<int>(lanelength, 0);
}

void Map_information::Fromcurrent_toprevious() {
	recorded.existence.previous = recorded.existence.current;
	recorded.ID.previous = recorded.ID.current;
}