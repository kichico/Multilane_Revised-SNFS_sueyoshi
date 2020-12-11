#include "Multilane_trafficflow_model.h"

void Multilane_trafficflow_model::calculation(int lanelength, int NumberofCars, double C, double D) {
	_defineconstants(lanelength, NumberofCars, C, D);
	std::string fileplace = "C:/Users/sueki/source/repos/Result/Multilane_Sueyoshi/";
	std::string filename_globalrho_flux = "globalrho_flux_multilane.csv";
	filename_globalrho_flux = fileplace + filename_globalrho_flux;
	std::ofstream ofsDF(filename_globalrho_flux, std::ios::app);
	//ofsDF << "globalrho,flux" << std::endl;
	std::string filename_position_time = "position_time.csv";
	filename_position_time = fileplace + filename_position_time;
	std::ofstream ofsPT(filename_position_time, std::ios::app);
	ofsPT << "elapsedtime,position" << std::endl;
	std::cout <<constants.N << " => ";
	initialize(constants.lanelength, constants.N, constants.NumofLane);
	Measurewillbedone = false;
	double global_density = constants.N / constants.lanelength;
	for (int i = 0; i < 1800; i++) _dosimulation();
	Measurewillbedone = true;
	for (int i = 0; i < 300; i++) {
		_dosimulation();
		if (constants.N == 360) for (int ID = 0; ID < constants.N; ID++) if (car.lanenumber[ID] == 0) ofsPT << i << "," << car.position.current[ID] << std::endl;
	}
	ofsDF << constants.N << "," << flux << std::endl;
	std::cout << flux << std::endl;
	flux = 0;
	ofsDF.close();
	ofsPT.close();
}

void Multilane_trafficflow_model::_dosimulation() {
	decide_velocity();
	turnon_turn_signal();
	update_position();
	lane_change(car.canditate_velocity);
	if (flg_lanechange) update_position();
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
	constants.NumofLane = 3;
	constants.C = C;
	constants.D = D;
}