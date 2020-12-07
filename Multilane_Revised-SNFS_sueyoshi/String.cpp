#include "String.h"

std::string string::int_to_string(int I, int decimal) {
	std::stringstream ss;
	ss << std::fixed;
	ss << std::setprecision(decimal) << double(I);
	return ss.str();
}

std::string string:: double_to_string(double D, int decimal) {
	std::stringstream ss;
	ss << std::fixed;
	ss << std::setprecision(decimal) << D;
	return ss.str();
}

int string::stoi(std::string str) {
	std::istringstream ss(str);
	int I;
	ss >> I;
	return I;
}
