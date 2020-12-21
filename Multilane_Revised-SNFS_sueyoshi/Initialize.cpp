#include "Initialize.h"

void Initialize::initialize(int lanelength, int NumberofCars) {
	car.initialize(NumberofCars);
	map.initialize(lanelength);
	_initialplacement(lanelength,NumberofCars);
	_defineVmax(flg_distributedVmax,NumberofCars);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
}

//In this function, cell is assigned for each vehicle randomly.
//and record the position and ID relationships in "map" class
void Initialize::_initialplacement(int lanelength,int NumberofCars) {
	std::vector<int> List_notplacedcell(lanelength);
	for (int i = 0; i < lanelength; i++) List_notplacedcell[i] = i;
	for (int ID = 0; ID < NumberofCars; ID++) {
		int remainListsize = List_notplacedcell.size();
		int picker = random.random(remainListsize - 1);
		int pikedupcell = List_notplacedcell[picker];
		std::iter_swap(List_notplacedcell.begin() + picker, List_notplacedcell.end() - 1);
		List_notplacedcell.pop_back();
		//the calculation speed of "iter_swap + pop_back" method is faster than "erase" method
		car.position.current[ID] = car.position.previous[ID] = pikedupcell;
		map.recorded.existence.current[pikedupcell] = map.recorded.existence.previous[pikedupcell] = true;
		map.recorded.ID.current[pikedupcell] = map.recorded.ID.previous[pikedupcell] = ID;
	}
	int cnt_identified = 1;
	int followingcarposition = 0;
	int followingcarID = 0;
	int focalcarID = 0;
	int maximumdistance = 0;
	int firstidentifiedcarID = 0;
	//In honestly say, this section should be rewritten because of some reasons.
	for (int i = 0; i < lanelength; i++) {
		if (map.recorded.existence.current[i]) {
			if (cnt_identified == 1) {
				followingcarID = map.recorded.ID.current[i];
				firstidentifiedcarID = followingcarID;
				followingcarposition = car.position.current[followingcarID];
				if (NumberofCars == 1) break;
				++cnt_identified;
			}
			else if (cnt_identified != NumberofCars) {
				focalcarID = map.recorded.ID.current[i];
				car.around.preceeding.current[followingcarID] = focalcarID;
				car.around.following.current[focalcarID] = followingcarID;
				car.distance.current[followingcarID] = car.position.current[focalcarID] - followingcarposition -1;
				if (car.distance.current[followingcarID] < 0) car.distance.current[followingcarID] += lanelength;
				if (car.distance.current[followingcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[followingcarID];
					car.leadingcar.existence = true;
					car.leadingcar.ID = followingcarID;
					car.leadingcar.distance = maximumdistance;
				}
				followingcarID = focalcarID;
				followingcarposition = car.position.current[followingcarID];
				++cnt_identified;
			}
			else if (cnt_identified == NumberofCars) {
				focalcarID = map.recorded.ID.current[i];
				car.around.following.current[focalcarID] = followingcarID;
				car.around.preceeding.current[followingcarID] = car.around.following.current[firstidentifiedcarID] = focalcarID;
				car.around.preceeding.current[focalcarID] = firstidentifiedcarID;
				car.distance.current[followingcarID] = car.position.current[focalcarID] - followingcarposition - 1;
				if (car.distance.current[followingcarID] < 0) car.distance.current[followingcarID] += lanelength;
				car.distance.current[focalcarID] = car.position.current[firstidentifiedcarID] - car.position.current[focalcarID] - 1;
				if (car.distance.current[focalcarID] < 0) car.distance.current[focalcarID] += lanelength;
				car.distance.current[firstidentifiedcarID] = car.position.current[firstidentifiedcarID] - car.position.current[focalcarID] - 1;
				if (car.distance.current[firstidentifiedcarID] < 0) car.distance.current[firstidentifiedcarID] += lanelength;
				if (car.distance.current[followingcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[followingcarID];
					car.leadingcar.existence = true;
					car.leadingcar.ID = followingcarID;
					car.leadingcar.distance = maximumdistance;
				}
				if (car.distance.current[focalcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[focalcarID];
					car.leadingcar.ID = focalcarID;
					car.leadingcar.distance = maximumdistance;
				}
				if (car.distance.current[firstidentifiedcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[firstidentifiedcarID];
					car.leadingcar.ID = firstidentifiedcarID;
					car.leadingcar.distance = maximumdistance;
				}
				break;
			}
		}
	}
}

void Initialize::_defineVmax(bool flg_distributedVmax, int NumberofCars) {
	constants.Vmax = std::vector<int>(NumberofCars, 0);
	if (flg_distributedVmax == false) for (int i = 0; i < NumberofCars;i++) constants.Vmax[i] = 5;
	else {
		//TODO When it is introduced variable distributed Vmax, this section should be change.
		for (int i = 0; i < NumberofCars;i++) {
			if (i % 3 == 0) constants.Vmax[i] = 4;
			if (i % 3 == 1) constants.Vmax[i] = 5;
			if (i % 3 == 2) constants.Vmax[i] = 6;
		}
		std::vector<int> List_notassignedVmax(NumberofCars);
		for (int ID = 0; ID < NumberofCars; ID++) {
			int remainListsize = List_notassignedVmax.size();
			int picker = random.random(remainListsize - 1);
			int pikedupVmax =List_notassignedVmax[picker];
			std::iter_swap(List_notassignedVmax.begin() + picker,List_notassignedVmax.end() - 1);
			List_notassignedVmax.pop_back();
			car.velocity.current[ID] = pikedupVmax;
		}
	}
}