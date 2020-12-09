#include "Update_Position.h"

void Update_Position::update_position() {
	Update_again = std::vector<bool>(constants.N, true);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
	map.updated.existence = map.recorded.existence.current;
	map.updated.ID = map.recorded.ID.current;
	map.lanevelocity = 0;
	bool keepupdating = true;
	int lanenumber = 0;
	for (int i = 0; i < constants.NumofLane; i++) while (keepupdating) keepupdating = _update_fromLeadingcar(lanenumber, Measurewillbedone);
	map.recorded.existence.current = map.updated.existence;
	map.recorded.ID.current = map.updated.ID;
	car.canditate_velocity = std::vector<int>(constants.N, 0);
	//car.velocity.current = car.canditate_velocity;
	if (Measurewillbedone) {
		for (int lanenumber = 0; lanenumber < constants.NumofLane; lanenumber++) {
			int i = 1;
			while (true) {
				if (map.recorded.existence.previous[lanenumber][100 - i]) {
					int possiblypassedcarID = map.recorded.ID.current[lanenumber][100 - i];
					if (car.position.current[possiblypassedcarID] >= 100) flux++; std::cout << flux << std::endl;
				}
				i++;
				if (i > 5) break;
			}
		}
	}
}

bool Update_Position::_update_fromLeadingcar(int lanenumber, bool flg_measure) {
	int ID = car.leadingcar[lanenumber].ID;
	int nextposition = 0;
	map.lanevelocity = 0;
	Car_information::Leadingcar tempLeadingcar;
	tempLeadingcar.existence = false;
	//map.updated.existence[car.position.current[ID]] = true;
	int previouslanevelocity = map.lanevelocity;
	while (true) {
		if (Update_again[ID]) _move_forward_car(ID);
		else nextposition = car.position.current[ID];
		if (ID == car.leadingcar[lanenumber].ID) car.leadingcar[lanenumber].existence = false;
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
		if (car.around.following.current[ID] == car.leadingcar[lanenumber].ID) {
			int followingcarID = car.around.following.current[ID];
			int followingcarposition = car.position.current[followingcarID];
			int distance = car.position.current[ID] - followingcarposition;
			if (distance < 0) distance += constants.lanelength;
			if (distance > tempLeadingcar.distance) {
				tempLeadingcar.ID = followingcarID;
				tempLeadingcar.distance = distance;
			}
			//TODO modify when introducing multilane system
			if (previouslanevelocity == map.lanevelocity) return false;
			else {
				ID = car.leadingcar[lanenumber].ID;
				previouslanevelocity = map.lanevelocity;
				map.lanevelocity = 0;
			}
		}
		else ID = car.around.following.current[ID];
	}
	car.leadingcar[lanenumber] = tempLeadingcar;
}

void Update_Position::_move_forward_car(int ID) {
	int nextposition = car.position.current[ID];
	int distanceavailable = car.canditate_velocity[ID];
	int lanenumber = car.lanenumber[ID];
	for (int i = 1; i <= distanceavailable; i++) {
		++nextposition;
		if (nextposition >= constants.lanelength) nextposition -= constants.lanelength;
		if (map.updated.existence[lanenumber][nextposition]) {
			Update_again[ID] = true;
			--nextposition;
			if (nextposition < 0) nextposition += constants.lanelength;
			car.canditate_velocity[ID] = i - 1;
			break;
		}
	}
	if (nextposition == car.position.current[ID] + distanceavailable) Update_again[ID] = false;
	map.updated.existence[lanenumber][car.position.current[ID]] = false;
	map.updated.existence[lanenumber][nextposition] = true;
	map.updated.ID[lanenumber][car.position.current[ID]] = 0;
	map.updated.ID[lanenumber][nextposition] = ID;
	car.position.current[ID] = nextposition;
	car.velocity.current[ID] = nextposition - car.position.previous[ID];
	if (car.velocity.current[ID] < 0) car.velocity.current[ID] += constants.lanelength;
	int preceedingcarID = car.around.preceeding.current[ID];
	car.distance.current[ID] = car.position.current[preceedingcarID] - car.position.current[ID];
	if (car.distance.current[ID] < 0) car.distance.current[ID] += constants.lanelength;
}