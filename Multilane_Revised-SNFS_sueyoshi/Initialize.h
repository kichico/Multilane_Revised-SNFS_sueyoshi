#ifndef INITIALIZE_H
#define INITIALIZE_H
#include "Car_information.h"
#include "Constants.h"
#include "Map_information.h"
#include "random.h"
#include "String.h"
#include <iostream>
#include <fstream>

//This class is superviser of some classes, "Car_information" , "Map_information" and more.
class Initialize {
private:
	void _initialplacement(double lanelength, int NumberofCars);
	//void _defineVmax(bool flg_ditributedVmax, int NumberofCars);
public:
	bool flg_distributedVmax = false;
	Car_information car;
	Map_information map;
	Random random;
	Constants constants;
	void initialize(double lanelength, int NumberofCars);
};

#endif // !INITIALIZE_H
