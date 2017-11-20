#pragma once

#include "Common.h"
#include "GameState.h"

namespace SparCraft
{
	class Population_Kiter
	{
	private:
		std::vector<size_t> safeDistancesUpper;
		std::vector<unsigned long long> safeDistancesLower;
	public:
		Population_Kiter(const MoveArray & moves);
		
		StateEvalScore eval(const IDType & player, const GameState& state, const MoveArray & moves);
		void applyMoves(GameState& state, const MoveArray & moves, const IDType& playerID);
	};
}