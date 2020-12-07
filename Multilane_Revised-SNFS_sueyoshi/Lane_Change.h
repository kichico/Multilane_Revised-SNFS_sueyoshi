#ifndef LANECHANGE_H
#define LANECHANGE_H
#include "Decide_Velocity.h"
class Lane_Change : public Decide_Velocity {
private:
	void _pickup_Leadingcar();
	void _pickup_whichcarwillmove();
	void _check_insentives(int lanechangerID, int signal);
	int _get_aroundinformation(int lanechangerID, int turn_signal);
	void _choose_whichlanewillmove(int lanechangerID);
	void _get_aroundinformation_afterlanechanging(int lanenumber, int focalcarposition);
	int leftsidedistance;
	int rightsidedistance;
	int leader;
	bool lanechange_availability;
	struct Status {
		bool left;
		bool right;
	};
	struct front_rear_information {
		int ID;
		int distance;
	};
	struct  Around_Information {
		front_rear_information front;
		front_rear_information rear;
	};
	struct Lanechanger {
		int LanechangerID;
		Status status_signal;
		Around_Information around_information;
	};
	std::vector<Lane_Change::Lanechanger> canditate_ListofLanechanger;
public:
	void lane_change(std::vector<int> canditate_velocity);
	void turnon_turn_signal();
	bool flg_lanechange;
	//std::vector<bool> Update_again;
};

#endif // !LANECHANGE_H

