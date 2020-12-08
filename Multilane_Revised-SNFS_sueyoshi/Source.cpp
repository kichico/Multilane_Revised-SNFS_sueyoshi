#include "Multilane_trafficflow_model.h"

int main() {
	Multilane_trafficflow_model Mlt;
	int i = 15;
	for (i; i < 300; i += 15) Mlt.calculation(300, i, 0.0, 0.0);
	return 0;
}