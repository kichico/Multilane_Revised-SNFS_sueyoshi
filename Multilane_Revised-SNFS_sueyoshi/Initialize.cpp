#include "Initialize.h"

void Initialize::initialize(int lanelength, int NumberofCars, int NumberofLanes) {
	car.initialize(NumberofCars,NumberofLanes);
	map.initialize(lanelength, NumberofLanes);
	_initialplacement(lanelength,NumberofCars,NumberofLanes);
	_defineVmax(flg_distributedVmax,NumberofCars);
	_initialassignment_strategy();
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
}

void Initialize::_initialplacement(int lanelength,int NumberofCars, int NumberofLanes) {
	struct InitialPlacement {
		int lanenumber;
		int cellnumber;
	};
	std::vector<InitialPlacement> List_notplacedcell(0);
	InitialPlacement canditate_placement;
	for (int lanenumber = 0; lanenumber < NumberofLanes; ++lanenumber) {
		for (int i = 0; i < lanelength; i++) {
			canditate_placement.lanenumber = lanenumber;
			canditate_placement.cellnumber = i;
			List_notplacedcell.emplace_back(canditate_placement);
		}
	}
	car.lanenumber = std::vector<int>(constants.N, 0);
	for (int ID = 0; ID < NumberofCars; ID++) {
		int remainListsize = List_notplacedcell.size();
		int picker = random.random(remainListsize - 1);
		InitialPlacement pickedupcell = List_notplacedcell[picker];
		std::iter_swap(List_notplacedcell.begin() + picker, List_notplacedcell.end() - 1);
		List_notplacedcell.pop_back();
		car.position.current[ID] = car.position.previous[ID] = pickedupcell.cellnumber;
		car.lanenumber[ID] = pickedupcell.lanenumber;
		map.recorded.existence.current[pickedupcell.lanenumber][pickedupcell.cellnumber] = map.recorded.existence.previous[pickedupcell.lanenumber][pickedupcell.cellnumber] = true;
		map.recorded.ID.current[pickedupcell.lanenumber][pickedupcell.cellnumber] = map.recorded.ID.previous[pickedupcell.lanenumber][pickedupcell.cellnumber] = ID;
		map.NumberofCars_at_thislane[pickedupcell.lanenumber]++;
	}
	int followingcarposition = 0;
	int followingcarID = 0;
	int focalcarID = 0;
	int maximumdistance = 0;
	int firstidentifiedcarID = 0;
	//TODO When it is introduced Multilane system, these conditions shoud be modified.
	for (int lanenumber = 0; lanenumber < NumberofLanes; lanenumber++) {
		int cnt_identified = 1;
		for (int cellnumber = 0; cellnumber < lanelength; cellnumber++) {
			if (map.recorded.existence.current[lanenumber][cellnumber]) {
				if (cnt_identified == 1) {
					followingcarID = map.recorded.ID.current[lanenumber][cellnumber];
					firstidentifiedcarID = followingcarID;
					followingcarposition = car.position.current[followingcarID];
					++cnt_identified;
				}
				else if (cnt_identified != map.NumberofCars_at_thislane[lanenumber]) {
					focalcarID = map.recorded.ID.current[lanenumber][cellnumber];
					car.around.preceeding.current[followingcarID] = focalcarID;
					car.around.following.current[focalcarID] = followingcarID;
					car.distance.current[followingcarID] = car.position.current[focalcarID] - followingcarposition;
					if (car.distance.current[followingcarID] < 0) car.distance.current[followingcarID] += lanelength;
					if (car.distance.current[followingcarID] >= maximumdistance) {
						maximumdistance = car.distance.current[followingcarID];
						car.leadingcar[lanenumber].existence = true;
						car.leadingcar[lanenumber].ID = followingcarID;
						car.leadingcar[lanenumber].distance = maximumdistance;
					}
					followingcarID = focalcarID;
					followingcarposition = car.position.current[followingcarID];
					++cnt_identified;
				}
				else if (cnt_identified == map.NumberofCars_at_thislane[lanenumber]) {
					focalcarID = map.recorded.ID.current[lanenumber][cellnumber];
					//followingcarID = car.around.following.current[focalcarID];
					car.around.following.current[focalcarID] = followingcarID;
					car.around.preceeding.current[followingcarID] = car.around.following.current[firstidentifiedcarID] = focalcarID;
					car.around.preceeding.current[focalcarID] = firstidentifiedcarID;
					car.distance.current[followingcarID] = car.position.current[focalcarID] - followingcarposition;
					if (car.distance.current[followingcarID] < 0) car.distance.current[followingcarID] += lanelength;
					car.distance.current[focalcarID] = car.position.current[firstidentifiedcarID] - car.position.current[focalcarID];
					if (car.distance.current[focalcarID] < 0) car.distance.current[focalcarID] += lanelength;
					car.distance.current[firstidentifiedcarID] = car.position.current[firstidentifiedcarID] - car.position.current[focalcarID];
					if (car.distance.current[firstidentifiedcarID] < 0) car.distance.current[firstidentifiedcarID] += lanelength;
					if (car.distance.current[followingcarID] >= maximumdistance) {
						maximumdistance = car.distance.current[followingcarID];
						car.leadingcar[lanenumber].existence = true;
						car.leadingcar[lanenumber].ID = followingcarID;
						car.leadingcar[lanenumber].distance = maximumdistance;
					}
					if (car.distance.current[focalcarID] >= maximumdistance) {
						maximumdistance = car.distance.current[focalcarID];
						car.leadingcar[lanenumber].ID = focalcarID;
						car.leadingcar[lanenumber].distance = maximumdistance;
					}
					if (car.distance.current[firstidentifiedcarID] >= maximumdistance) {
						maximumdistance = car.distance.current[firstidentifiedcarID];
						car.leadingcar[lanenumber].ID = firstidentifiedcarID;
						car.leadingcar[lanenumber].distance = maximumdistance;
					}
					break;
				}
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

void Initialize::_initialassignment_strategy() {
	double ratio_C = constants.C;
	double ratio_D = constants.D;
	int NumofC = ceil(ratio_C * constants.N);
	int NumofD = floor(ratio_D * constants.N);
	std::vector<int> Listofcars(constants.N, 0);
	for (int i = 0; i < constants.N; i++) Listofcars[i] = car.strategy.C;
	for (int i = 0; i < NumofD; i++) {
		int NotassignedstrategyD = Listofcars.size();
		int picker = random.random(NotassignedstrategyD - 1);
		int pikedupcar = Listofcars[picker];
		std::iter_swap(Listofcars.begin() + pikedupcar, Listofcars.end() - 1);
		Listofcars.pop_back();
	}
}