#ifndef UPDATEPOSITION_H
#define UPDATEPOSITION_H
#include "OVfunction.h"
class Update_Position :public OVfunction {
private:
	void _update_fromLeadingcar(bool flg_measure);
	//void _move_forward_car(int ID);
	int cnt_update = 0;
	bool flg_updated = false;
public:
	bool Measurewillbedone;
	void update_position();
	std::vector<bool> Update_again;
	int flux;
};

#endif // !UPDATEPOSITION_H
