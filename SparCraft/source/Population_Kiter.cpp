#include "Population_Kiter.h"

#include "Common.h"
#include "GameState.h"
#include "Game.h"


using namespace SparCraft;

Population_Kiter::Population_Kiter(const MoveArray & moves) {
	safeDistancesUpper = std::vector<size_t>(moves.numUnits(), 0);
	safeDistancesLower = std::vector<unsigned long long>(moves.numUnits(), std::numeric_limits<unsigned long long>::max());
}

void Population_Kiter::applyMoves(GameState& state, const MoveArray & moves, const IDType& playerID) {
	std::vector<Action> moveVec; 

	for (IDType u = 0; u < moves.numUnits(); ++u)
	{
		bool foundAction = false;
		IDType actionMoveIndex = 0;
		IDType furthestMoveIndex = 0;
		IDType closestMoveIndex = 0;
		double actionHighestDPS = 0;

		// Each unit has a different distance range
		size_t furthestMoveDist = safeDistancesUpper[(size_t)u];
		unsigned long long closestMoveDist = safeDistancesLower[(size_t)u];

		const Unit & ourUnit = state.getUnit(playerID, u);
		const Unit & closestUnit = ourUnit.canHeal() ? state.getClosestOurUnit(playerID, u) : state.getClosestEnemyUnit(playerID, u);

		for (IDType m = 0; m < moves.numMoves(u); ++m)
		{
			const Action move = moves.getMove(u, m);

			if (move.type() == ActionTypes::ATTACK)
			{
				const Unit & target = state.getUnit(state.getEnemy(move.player()), move.index());
				double dpsHPValue = target.dpf() / target.currentHP();

				if (dpsHPValue > actionHighestDPS)
				{
					actionHighestDPS = dpsHPValue;
					actionMoveIndex = m;
					foundAction = true;
				}
			}
			else if (move.type() == ActionTypes::HEAL)
			{
				const Unit & target = state.getUnit(move.player(), move.index());
				double dpsHPValue = target.dpf() / target.currentHP();

				if (dpsHPValue > actionHighestDPS)
				{
					actionHighestDPS = dpsHPValue;
					actionMoveIndex = m;
					foundAction = true;
				}
			}
			else if (move.type() == ActionTypes::MOVE)
			{
				Position ourDest = Position(ourUnit.x() + Constants::Move_Dir[move.index()][0], ourUnit.y() + Constants::Move_Dir[move.index()][1]);
				size_t dist = closestUnit.getDistanceSqToPosition(ourDest, state.getTime());

				if (dist > furthestMoveDist)
				{
					furthestMoveDist = dist;
					furthestMoveIndex = m;
				}

				if (dist < closestMoveDist)
				{
					closestMoveDist = dist;
					closestMoveIndex = m;
				}
			}
		}

		// the move we will be returning
		size_t bestMoveIndex = 0;

		// if we have an attack move we will use that one
		if (foundAction)
		{
			bestMoveIndex = actionMoveIndex;
		}
		// otherwise use the closest move to the opponent
		else
		{
			// if we are in attack range of the unit, back up
			if (ourUnit.canAttackTarget(closestUnit, state.getTime()))
			{
				bestMoveIndex = furthestMoveIndex;
			}
			// otherwise get back into the fight
			else
			{
				bestMoveIndex = closestMoveIndex;
			}
		}

		moveVec.push_back(moves.getMove(u, bestMoveIndex));
	}
}

StateEvalScore Population_Kiter::eval(const IDType & player, const GameState& state, const MoveArray & moves) {
	// apply the move based on rule: enemy within safeDistance, move back; else, attack
	Game g(state, 100);

	// Framework to evaluate a mutated script? 

	// get the score of that state
	return g.getState().eval(player, SparCraft::EvaluationMethods::LTD2);
}
