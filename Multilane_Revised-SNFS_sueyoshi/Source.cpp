#include "Multilane_trafficflow_model.h"

//This is the sourcefile, this files job is only calling "calculation" function that is written in Multilane_trafficflow_model.cpp
int main() {
	Multilane_trafficflow_model Mlt;
	int i = 15;
	for (i; i < 300; i += 15) Mlt.calculation(300, i, 0.0, 0.0);
	return 0;
}