#pragma once

#include "Common.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <memory>

namespace SparCraft
{
	typedef std::pair<Player_KiterDPSEvo*, int> Chromosome;

	class KiterComparator {
	public:
		bool operator() (std::pair<Player_KiterDPSEvo*, int> lhs, std::pair<Player_KiterDPSEvo*, int> rhs) const;
	};

	class Population_Kiter
	{
	private:
		size_t _popSize;
		size_t _numGen;
		size_t _mu; 
		size_t _lambda;

		// is using heap too memory intensive?
		std::vector<Player_KiterDPSEvo*> _populations;

	protected:
		// initialize method for population of many KiterDPSEvo
		void initialize();

		// mutate method
		void mutate(Chromosome& c, const GameState & state);

		// evaluation method
		int Population_Kiter::eval(Player_KiterDPSEvo* kiter, const GameState & state);

	public:
		Population_Kiter(size_t popSize, size_t numGen);
		size_t evolveSafeDist(const GameState & state);
		~Population_Kiter();
	};

}