#pragma once

#include "Common.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <memory>
#include <queue>

namespace SparCraft
{
	typedef std::pair<size_t, int> Chromosome;

	class KiterComparator {
	public:
		bool operator() (Chromosome lhs, Chromosome rhs) const;
	};

	class Population_Kiter
	{
	private:
		size_t _popSize;
		size_t _numGen;
		size_t _mu; 
		size_t _lambda;

		std::priority_queue<Chromosome, std::vector<Chromosome>, KiterComparator> _genePool;

	protected:
		// initialize method for population of many KiterDPSEvo
		void initialize(const GameState& state, PlayerPtr & p1, PlayerPtr & p2);

		// mutate method
		void mutate(Chromosome& c, const GameState & state);

		// evaluation method
		int Population_Kiter::eval(Player_KiterDPSEvo* kiter, const GameState & state, PlayerPtr & p1, PlayerPtr & p2);

		void printDist();
	public:
		Population_Kiter(size_t popSize, size_t numGen);
		size_t evolveSafeDist(const GameState & state, PlayerPtr & p1, PlayerPtr & p2);
	};

}