#include "Multilane_trafficflow_model.h"

//This is the main code of this single lane CA model.
//In this code, there are one big function "calculation" and two subfunction "_defineconstants" "_sosimulation"


//In this function, some parameters are defined and something are prepared for output
//Argument C and D is coorporation rate and defraction rate, but they don't related with this "single" lane program.

void Multilane_trafficflow_model::calculation(int lanelength, int NumberofCars, double C, double D) {
	_defineconstants(lanelength, NumberofCars, C, D);
	std::string fileplace = "C:/Users/sueki/source/repos/Result/Multilane_Sueyoshi/";
	std::string filename_globalrho_flux = "globalrho_flux.csv";
	filename_globalrho_flux = fileplace + filename_globalrho_flux;
	std::ofstream ofsDF(filename_globalrho_flux, std::ios::app);
	std::string filename_position_time = "position_time.csv";
	filename_position_time = fileplace + filename_position_time;
	std::ofstream ofsPT(filename_position_time, std::ios::app);
	ofsPT << "elapsedtime,position" << std::endl;
	std::cout <<constants.N << " => ";
	initialize(constants.lanelength,constants.N); 
	Measurewillbedone = false;
	double global_density = constants.N / constants.lanelength;
	for (int i = 0; i < 1800; i++) {
		_dosimulation();
	}
	Measurewillbedone = true;
	for (int i = 0; i < 300; i++) {
		_dosimulation();
		if (constants.N == 180) {
			for (int ID = 0; ID < constants.N; ID++) ofsPT << i << ","<< car.position.current[ID] << std::endl;
			std::cout << "debug..." << std::endl;
		}
	}
	ofsDF << constants.N << "," << flux << std::endl;
	std::cout << flux << std::endl;
	flux = 0;
	ofsDF.close();
	ofsPT.close();
}

void Multilane_trafficflow_model::_dosimulation() {
	decide_velocity();
	update_position();
}

void Multilane_trafficflow_model::_defineconstants(int lanelength, int NumberofCars, double C, double D) {
	constants.r = 0.99;
	constants.q = 0.99;
	constants.p1 = 0.999;
	constants.p2 = 0.99;
	constants.p3 = 0.98;
	constants.p4 = 0.01;
	constants.G = 15;
	constants.S = 2;
	constants.N = NumberofCars;
	constants.lanelength = lanelength;
}