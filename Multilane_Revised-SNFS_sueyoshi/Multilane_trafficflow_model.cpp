#include "Multilane_trafficflow_model.h"

//This is the main code of this single lane CA model.
//In this code, there are one big function "calculation" and two subfunction "_defineconstants" "_sosimulation"


//In this function, some parameters are defined and something are prepared for output
//Argument C and D is coorporation rate and defraction rate, but they don't related with this "single" lane program.

void Multilane_trafficflow_model::calculation(double lanelength, int NumberofCars, double C, double D) {
	_defineconstants(lanelength, NumberofCars, C, D);
	std::string fileplace = "C:/Users/sueki/source/repos/Result/Multilane_Sueyoshi/";
	std::string FilenameGF = "C:/Users/sueki/source/repos/Result/OptimalVelocitymodel/Optimal_Velocity_Greenfunction.csv";
	std::string filename_globalrho_flux = "globalrho_flux_greenfunction.csv";
	std::string filename_position_time = "position_time_greenfunction.csv";
	filename_globalrho_flux = fileplace + filename_globalrho_flux;
	filename_position_time = fileplace + filename_position_time;
	std::ofstream ofsDF(filename_globalrho_flux, std::ios::app);
	std::ofstream ofsGF(FilenameGF);
	std::ofstream ofsPT(filename_position_time);
	ofsGF << "elapsedtime,velocity" << std::endl;
	ofsPT << "elapsedtime,position" << std::endl;
	std::cout <<constants.N << " => ";
	initialize(constants.lanelength,constants.N); 
	Measurewillbedone = false;
	double global_density = constants.N / constants.lanelength;
	for (int i = 0; i < 500; i++) {
		_dosimulation();
		for (int ID = 0; ID < constants.N; ++ID) ofsGF << ID << "," << i * 0.1 << "," << car.velocity.current[ID] << "," << car.position.current[ID] << std::endl;
		for (auto position : car.position.current) ofsPT << (double)i * dt << "," << position << std::endl;
	}
	Measurewillbedone = true;
	/*for (int i = 0; i < 300; i++) {
		_dosimulation();
		ofsGF << i * 0.1 << "," << car.velocity.current[10] << "," << car.position.current[10] << std::endl;
		for (auto position:car.position.current) ofsPT << i * dt << "," << position << std::endl;
	}*/
	ofsDF << constants.N << "," << flux << std::endl;
	std::cout << flux << std::endl;
	flux = 0;
	ofsDF.close();
	ofsGF.close();
	ofsPT.close();
}

void Multilane_trafficflow_model::_dosimulation() {
	decidevelocity();
	update_position();
}

void Multilane_trafficflow_model::_defineconstants(double lanelength, int NumberofCars, double C, double D) {
	constants.S = 2;
	constants.N = NumberofCars;
	constants.lanelength = lanelength;
}