#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <vector>

//This class store the information of vechiles based on ID
class Car_information {
private:
	struct CurrentandPreviousvector {
		std::vector<double> current;
		std::vector<double> previous;
	};
	struct PreceedingandFollowingcarID {
		CurrentandPreviousvector preceeding;
		CurrentandPreviousvector following;
	};
public:
	struct Leadingcar {
		int ID;
		double distance;
		bool existence;
	};
	struct Measure {
		bool measured;
		double elapsed;
	};
	std::vector<double> canditate_velocity;
	//std::vector<int> S;
	void initialize(int NumberofCars);
	void Fromcurrent_toprevious();
	double Vmax = 27;
	CurrentandPreviousvector position, velocity, distance;
	Leadingcar leadingcar;
	PreceedingandFollowingcarID around;
	std::vector<Measure> measure;
};

#endif // !CARINFORMATION_H
