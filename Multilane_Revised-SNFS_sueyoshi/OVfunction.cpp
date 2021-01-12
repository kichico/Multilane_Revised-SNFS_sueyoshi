#include "OVfunction.h"


void OVfunction::decidevelocity() {
	dv = std::vector<double>(constants.N, 0.0);
	for (int ID = 0; ID < constants.N; ++ID) {
		OVterm = OV(ID);
		car.velocity.current[ID] = car.velocity.current[ID] + alpha * dt * (OVterm - car.velocity.current[ID]);
		//std::cout << ID << "th car velocity=>" << car.velocity.current[ID] << std::endl;
		//std::cout << ID << "th OVterm=>" << OVterm << std::endl
		//std::cout << ID << "th car position=>" << car.position.current[ID] << std::endl;
	}

}
double OVfunction::OV(int ID) {
	int preceedingcarID = ID - 1;
	if (preceedingcarID< 0) preceedingcarID += constants.N;
	headway = car.position.current[preceedingcarID] - car.position.current[ID] - 5;
	if (headway < 0) headway += constants.lanelength;
	//std::cout << ID << "th car headway=>" << headway << std::endl;
	if (car.around.preceeding.current[ID] < 0) headway += constants.lanelength;
	//std::cout << "debug" << tanh(headway - hc) - tanh(hc) << std::endl;
	V = car.Vmax * (tanh(headway - hc) + tanh(hc)) / 2;
	//std::cout << V << std::endl;
	//std::cout << ID << "th car headway=>" <<headway << std::endl;
	return V;
}
