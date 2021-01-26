#include "Initialize.h"

void Initialize::initialize(double lanelength, int NumberofCars) {
	car.initialize(NumberofCars);
	map.initialize(lanelength);
	_initialplacement(lanelength,NumberofCars);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
}

//In this function, cell is assigned for each vehicle randomly.
//and record the position and ID relationships in "map" class
void Initialize::_initialplacement(double lanelength,int NumberofCars) {
	int iter = 0;
	for (int i = constants.N - 1; i >= 0; --i) {
		car.position.current[i] = (double)8 * iter;
		car.position.current[i] += random.random(2.0);
		if (car.position.current[i] >= constants.lanelength) car.position.current[i] -= constants.lanelength;
		iter++;
	}
	for (int i = 0; i < constants.N; ++i) car.velocity.current[i] = random.random(1.0, 3.0);
}

