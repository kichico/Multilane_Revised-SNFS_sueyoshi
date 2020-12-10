#include "Multilane_trafficflow_model.h"

int main() {
	Multilane_trafficflow_model Mlt;
	int i = 360;
	for (i; i < 900; i += 45) Mlt.calculation(300, i, 0.5, 0.5);
	return 0;
}