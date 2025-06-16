#include "Random_Gen.h"
RandomGenerator& RandomGenerator::get_instance() {
	static RandomGenerator instance;
	return instance;
}

int RandomGenerator::get_random_int(int max) {
	
	std::lock_guard<std::mutex> lock(mtx);
	
	std::uniform_int_distribution<int> distrib(0, max-1);
	return distrib(gen);
}