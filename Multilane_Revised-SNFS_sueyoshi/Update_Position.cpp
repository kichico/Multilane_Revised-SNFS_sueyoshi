#include "Update_Position.h"

void Update_Position::update_position() {
	//Update_again = std::vector<bool>(constants.N, true);
	car.Fromcurrent_toprevious();
	map.Fromcurrent_toprevious();
	_update_fromLeadingcar(Measurewillbedone);
	if (Measurewillbedone) for (int i = 0; i < constants.N; i++) if (car.position.previous[i] < 100 && car.position.current[i] >= 100) flux++;
}

void Update_Position::_update_fromLeadingcar(bool flg_measure) {
	int ID = 0;
	for (int i = 0; i < constants.N; ++i) {
		car.position.current[i] += car.velocity.current[i] * dt;
		//std::cout << "debug=>" << car.position.current[0] << std::endl;
		if (car.position.current[i] >= constants.lanelength) car.position.current[i] -= constants.lanelength;
	}
}

