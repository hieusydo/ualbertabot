#include "Population_Kiter.h"
#include <queue>
#include <random>
#include <utility> 
#include "Common.h"
using namespace SparCraft;

double MU_RATIO = 0.8;

Population_Kiter::Population_Kiter(size_t popSize, size_t numGen) 
	: _popSize(popSize), 
	_numGen(numGen), 
	_mu(popSize * MU_RATIO),
	_lambda(popSize - _mu) {}

// initialize method for population of many KiterDPSEvo
void Population_Kiter::initialize(const GameState& state, PlayerPtr & p1, PlayerPtr & p2) {
	std::random_device rd; // get a random seed from the OS entropy device
	std::mt19937_64 eng(rd()); // use the 64-bit Mersenne Twister 19937 generator with the rd seed
	std::uniform_int_distribution<size_t> distr(0, 150); // define the distribution

	Player_KiterDPSEvo* kiter = dynamic_cast<Player_KiterDPSEvo *>(p1.get());
	kiter->switchOnOffline();
	for (size_t i = 0; i < _popSize; ++i) {
		size_t d = distr(eng);
		kiter->setSafeDist(d);
		int score = eval(kiter, state, p1, p2);
		Chromosome c(d, score);
		_genePool.push(c);
	}
}

//// mutate method
//void Population_Kiter::mutate(Chromosome& c, const GameState & state) {
//	// change the safeDist of one Kiter script at a random location
//	int newDist = c.first->getSafeDist() / 2;
//	c.first->setSafeDist(newDist);
//	c.second = eval(c.first, state);
//}

// evaluation method 
int Population_Kiter::eval(Player_KiterDPSEvo* kiter, const GameState & state, PlayerPtr & p1, PlayerPtr & p2) {
	int kiterScore = 0;
	Game g(state, p1, p2, 1000);
	g.play();
	kiterScore = g.getState().evalLTD2(Players::Player_One);
	return kiterScore;
}

// Comparator for MIN HEAP
bool KiterComparator::operator() (Chromosome lhs, Chromosome rhs) const {
	return lhs.second > rhs.second;
}

void Population_Kiter::printDist() {
	while (!_genePool.empty()) {
		Chromosome c = _genePool.top();
		std::cout << "(" << c.first << " " << c.second << ")" << " ";
		_genePool.pop();
	}
	std::cout << "\n";
}

// EVOLUTION STRATEGY: http://www.cleveralgorithms.com/nature-inspired/evolution/evolution_strategies.html
size_t Population_Kiter::evolveSafeDist(const GameState & state, PlayerPtr & p1, PlayerPtr & p2) {
	Chromosome bestGene;
	//Player_KiterDPSEvo* p0 = new Player_KiterDPSEvo(PlayerModels::KiterDPSEvo);
	//Player_AttackClosest* p1 = new Player_AttackClosest(PlayerModels::AttackClosest);
	//GameState state = GameState();
	//Game g(state, PlayerPtr(p0), PlayerPtr(p1), 20000);

	//std::cout << state.numUnits(0) << " -- " << state.getEnemy(0) << "HIEUU\n";

	// initialize population of Kiters to having random safeDist values
	// and evaluate the baseline population 
	initialize(state, p1, p2);
	printDist();

	//// initialize a genePool - priority queue of Player_Kiter http://www.cplusplus.com/reference/queue/priority_queue/
	//// write comparator for Player_Kiter
	//std::priority_queue<Chromosome, std::vector<Chromosome>, KiterComparator> genePool;
	
	//// evaluate the baseline population
	//// and add to genePool
	//for (Player_KiterDPSEvo* p : _populations) {
	//	int kiterScore = eval(p, state);
	//	Chromosome chromosome(p, kiterScore);
	//	genePool.push(chromosome);
	//}

	//bestGene = genePool.top();
	//// main evolution loop
	//for (size_t i = 0; i < _numGen; ++i) {
	//	//std::cout << "Generation " << i << " with genePool of sz " << genePool.size() << "\n";
	//	// remove lambda worst
	//	for (size_t i = 0; i < _lambda; ++i) {
	//		std::cout << "Worse lambda safeDist: " << genePool.top().first->getSafeDist() << "\n";

	//		genePool.pop();
	//	}

	//	// mutate mu best
	//	for (size_t i = 0; i < _mu; ++i) {
	//		Chromosome c = genePool.top();
	//		mutate(c, state);
	//		genePool.push(c);
	//	}

	//	// find best chromosome of this gen
	//	bestGene = genePool.top();

	//	std::cout << "After gen " << i << " \n";
	//	printDist();
	//}

	////std::cout << "===============\n";
	////for (size_t i = 0; i < genePool.size(); ++i) {
	////	std::cout << "Top lambda safeDist: " << genePool.top().first->getSafeDist() << " with score " << genePool.top().second << "\n";
	////	genePool.pop();
	////}

	//// return best gen
	////Chromosome bestChromosome = genePool.top();
	//int bestDist = bestGene.first->getSafeDist();
	////std::cout << "Best safeDist: " << bestDist << " - Best eval score: " << bestGene.second << "\n";

	//return bestDist;

	return 145;
}

