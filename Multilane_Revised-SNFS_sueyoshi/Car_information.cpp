#include "Car_information.h"

void Car_information::Fromcurrent_toprevious() {
	position.previous = position.current;
	velocity.previous = velocity.current;
	distance.previous = distance.current;
}

void Car_information::initialize(int NumberofCars) {
	position.current = position.previous = std::vector<int>(NumberofCars, 0);
	velocity.current = velocity.previous = std::vector<int>(NumberofCars, 0);
	distance.current = distance.previous = std::vector<int>(NumberofCars, 0);
	measure = std::vector<Measure>(NumberofCars);
	canditate_velocity = std::vector<int>(NumberofCars, 0);
	S = std::vector<int>(NumberofCars, 0);
}

