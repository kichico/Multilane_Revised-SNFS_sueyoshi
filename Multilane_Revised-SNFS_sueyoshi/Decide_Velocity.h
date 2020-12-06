#ifndef DECIDEVELOCITY_H
#define DECIDEVELOCITY_H
#include "Initialize.h"
class Decide_Velocity :public Initialize {
private:
	struct Rule {
		int V1 = 0;
		int V2 = 0;
		int V3 = 0;
		int V4 = 0;
	};
	void _make_V1(int V, int i);
	void _make_V2(int i);
	void _make_V3(int i);
	void _make_V4(int i);
	bool flg_decide;
	int V = 0;
public:
	//int V_decided = 0;
	void decide_velocity();
	Rule rule;
};

#endif // !DECIDEVELOCITY_H
