#include "Decide_Velocity.h"

void Decide_Velocity::decide_velocity() {
	car.canditate_velocity = std::vector<int>(constants.N, 0);
//#pragma omp parallel for num_threads(4)
	for (int ID = 0; ID < constants.N; ID++) {
		V = car.velocity.current[ID]; 
		_make_V1(V, ID);
		_make_V2(ID);
		_make_V3(ID);
		_make_V4(ID);
		car.canditate_velocity[ID] = rule.V4; //Substitute decided velocity to temporary velocity.
	}
}

void Decide_Velocity::_make_V1(int V, int ID) { //acceleration
	//std::cout << "debuging V1 start" << std::endl;
	int preceedingcarID = car.around.preceeding.current[ID];
	int Difference_of_Velocity = car.velocity.current[preceedingcarID] - car.velocity.current[ID];
	if (car.distance.current[ID] >= constants.G || Difference_of_Velocity >= 0) {
		if (V + 1 > constants.Vmax[ID]) rule.V1 = constants.Vmax[ID];
		else rule.V1 = V + 1;
	}
	else rule.V1 = V;
	if (rule.V1 < 0) {
		std::cout << "error V1 " << ID << std::endl;
		std::cout << rule.V1 << std::endl;
		std::getchar();
	}
	//std::cout << "debuging V1 end" << std::endl;
}

void Decide_Velocity::_make_V2(int ID) {
	//std::cout << "debuging V2 start" << std::endl;
	rule.V2 = rule.V1;
	if (random.random(1.0) <= constants.q) {
		car.S[ID] = 1;
		if (random.random(1.0) <= constants.r) car.S[ID] = constants.S;
		int previous_preceedingcarID = car.around.preceeding.previous[ID];
		int s = 1;
		for (s; s < car.S[ID]; s++) previous_preceedingcarID = car.around.preceeding.previous[previous_preceedingcarID];
		int distance_previous = car.position.previous[previous_preceedingcarID] - car.position.previous[ID];
		distance_previous -= car.S[ID];
		if (distance_previous < 0) distance_previous += constants.lanelength;
		if (rule.V1 > distance_previous) rule.V2 = distance_previous;
	}

	if (rule.V2 < 0) {
		std::cout << "error V2 " << ID << std::endl;
		std::cout << rule.V2 << std::endl;
		std::getchar();
	}
	//std::cout << "debuging V2 end" << std::endl;
}

void Decide_Velocity::_make_V3(int ID) {
	//std::cout << "debuging V3 start" << std::endl;
	rule.V3 = rule.V2;
	car.S[ID] = constants.S;
	int preceedingcarID = car.around.preceeding.current[ID];
	int s = 1;
	for (s; s < car.S[ID]; s++) preceedingcarID = car.around.preceeding.current[preceedingcarID];
	int distance_current = car.position.current[preceedingcarID] - car.position.current[ID];
	distance_current -= car.S[ID];
	if (distance_current < 0) distance_current += constants.lanelength;
	if (rule.V2 > distance_current) rule.V3 = distance_current;
	if (rule.V3 < 0) {
		std::cout << "error V3 " << ID << std::endl;
		std::cout << rule.V3 << std::endl;
		std::getchar();
	}
	//std::cout << "debuging V3 end" << std::endl;
}

void Decide_Velocity::_make_V4(int ID) {
	//std::cout << "debuging V4 start" << std::endl;
	double p_i = constants.p1;
	rule.V4 = rule.V3;
	int preceedingcarID = car.around.preceeding.current[ID];
	int Difference_of_Velocity = car.velocity.current[preceedingcarID] - car.velocity.current[ID];
	if (Difference_of_Velocity < 0) car.distance.current[ID] += constants.lanelength;
	if (car.distance.current[ID] < constants.G) {
		if (Difference_of_Velocity > 0) p_i = constants.p2;
		if (Difference_of_Velocity == 0) p_i = constants.p3;
		if (Difference_of_Velocity < 0) p_i = constants.p4;
	}
	if (random.random(1.0) < 1 - p_i) {
		if (rule.V3 == 0) rule.V4 = 0;
		else if (rule.V3 - 1 > 1) rule.V4 = rule.V3 - 1;
		else rule.V4 = 1;
	}
	if (rule.V4 < 0) {
		std::cout << "error V4 " << ID << std::endl;
		std::cout << rule.V4 << std::endl;
		std::getchar();
	}
	//std::cout << "debuging V4 end" << std::endl;
}