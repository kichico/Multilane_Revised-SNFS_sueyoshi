#ifndef RANDOM_H
#define RANDOM_H
#include <stdlib.h>
#include <stdio.h>
#include <svrng.h>
#include <time.h>
#include <cstdlib>
#include <iostream>

class Random {
public:
	Random();
	Random(int complement_seed_number);
	~Random();
	int random(int N);
	int random(int Nmin, int Nmax);
	double random(double D);
private:
	svrng_engine_t *engine;
	int get_rand(int CCC);
};

#endif	//RANDOM_H
