#ifndef CARINFORMATION_H
#define CARINFORMATION_H

#include <vector>
class Car_information {
private:
	struct CurrentandPreviousvector {
		std::vector<int> current;
		std::vector<int> previous;
	};
	struct PreceedingandFollowingcarID {
		CurrentandPreviousvector preceeding;
		CurrentandPreviousvector following;
	};
	struct Signalstatus {
		const int left = 0;
		const int right = 1;
	};
	struct Strategy {
		const int C = 0;
		const int D = 1;
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
	std::vector<int> lanenumber;
	std::vector<int> S;
	std::vector<int> signal;
	Signalstatus signal_status;
	Strategy strategy;
	void initialize(int NumberofCars, int NumberofLanes);
	void Fromcurrent_toprevious();
	CurrentandPreviousvector position, velocity, distance;
	std::vector<Leadingcar> leadingcar;
	PreceedingandFollowingcarID around;
	std::vector<Measure> measure;
	std::vector<int> assigned_strategy;
	
};

#endif // !CARINFORMATION_H
