#include "Lane_Change.h"

void Lane_Change::turnon_turn_signal() {
	lanechange_availability = false;
	flg_lanechange = false;
	_pickup_Leadingcar();
	_pickup_whichcarwillmove();
	ListofLanechanger.clear();
	ListofLanechanger_signal.clear();
	if (!canditate_ListofLanechanger.empty()) {
		int NumberofLanechangers = canditate_ListofLanechanger.size();
		for (int i = 0; i < NumberofLanechangers; i++) {
			_check_insentives(i, car.signal_status.left);
			_check_insentives(i, car.signal_status.right);
			_choose_whichlanewillmove(i);
		}
	}
}

void Lane_Change::lane_change(std::vector<int> canditate_velocity) {
	bool lanechange_willbedone = false;
	if (lanechange_availability == true) {
		int NumberofLanechangers = ListofLanechanger.size();
		for (int i = 0; i < ListofLanechanger.size(); i++) {
			int ID = ListofLanechanger[i];
			int lanechange = 1;
			int position = car.position.current[ListofLanechanger[i]];
			if (ListofLanechanger_signal[i] == car.signal_status.left) lanechange = -1;
			int next_lane = car.lanenumber[ID] + lanechange;
			if (map.NumberofCars_at_thislane[next_lane] == 0) lanechange_willbedone = true;
			if (map.recorded.existence.current[next_lane][position]) {
				lanechange_willbedone = false;
				return;
			}
			if (!map.recorded.existence.current[next_lane][position]) {
				int j = 1;
				while (true) {
					int followingcar_position = position - j;
					if (followingcar_position < 0) followingcar_position += constants.lanelength;
					bool followingcar_existence_at_sidelane = map.recorded.existence.current[next_lane][followingcar_position];
					if (followingcar_existence_at_sidelane) {
						int followerposition = position - j;
						int followingcar_ID_at_sidelane = map.recorded.ID.current[next_lane][followerposition];
						if (j >= car.velocity.current[followingcar_ID_at_sidelane] - car.velocity.current[ID]) lanechange_willbedone = true;
						break;
					}
					else j++;
				}
			}
			if (lanechange_willbedone) {
				flg_lanechange = true;
				if (car.leadingcar[car.lanenumber[ID]].ID == ID) car.leadingcar[car.lanenumber[ID]].existence = false;
				map.NumberofCars_at_thislane[car.lanenumber[ID]]--;
				map.recorded.existence.current[car.lanenumber[ID]][position] = false;
				_get_aroundinformation_afterlanechanging(car.lanenumber[ID], car.position.current[ID]);
				car.lanenumber[ID] += lanechange;
				map.NumberofCars_at_thislane[car.lanenumber[ID]]++;
				map.recorded.existence.current[car.lanenumber[ID]][position] = true;
				_get_aroundinformation_afterlanechanging(car.lanenumber[ID], car.position.current[ID]);
			}
		}
	}
}

void Lane_Change::_pickup_Leadingcar() {
	std::vector<int> listofLeadingcars(0);
	for (int i = 0; i < constants.NumofLane; i++) listofLeadingcars.emplace_back(car.leadingcar[i].ID);
	int NumofLeadingcar = listofLeadingcars.size();
	int pickedupLeadingcar = random.random(NumofLeadingcar - 1);
	leader = listofLeadingcars[pickedupLeadingcar];
}

void Lane_Change::_pickup_whichcarwillmove() {
	int cnt_pickup = 0;
	int ID = leader;
	canditate_ListofLanechanger.clear();
	for (int i = 0; i < constants.lanelength; i++) {
		int position = car.position.current[leader] - i;
		if (position < 0) position += constants.lanelength;
		std::vector<Lane_Change::Lanechanger> Checksameposition_at_differentlane;
		for (int lanenumber = 0; lanenumber < constants.NumofLane; lanenumber++) {
			if (map.recorded.existence.current[lanenumber][position]) {
				Lane_Change::Lanechanger candidate_lanechanger;
				if (car.assigned_strategy[map.recorded.ID.current[lanenumber][position]] == car.strategy.D) {
					candidate_lanechanger.LanechangerID = map.recorded.ID.current[lanenumber][position];
					candidate_lanechanger.status_signal.left = false;
					candidate_lanechanger.status_signal.right = false;
					Checksameposition_at_differentlane.emplace_back(candidate_lanechanger);
				}
				cnt_pickup++;
			}
		}
		if (!Checksameposition_at_differentlane.empty()) {//decide the order of check insentive
			if (Checksameposition_at_differentlane.size() > 1) {
				while (Checksameposition_at_differentlane.size() > 0) {
					int Numofcaratsameposition = Checksameposition_at_differentlane.size();
					int randompickup = random.random(Numofcaratsameposition - 1);
					Lane_Change::Lanechanger randomlanechanger = Checksameposition_at_differentlane[randompickup];
					canditate_ListofLanechanger.emplace_back(randomlanechanger);
					Checksameposition_at_differentlane.erase(Checksameposition_at_differentlane.begin() + randompickup);
				}
			}
			else canditate_ListofLanechanger.emplace_back(Checksameposition_at_differentlane[0]);
		}
		if (cnt_pickup >= constants.N) break;
	}
}

void Lane_Change::_check_insentives(int lanechangerID, int signal) {
	bool insentivewillbemet = false;
	int ID = canditate_ListofLanechanger[lanechangerID].LanechangerID;
	int current_lane = car.lanenumber[ID];
	int side_lane = current_lane;
	if (signal == car.signal_status.left) {
		if (current_lane > 0) {
			insentivewillbemet = true;
			side_lane -= 1;
		}
	}
	else if (signal == car.signal_status.right) {
		if (current_lane < constants.NumofLane - 1) {
			insentivewillbemet = true;
			side_lane += 1;
		}
	}
	if (insentivewillbemet) {
		//Exception handling(—áŠOˆ—)
		if (map.recorded.existence.current[side_lane][car.position.current[ID]]) return;
		if (car.distance.current[ID] > car.velocity.current[ID] - car.velocity.current[car.around.preceeding.current[ID]]) {
			return;
		}
		//
		if (signal == car.signal_status.left) {
			if (map.NumberofCars_at_thislane[side_lane] == 0) {
				canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance = constants.lanelength;
				canditate_ListofLanechanger[lanechangerID].status_signal.left = true;
				lanechange_availability = true;
			}
			else {
				leftsidedistance = _get_aroundinformation(lanechangerID, signal);
				if (leftsidedistance > car.velocity.current[ID] - car.velocity.current[canditate_ListofLanechanger[lanechangerID].around_information.preceeding.ID]) {
					lanechange_availability = true;
					canditate_ListofLanechanger[lanechangerID].status_signal.left = true;
				}
			}
		}
		if (signal == car.signal_status.right) {
			if (map.NumberofCars_at_thislane[side_lane] == 0) {
				canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance = constants.lanelength;
				canditate_ListofLanechanger[lanechangerID].status_signal.right = true;
				lanechange_availability = true;
			}
			else {
				rightsidedistance = _get_aroundinformation(lanechangerID, signal);
				if (rightsidedistance > car.velocity.current[ID] - car.velocity.current[canditate_ListofLanechanger[lanechangerID].around_information.preceeding.ID]) {
					lanechange_availability = true;
					canditate_ListofLanechanger[lanechangerID].status_signal.right = true;
				}
			}
		}
		//std::cout << lanechangerID << "th canditatelistoflanechanger's signal left=>" << canditate_ListofLanechanger[lanechangerID].status_signal.left << ", right" << canditate_ListofLanechanger[lanechangerID].status_signal.right << std::endl;
	}
	//std::cout << lanechangerID << "th canditatelistoflanechanger's signal left=>" << canditate_ListofLanechanger[lanechangerID].status_signal.left << ", right=>" << canditate_ListofLanechanger[lanechangerID].status_signal.right << std::endl;

}

int Lane_Change::_get_aroundinformation(int lanechangerID, int turn_signal) {
	//std::cout << "debug lanechange3 " << lanechangerID << std::endl;
	int side_lane = 0;
	int ID = canditate_ListofLanechanger[lanechangerID].LanechangerID;
	int n = 0;
	side_lane = car.lanenumber[ID] - 1;
	if (turn_signal == car.signal_status.right) side_lane = car.lanenumber[ID] + 1;
	while (true) {
		int front_position = car.position.current[ID] + n;
		int rear_position = car.position.current[ID] - n;
		if (front_position >= constants.lanelength) front_position -= constants.lanelength;
		if (rear_position < 0) rear_position += constants.lanelength;
		//std::cout << "frontposition=>" << front_position << std::endl;
		if (map.recorded.existence.current[side_lane][front_position]) {
			int preceedingcarID = map.recorded.ID.current[side_lane][front_position];
			canditate_ListofLanechanger[lanechangerID].around_information.preceeding.ID = map.recorded.ID.current[side_lane][front_position];
			canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance = n;
			canditate_ListofLanechanger[lanechangerID].around_information.following.ID = car.around.following.current[preceedingcarID];
			canditate_ListofLanechanger[lanechangerID].around_information.following.distance = car.position.current[ID] - car.position.current[canditate_ListofLanechanger[lanechangerID].around_information.following.ID];
			if (canditate_ListofLanechanger[lanechangerID].around_information.following.distance < 0) canditate_ListofLanechanger[lanechangerID].around_information.following.distance += constants.lanelength;
			break;
		}
		if (map.recorded.existence.current[side_lane][rear_position]) {
			int followingcarID = map.recorded.ID.current[side_lane][rear_position];
			canditate_ListofLanechanger[lanechangerID].around_information.following.ID = map.recorded.ID.current[side_lane][rear_position];
			canditate_ListofLanechanger[lanechangerID].around_information.following.distance = n;
			canditate_ListofLanechanger[lanechangerID].around_information.preceeding.ID = car.around.preceeding.current[followingcarID];
			canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance = car.position.current[canditate_ListofLanechanger[lanechangerID].around_information.preceeding.ID] - car.position.current[ID];
			if (canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance < 0) canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance += constants.lanelength;
			break;
		}
		n++;
	}
	//std::cout << "debug lanechange4" << std::endl;
	return canditate_ListofLanechanger[lanechangerID].around_information.preceeding.distance;
}



void Lane_Change::_choose_whichlanewillmove(int lanechangerID) {
	if (canditate_ListofLanechanger[lanechangerID].status_signal.left == true && canditate_ListofLanechanger[lanechangerID].status_signal.right == true) {
		if (leftsidedistance > rightsidedistance) canditate_ListofLanechanger[lanechangerID].status_signal.right = false;
		else if (leftsidedistance < rightsidedistance) canditate_ListofLanechanger[lanechangerID].status_signal.left = false;
		else {
			double var_choice_whichlane = random.random(1.0);
			if (var_choice_whichlane <= 0.5) canditate_ListofLanechanger[lanechangerID].status_signal.right = false;
			else canditate_ListofLanechanger[lanechangerID].status_signal.left = false;
		}
	}
	if (canditate_ListofLanechanger[lanechangerID].status_signal.left || canditate_ListofLanechanger[lanechangerID].status_signal.right) {
		ListofLanechanger.emplace_back(canditate_ListofLanechanger[lanechangerID].LanechangerID);
		if (canditate_ListofLanechanger[lanechangerID].status_signal.left == true) {
			ListofLanechanger_signal.emplace_back(car.signal_status.left);
		}
		else if (canditate_ListofLanechanger[lanechangerID].status_signal.right == true) {
			ListofLanechanger_signal.emplace_back(car.signal_status.right);
		}
	}
}

void Lane_Change::_get_aroundinformation_afterlanechanging(int lanenumber, int focalcarposition) {
	int preceedingcarID, followingcarID;
	int preceedingcarposition, followingcarposition;
	bool preceedingcarisidentified = false;
	bool followingcarisidentified = false;
	bool identifyingiscompleted = false;
	preceedingcarposition = focalcarposition + 1;
	followingcarposition = focalcarposition - 1;
	int ID = map.recorded.ID.current[lanenumber][focalcarposition];
	int canditateLeadingcarID;
	int largerdistance = 0;
	while (!identifyingiscompleted) {
		if (preceedingcarposition >= constants.lanelength) preceedingcarposition -= constants.lanelength;
		if (followingcarposition < 0) followingcarposition += constants.lanelength;
		if (!preceedingcarisidentified) {
			if (map.recorded.existence.current[lanenumber][preceedingcarposition]) preceedingcarisidentified = true;
			else preceedingcarposition++;
		}
		if (!followingcarisidentified) {
			if (map.recorded.existence.current[lanenumber][followingcarposition]) followingcarisidentified = true;
			else followingcarposition--;
		}
		if (preceedingcarisidentified == true && followingcarisidentified == true) identifyingiscompleted = true;
	}
	preceedingcarID = map.recorded.ID.current[lanenumber][preceedingcarposition];
	followingcarID = map.recorded.ID.current[lanenumber][followingcarposition];
	if (!map.recorded.existence.current[lanenumber][focalcarposition]) {
		int headway = preceedingcarposition - followingcarposition;
		if (headway < 0) headway += constants.lanelength;
		car.around.preceeding.current[followingcarID] = preceedingcarID;
		car.distance.current[followingcarID] = headway;
		car.around.following.current[preceedingcarID] = followingcarID;
		//—vC³
		car.distance.current[preceedingcarID] = headway;
		canditateLeadingcarID = followingcarID;
	}
	else {
		int preceeding_focal_distance = preceedingcarposition - focalcarposition;
		if (preceeding_focal_distance < 0) preceeding_focal_distance += constants.lanelength;
		int focal_following_distance = focalcarposition - followingcarposition;
		if (focal_following_distance < 0) focal_following_distance += constants.lanelength;
		car.around.preceeding.current[ID] = preceedingcarID;
		car.around.following.current[preceedingcarID] = ID;
		car.distance.current[ID] = car.distance.current[preceedingcarID] = preceeding_focal_distance;
		car.around.following.current[ID] = followingcarID;
		car.around.preceeding.current[followingcarID] = ID;
		car.distance.current[followingcarID] = focal_following_distance;
		if (preceeding_focal_distance >= focal_following_distance) {
			largerdistance = preceeding_focal_distance;
			canditateLeadingcarID = preceedingcarID;
		}
		else {
			largerdistance = focal_following_distance;
			canditateLeadingcarID = followingcarID;
		}

	}
	if (!car.leadingcar[lanenumber].existence) {
		car.leadingcar[lanenumber].existence = true;
		car.leadingcar[lanenumber].ID = canditateLeadingcarID;
		car.leadingcar[lanenumber].distance = largerdistance;
	}
	else {
		if (largerdistance > car.leadingcar[lanenumber].distance) {
			car.leadingcar[lanenumber].ID = canditateLeadingcarID;
			car.leadingcar[lanenumber].distance = largerdistance;
		}
	}
}