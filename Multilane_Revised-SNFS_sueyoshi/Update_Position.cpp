#include "Update_Position.h"

void Update_Position::update_position() {
	Update_again = std::vector<bool>(constants.N, true);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
	map.updated.existence = std::vector<bool>(constants.lanelength, false);
	map.updated.ID = std::vector<int>(constants.lanelength, 0);
	map.lanevelocity = 0;
	bool keepupdating = true;
	int lanenumber = 0;
	while (keepupdating) keepupdating = _update_fromLeadingcar(lanenumber,Measurewillbedone);
	map.recorded.existence.current = map.updated.existence;
	map.recorded.ID.current = map.updated.ID;
	if(Measurewillbedone) for (int i = 0; i < constants.N; i++) if (car.position.previous[i] < 100 && car.position.current[i] >= 100) flux++;
}

bool Update_Position::_update_fromLeadingcar(int lanenumber, bool flg_measure) {
	int ID = car.leadingcar.ID;
	int nextposition = 0;
	map.lanevelocity = 0;
	Car_information::Leadingcar tempLeadingcar;
	tempLeadingcar.existence = false;
	//map.updated.existence[car.position.current[ID]] = true;
	int previouslanevelocity = map.lanevelocity;
	while (true) {
		if (Update_again[ID]) _move_forward_car(ID);
		else nextposition = car.position.current[ID];
		if (ID == car.leadingcar.ID) car.leadingcar.existence = false;
		map.lanevelocity += car.canditate_velocity[ID];
		int headway = car.distance.current[ID];
		if (!tempLeadingcar.existence) {
			tempLeadingcar.ID = ID;
			tempLeadingcar.existence = true;
			tempLeadingcar.distance = headway;
		}
		else {
			if (headway > tempLeadingcar.distance) {
				tempLeadingcar.ID = ID;
				tempLeadingcar.distance = headway;
			}
		}
		if (car.around.following.current[ID] == car.leadingcar.ID) {
			int followingcarID = car.around.following.current[ID];
			int followingcarposition = car.position.current[ID];
			int distance = car.position.current[ID] - followingcarposition;
			if (distance < 0) distance += constants.lanelength;
			if (distance > tempLeadingcar.distance) {
				tempLeadingcar.ID = followingcarID;
				tempLeadingcar.distance = distance;
			}
			//TODO modify when introducing multilane sysy\tem
			if (previouslanevelocity == map.lanevelocity) return false;
			else {
				ID = car.leadingcar.ID;
				previouslanevelocity = map.lanevelocity;
				map.lanevelocity = 0;
			}
		}
		else ID = car.around.following.current[ID];
	}
}

void Update_Position::_move_forward_car(int ID) {
	int nextposition = car.position.current[ID];
	int distanceavailable = car.canditate_velocity[ID];
	for (int i = 1; i <= distanceavailable; i++) {
		nextposition += i;
		if (nextposition >= constants.lanelength) nextposition -= constants.lanelength;
		if (map.updated.existence[nextposition]) {
			Update_again[ID] = true;
			--nextposition;
			car.canditate_velocity[ID] -= i - 1;
			break;
		}
	}
	if (nextposition == car.position.current[ID] + distanceavailable) Update_again[ID] = false;
	map.updated.existence[car.position.current[ID]] = false;
	map.updated.existence[nextposition] = true;
	map.updated.ID[car.position.current[ID]] = false;
	map.updated.ID[nextposition] = true;
	car.position.current[ID] = nextposition;
	int preceedingcarID = car.around.preceeding.current[ID];
	car.distance.current[ID] = car.position.current[preceedingcarID] - car.position.current[ID];
	if (car.distance.current[ID] < 0) car.distance.current[ID] += constants.lanelength;
}