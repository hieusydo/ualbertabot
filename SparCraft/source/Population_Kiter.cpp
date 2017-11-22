#include "Population_Kiter.h"
#include <queue>
using namespace SparCraft;

Population_Kiter::Population_Kiter(size_t popSize, size_t numGen) {
	_popSize = popSize;
	_numGen = numGen;
	_populations = std::vector<Player_KiterDPSEvo*>(popSize, new Player_KiterDPSEvo(PlayerModels::KiterDPSEvo));
}

// initialize method for population of many KiterDPSEvo
void Population_Kiter::initialize() {}

// mutate method
void Population_Kiter::mutate() {
	// change the safeDist of one Kiter script at a random location
}

// evaluation method
int Population_Kiter::eval(const GameState & state) {
	Game g = Game(state, 100);
	g.play(); 
	
	// IDPlayer or actual pointer?
	const IDType player = PlayerModels::KiterDPSEvo;
	return g.getState().eval(player, SparCraft::EvaluationMethods::LTD2).val();
}

size_t Population_Kiter::evolveSafeDist(const GameState & state) {
	// EVOLUTION STRATEGY: http://www.cleveralgorithms.com/nature-inspired/evolution/evolution_strategies.html

	// initializa population of Kiters to having random safeDist values
	for (Player_KiterDPSEvo*& p : _populations) {
		p->setSafeDist(rand());
	}

	size_t score = 0;

	// initialize priority queue of Player_KiterL http://www.cplusplus.com/reference/queue/priority_queue/
	// write comparator for Player_Kiter

	// evaluate the baseline population
	// and add to genePool
	
	// main while loop
		// remove lambda worst

		// mutate mu best

		// find best chromosome of this gen

	// return best gen
	return score;
}
