#include "Car_information.h"

void Car_information::Fromcurrent_toprevious() {
	position.previous = position.current;
	velocity.previous = velocity.current;
	distance.previous = distance.current;
	around.preceeding.previous = around.preceeding.current;
	around.following.previous = around.following.current;
}

void Car_information::initialize(int NumberofCars) {
	position.current = position.previous = std::vector<int>(NumberofCars, 0);
	velocity.current = velocity.previous = std::vector<int>(NumberofCars, 0);
	distance.current = distance.previous = std::vector<int>(NumberofCars, 0);
	around.following.current = around.following.previous = around.preceeding.current = around.preceeding.previous = std::vector<int>(NumberofCars, 0);
	measure = std::vector<Measure>(NumberofCars);
	canditate_velocity = std::vector<int>(NumberofCars, 0);
	S = std::vector<int>(NumberofCars, 0);
}

