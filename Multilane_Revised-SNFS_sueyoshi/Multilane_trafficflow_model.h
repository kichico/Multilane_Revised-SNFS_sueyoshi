#ifndef MULTILANETRAFFICFLOW_H
#define MULTILANETRAFFICFLOW_H
#include "Update_Position.h"
#include <fstream>
class Multilane_trafficflow_model : public Update_Position {
private:
	void _dosimulation();
	void _defineconstants(int lanelength, int NumberofCars, double C, double D);
public:
	void calculation(int lanelength, int NumberofCars, double C, double D);
};


#endif // !MULTILANETRAFFICFLOW_H