#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <vector>

//This class store the information of vechiles based on ID
class Car_information {
private:
	struct CurrentandPreviousvector {
		std::vector<int> current;
		std::vector<int> previous;
	};
	struct PreceedingandFollowingcarID {
		CurrentandPreviousvector preceding;
		CurrentandPreviousvector following;
	};
public:
	struct Leadingcar {
		int ID;
		int distance;
		bool existence;
	};
	struct Measure {
		bool measured;
		double elapsed;
	};
	std::vector<int> canditate_velocity;
	std::vector<int> S;
	void initialize(int NumberofCars);
	void Fromcurrent_toprevious();
	CurrentandPreviousvector position, velocity, distance;
	Leadingcar leadingcar;
	PreceedingandFollowingcarID around;
	std::vector<Measure> measure;
};

#endif // !CARINFORMATION_H
