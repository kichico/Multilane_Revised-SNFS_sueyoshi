#ifndef CAR_INFORMATION.H
#define CAR_INFORMATION.H

#include <vector>
class Car_information {
private:
	struct CurrentandPrevious {
		std::vector<int> current;
		std::vector<int> previous;
	};
	struct PreceedingandFollowing {
		std::vector<int> preceeding;
		std::vector<int> following;
	};
public:
	struct Measure {
		bool measured;
		double elapsed;
	};
	std::vector<int> canditate_velocity;
	//std::vector<int> lanenumber;
	std::vector<int> S;
	void initialize(int NumberofCars);
	void Fromcurrent_toprevious();
	CurrentandPrevious position, velocity, distance;
	std::vector<PreceedingandFollowing> around;
	std::vector<Measure> measure;
};

#endif // !CAR_INFORMATION.H
