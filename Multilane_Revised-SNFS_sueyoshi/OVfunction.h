#ifndef OVF
#define OVF
#include "Initialize.h"
#include <math.h>
#include <cmath>

class OVfunction : public Initialize {
public:
	void decidevelocity();
	double dt = 0.1;
	std::vector<double> dv;
private:
	double alpha = 0.9;
	double hc = 21.1;
	double OVterm;
	double V;
	double headway;
	double OV(int ID);
};

#endif // !OVF



