#include "Population_Kiter.h"
#include <queue>
#include <utility> 
#include "Common.h"
using namespace SparCraft;

double MU_RATIO = 0.8;

Population_Kiter::Population_Kiter(size_t popSize, size_t numGen) : _popSize(popSize), _numGen(numGen) {
	_populations = {};
	_mu = (size_t) popSize * MU_RATIO;
	_lambda = popSize - _mu;
}

// initialize method for population of many KiterDPSEvo
void Population_Kiter::initialize() {
	for (size_t i = 0; i < _popSize; ++i) {
		Player_KiterDPSEvo* kiter = new Player_KiterDPSEvo(PlayerModels::KiterDPSEvo);
		kiter->setSafeDist(rand());
		_populations.push_back(kiter);
	}
}

// mutate method
void Population_Kiter::mutate(Chromosome& c, const GameState & state) {
	// change the safeDist of one Kiter script at a random location
	int newDist = c.first->getSafeDist() / 2;
	c.first->setSafeDist(newDist);
	c.second = eval(c.first, state);
}

// evaluation method
int Population_Kiter::eval(Player_KiterDPSEvo* kiter, const GameState & state) {
	int kiterScore = 0;
	Game g = Game(state, 100);
	//g.play(); 
	
	const IDType player = kiter->getType();
	kiterScore = g.getState().eval(player, SparCraft::EvaluationMethods::LTD2).val();

	return kiterScore;
}

// Comparator for MIN HEAP
bool KiterComparator::operator() (std::pair<Player_KiterDPSEvo*, int> lhs, std::pair<Player_KiterDPSEvo*, int> rhs) const {
	return lhs.second > rhs.second;
}

// EVOLUTION STRATEGY: http://www.cleveralgorithms.com/nature-inspired/evolution/evolution_strategies.html
size_t Population_Kiter::evolveSafeDist(const GameState & state) {
	Chromosome bestGene;

	// initializa population of Kiters to having random safeDist values
	initialize();

	// initialize a genePool - priority queue of Player_Kiter http://www.cplusplus.com/reference/queue/priority_queue/
	// write comparator for Player_Kiter
	std::priority_queue<std::pair<Player_KiterDPSEvo*, int>, std::vector<std::pair<Player_KiterDPSEvo*, int>>, KiterComparator> genePool;

	// evaluate the baseline population
	// and add to genePool
	int i = 0;
	for (Player_KiterDPSEvo* p : _populations) {
		int kiterScore = eval(p, state) + i;
		std::pair<Player_KiterDPSEvo*, int> chromosome(p, kiterScore);
		genePool.push(chromosome);
		i += 10;
	}

	bestGene = genePool.top();
	// main evolution loop
	for (size_t i = 0; i < _numGen; ++i) {
		//std::cout << "Generation " << i << " with genePool of sz " << genePool.size() << "\n";
		// remove lambda worst
		for (size_t i = 0; i < _lambda; ++i) {
			//std::cout << "Top lambda safeDist: " << genePool.top().first->getSafeDist() << "\n";
			genePool.pop();
		}

		// mutate mu best
		for (size_t i = 0; i < _mu; ++i) {
			Chromosome c = genePool.top();
			mutate(c, state);
			genePool.push(c);
		}

		// find best chromosome of this gen
		bestGene = genePool.top();
	}

	//std::cout << "===============\n";
	//for (size_t i = 0; i < genePool.size(); ++i) {
	//	std::cout << "Top lambda safeDist: " << genePool.top().first->getSafeDist() << " with score " << genePool.top().second << "\n";
	//	genePool.pop();
	//}

	// return best gen
	//Chromosome bestChromosome = genePool.top();
	int bestDist = bestGene.first->getSafeDist();
	//std::cout << "Best safeDist: " << bestDist << " - Best eval score: " << bestGene.second << "\n";

	return bestDist;
}

Population_Kiter::~Population_Kiter() {
	for (Player_KiterDPSEvo* p : _populations) {
		delete p;
	}
	_populations.clear();
}
