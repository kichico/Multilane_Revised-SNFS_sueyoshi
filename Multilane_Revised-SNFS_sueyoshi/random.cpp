#include "random.h"

Random::Random() {
	int rnd = get_rand(0);
	engine = new svrng_engine_t();
	*engine = svrng_new_mt19937_engine(rnd);
}

Random::Random(int csn) {
	int rnd = get_rand(csn);
	engine = new svrng_engine_t();
	*engine = svrng_new_mt19937_engine(rnd);
}

Random::~Random() {
	svrng_delete_engine(*engine);
	delete engine;
}

int Random::random(int N) {
	svrng_distribution_t dist = svrng_new_uniform_distribution_int(0, N + 1);
	int I = svrng_generate_int(*engine, dist);
	svrng_delete_distribution(dist);
	return I;
}

int Random::random(int Nmin, int Nmax) {
	svrng_distribution_t dist = svrng_new_uniform_distribution_int(Nmin, Nmax + 1);
	int I = svrng_generate_int(*engine, dist);
	svrng_delete_distribution(dist);
	return I;
}

double Random::random(double _D_) {
	svrng_distribution_t dist = svrng_new_uniform_distribution_double(0.0, _D_);
	double D = svrng_generate_double(*engine, dist);
	svrng_delete_distribution(dist);
	return D;
}

int Random::get_rand(int CCC) {
	srand((unsigned int)time(NULL) + CCC * 10000);
	return rand();
}
