#include "Update_Position.h"

//This function is calling _update_fromLeaidngcar by lane.
//If you increased the number of lanes, that function will be more and more called by this function.
//Also this function should be rewritten when introducing multilane system, let's consider what the matter.

void Update_Position::update_position() {
	Update_again = std::vector<bool>(constants.N, true);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
	map.updated.existence = map.recorded.existence.current;
	map.updated.ID = map.recorded.ID.current;
	map.lanevelocity = 0;
	bool keepupdating = true;
	int lanenumber = 0;
	while (keepupdating) keepupdating = _update_fromLeadingcar(lanenumber, Measurewillbedone);
	map.recorded.existence.current = map.updated.existence;
	map.recorded.ID.current = map.updated.ID;
	car.canditate_velocity = std::vector<int>(constants.N, 0);
	if (Measurewillbedone) {
		for (int i = 0; i < constants.N; i++) if (car.position.previous[i] < 100 && car.position.current[i] >= 100) {
			flux++;
		}
	}
}

//This function decide every car is updated own position until they want or not.
//This function is called once or twice at one lane.
bool Update_Position::_update_fromLeadingcar(int lanenumber, bool flg_measure) {
	int ID = car.leadingcar.ID;
	int nextposition = 0;
	map.lanevelocity = 0;
	Car_information::Leadingcar tempLeadingcar;
	tempLeadingcar.existence = false;
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
			int followingcarposition = car.position.current[followingcarID];
			int distance = car.position.current[ID] - followingcarposition;
			if (distance < 0) distance += constants.lanelength;
			if (distance > tempLeadingcar.distance) {
				tempLeadingcar.ID = followingcarID;
				tempLeadingcar.distance = distance;
			}
			//TODO modify when introducing multilane sysytem
			if (previouslanevelocity == map.lanevelocity) break;
			else {
				ID = car.leadingcar.ID;
				previouslanevelocity = map.lanevelocity;
				map.lanevelocity = 0;
			}
		}
		else ID = car.around.following.current[ID];
	}
	car.leadingcar = tempLeadingcar;
	return false;
}

void Update_Position::_move_forward_car(int ID) {
	int nextposition = car.position.current[ID];
	int distanceavailable = car.canditate_velocity[ID];
	for (int i = 1; i <= distanceavailable; i++) {
		++nextposition;
		if (nextposition >= constants.lanelength) nextposition -= constants.lanelength;
		if (map.updated.existence[nextposition]) {
			Update_again[ID] = true;
			--nextposition;
			if (nextposition < 0) nextposition += constants.lanelength;
			car.canditate_velocity[ID] -= i - 1;
			break;
		}
	}
	if (nextposition == car.position.current[ID] + distanceavailable) Update_again[ID] = false;
	map.updated.existence[car.position.current[ID]] = false;
	map.updated.existence[nextposition] = true;
	map.updated.ID[car.position.current[ID]] = 0;
	map.updated.ID[nextposition] = ID;
	car.position.current[ID] = nextposition;
	car.velocity.current[ID] = nextposition - car.position.previous[ID];
	if (car.velocity.current[ID] < 0) car.velocity.current[ID] += constants.lanelength;
	int preceedingcarID = car.around.preceding.current[ID];
	car.distance.current[ID] = car.position.current[preceedingcarID] - car.position.current[ID];
	if (car.distance.current[ID] < 0) car.distance.current[ID] += constants.lanelength;
}