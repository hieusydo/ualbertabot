#pragma once

#include "Common.h"
#include "GameState.h"
#include "Player.h"
#include "Game.h"
#include "Action.h"
#include <memory>

namespace SparCraft
{
	class Population_Kiter
	{
	private:
		size_t _popSize;
		size_t _numGen;
		std::vector<IDType> _populations;

	protected:
		// initialize method for population of many KiterDPSEvo
		void initialize();

		// mutate method
		void mutate();

		// evaluation method
		int eval();

	public:
		Population_Kiter(size_t popSize, size_t numGen);
		size_t evolveSafeDist();
	};

}