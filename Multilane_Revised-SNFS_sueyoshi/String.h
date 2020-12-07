#ifndef STRING_H
#define STRING_H
#include <string>
#include <sstream>
#include <string.h>
#include <iomanip>
class string {
	std::string int_to_string(int I, int decimal);
	std::string double_to_string(double D, int decimal);
	int stoi(std::string str);
};

#endif // STRING_H