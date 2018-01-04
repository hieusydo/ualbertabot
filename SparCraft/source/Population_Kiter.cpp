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
    //std::cout << "initialize\n";

	std::random_device rd; // get a random seed from the OS entropy device
	std::mt19937_64 eng(rd()); // use the 64-bit Mersenne Twister 19937 generator with the rd seed
	std::uniform_int_distribution<size_t> distr(0, 150); // define the distribution

	Player_KiterDPSEvo* kiter = dynamic_cast<Player_KiterDPSEvo *>(p1.get());
	kiter->switchOnOffline();
	for (size_t i = 0; i < _popSize; ++i) {
		size_t d = distr(eng);
		kiter->setSafeDist(d);
		int score = eval(state, p1, p2);
		Chromosome c(d, score);
		_genePool.push_back(c);
	}
}

// mutate method
Chromosome Population_Kiter::mutate(const Chromosome& c, const GameState & state, PlayerPtr & p1, PlayerPtr & p2) {
    //std::cout << "mutate\n";

    Chromosome res;
    Player_KiterDPSEvo* kiter = dynamic_cast<Player_KiterDPSEvo *>(p1.get());
    kiter->switchOnOffline();
    // Consider mutation by wiggling the parent dist +/- 5
    kiter->setSafeDist(c.first - 5);
    int leftScore = eval(state, p1, p2);
    kiter->setSafeDist(c.first + 5);
    int rightScore = eval(state, p1, p2);
    // Choose the offspring with better fitness eval score
    res.first = (leftScore > rightScore) ? (c.first - 5) : (c.first + 5);
    res.second = (leftScore > rightScore) ? leftScore : rightScore;
    return res;
}

// evaluation method 
int Population_Kiter::eval(const GameState & state, PlayerPtr & p1, PlayerPtr & p2) {
	int kiterScore = 0;
	Game g(state, p1, p2, 1000);
	g.play();
	kiterScore = g.getState().evalLTD2(Players::Player_One);
	return kiterScore;
}

bool KiterComparator::operator() (Chromosome lhs, Chromosome rhs) const {
    if (increasing) {
        return lhs.second < rhs.second;
    } 
    return lhs.second > rhs.second;
}

void Population_Kiter::printDist() {
    for (auto it = _genePool.begin(); it != _genePool.end(); it++) {
        std::cout << "(" << it->first << ", S: " << it->second << ") "; 
    }
	std::cout << "\n";
}

// EVOLUTION STRATEGY: http://www.cleveralgorithms.com/nature-inspired/evolution/evolution_strategies.html
size_t Population_Kiter::evolveSafeDist(const GameState & state, PlayerPtr & p1, PlayerPtr & p2) {
	Chromosome bestGene;

	// initialize population of Kiters to having random safeDist values
	// and evaluate the baseline population 
	initialize(state, p1, p2);
	//printDist();

	bestGene = _genePool[0];
	// main evolution loop
	for (size_t i = 0; i < _numGen; ++i) {
		//std::cout << "Generation " << i << " with genePool of sz " << genePool.size() << "\n";
		// remove lambda worst
        std::sort(_genePool.begin(), _genePool.end(), KiterComparator(false));
        //std::cout << "\n Starting gen " << i << " \n";
        //printDist();
		for (size_t i = 0; i < _lambda; ++i) {
			//std::cout << "Worse lambda safeDist: " << _genePool.top().first << "\n";
			_genePool.pop_back();
		}

		// re-mutate mu best
		for (size_t i = 0; i < _mu; ++i) {
			Chromosome c = _genePool[i];
			Chromosome mutated = mutate(c, state, p1, p2);
            _genePool.push_back(mutated);
		}
	}

	//std::cout << "===============\n";
	//for (size_t i = 0; i < genePool.size(); ++i) {
	//	std::cout << "Top lambda safeDist: " << genePool.top().first->getSafeDist() << " with score " << genePool.top().second << "\n";
	//	genePool.pop();
	//}

	// return best gen
	//Chromosome bestChromosome = genePool.top();
	//std::cout << "Best safeDist: " << bestDist << " - Best eval score: " << bestGene.second << "\n";
    std::sort(_genePool.begin(), _genePool.end(), KiterComparator(false));
    bestGene = _genePool[0];

    return bestGene.first;
}

