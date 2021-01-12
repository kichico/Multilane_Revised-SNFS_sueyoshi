#include "Multilane_trafficflow_model.h"

//This is the sourcefile, this files job is only calling "calculation" function that is written in Multilane_trafficflow_model.cpp
int main() {
	Multilane_trafficflow_model Mlt;
	Mlt.calculation(2000.0, 230, 0.0, 0.0);
	return 0;
}