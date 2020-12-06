#include "Initialize.h"

void Initialize::initialize(int lanelength, int NumberofCars) {
	car.initialize(NumberofCars);
	map.initialize(lanelength);
	_initialplacement(lanelength,NumberofCars);
	_defineVmax(flg_distributedVmax,NumberofCars);
}

void Initialize::_initialplacement(int lanelength,int NumberofCars) {
	std::vector<int> List_notplacedcell(lanelength);
	for (int ID = 0; ID < NumberofCars; ID++) {
		int remainListsize = List_notplacedcell.size();
		int picker = random.random(remainListsize - 1);
		int pikedupcell = List_notplacedcell[picker];
		std::iter_swap(List_notplacedcell.begin() + picker, List_notplacedcell.end() - 1);
		List_notplacedcell.pop_back();
		car.position.current[ID] = car.position.previous[ID] = pikedupcell;
		map.recorded.existence.current[pikedupcell] = map.recorded.existence.previous[pikedupcell] = true;
		map.recorded.ID.current[pikedupcell] = map.recorded.ID.previous[pikedupcell] = ID;
	}
	int cnt_identified = 1;
	int preceedingcarposition;
	int preceedingcarID;
	int focalcarID;
	int followingcarposition;
	int maximumdistance = 0;

	//TODO When it is introduced Multilane system, these conditions shoud be modified.
	
	for (int i = 0; i < lanelength; i++) {
		if (map.recorded.existence.current[i]) {
			if (cnt_identified == 1) {
				preceedingcarID = map.recorded.ID.current[i];
				preceedingcarposition = car.position.current[preceedingcarID];
				++cnt_identified;
			}
			else if (cnt_identified != NumberofCars) {
				focalcarID = map.recorded.ID.current[i];
				car.around.preceeding.current[focalcarID] = preceedingcarID;
				car.around.following.current[preceedingcarID] = focalcarID;
				car.distance.current[focalcarID] = preceedingcarposition - car.position.current[focalcarID];
				if (car.distance.current[focalcarID] < 0) car.distance.current[focalcarID] += lanelength;
				if (car.distance.current[focalcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[focalcarID];
					car.leadingcar.ID = focalcarID;
					car.leadingcar.distance = maximumdistance;
				}
				preceedingcarID = focalcarID;
				preceedingcarposition = car.position.current[preceedingcarID];
				++cnt_identified;
			}
			if (cnt_identified == NumberofCars) {
				focalcarID = map.recorded.ID.current[i];
				car.around.preceeding.current[focalcarID] = preceedingcarID;
				car.around.following.current[preceedingcarID] = car.around.preceeding.current[0] = focalcarID;
				car.distance.current[focalcarID] = preceedingcarposition - car.position.current[focalcarID];
				if (car.distance.current[focalcarID] < 0) car.distance.current[focalcarID] += lanelength;
				car.distance.current[0] = car.position.current[focalcarID] - car.position.current[0];
				if (car.distance.current[0] < 0) car.distance.current[0] += lanelength;
				if (car.distance.current[focalcarID] >= maximumdistance) {
					maximumdistance = car.distance.current[focalcarID];
					car.leadingcar.ID = focalcarID;
					car.leadingcar.distance = maximumdistance;
				}
				if (car.distance.current[0] >= maximumdistance) {
					maximumdistance = car.distance.current[0];
					car.leadingcar.ID = 0;
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