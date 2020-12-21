#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "Car_information.h"
#include "Constants.h"
#include "Map_information.h"
#include "random.h"
#include "String.h"
#include <iostream>
#include <fstream>

class Initialize {
private:
	void _initialplacement(int lanelength, int NumberofCars);
	void _defineVmax(bool flg_ditributedVmax, int NumberofCars);
public:
	bool flg_distributedVmax = false;
	Car_information car;
	Map_information map;
	Random random;
	Constants constants;
	void initialize(int lanelength, int NumberofCars);
};

#endif // !INITIALIZE_H
