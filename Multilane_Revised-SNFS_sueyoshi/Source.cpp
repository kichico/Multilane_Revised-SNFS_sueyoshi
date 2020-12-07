#include "Multilane_trafficflow_model.h"

int main() {
	Multilane_trafficflow_model Mlt;
	for (int i = 1; i <= 300; i++) Mlt.calculation(300, i, 0.0, 0.0);
	return 0;
}