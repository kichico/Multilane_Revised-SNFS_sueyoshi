#include "Map_information.h"

void Map_information::initialize(int lanelength) {
	recorded.existence.current = recorded.existence.previous = updated.existence.current = updated.existence.previous = std::vector<bool>(lanelength, false);
	recorded.ID.current = recorded.ID.previous = updated.ID.current = updated.ID.previous = std::vector<int>(lanelength, 0);
}