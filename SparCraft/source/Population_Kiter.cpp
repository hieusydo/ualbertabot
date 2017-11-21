#include "Population_Kiter.h"

using namespace SparCraft;

Population_Kiter::Population_Kiter(size_t popSize, size_t numGen) {
	_popSize = popSize;
	_numGen = numGen;
	_populations = std::vector<IDType>(popSize, PlayerModels::KiterDPSEvo);
}

// initialize method for population of many KiterDPSEvo
void Population_Kiter::initialize() {}

// mutate method
void Population_Kiter::mutate() {
	// change the safeDist of one Kiter script at a random location
}

// evaluation method
int eval() {}

size_t Population_Kiter::evolveSafeDist() {
	for (size_t i = 0; i <= _numGen; ++i) {
		// mutate

		// remove the worst one each time
	}
}
