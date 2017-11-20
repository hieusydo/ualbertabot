#include "Player_KiterDPSEvo.h"
#include "Population_Kiter.h"
#include "iostream"

using namespace SparCraft;

Player_KiterDPSEvo::Player_KiterDPSEvo (const IDType & playerID) 
{
	_playerID = playerID;
}

void Player_KiterDPSEvo::getMoves(GameState & state, const MoveArray & moves, std::vector<Action> & moveVec)
{
	moveVec.clear();

	// initialize population of safeDistances
	Population_Kiter p = Population_Kiter(moves);

	// while within time limit and number of Epoc, keep evolving and mutating

	// get best safeDistances

	IDType u = 0; // from moves.numUnits()
	size_t bestMoveIndex = 0; // from moves.numMoves(u)
	moveVec.push_back(moves.getMove(u, bestMoveIndex));

	//std::cout << "In getMoves\n";
	//moveVec.clear();
	//for (IDType u = 0; u < moves.numUnits(); ++u)
	//{
	//	bool foundAction = false;
	//	IDType actionMoveIndex = 0;
	//	IDType furthestMoveIndex = 0;
	//	IDType closestMoveIndex	= 0;
	//	double actionHighestDPS	= 0;
	//	
	//	size_t furthestMoveDist = 0;
	//	unsigned long long closestMoveDist = std::numeric_limits<unsigned long long>::max();

	//	const Unit & ourUnit = state.getUnit(_playerID, u);
	//	const Unit & closestUnit = ourUnit.canHeal() ? state.getClosestOurUnit(_playerID, u) : state.getClosestEnemyUnit(_playerID, u);

	//	for (IDType m = 0; m < moves.numMoves(u); ++m)
	//	{
	//		const Action move = moves.getMove(u, m);
	//			
	//		if (move.type() == ActionTypes::ATTACK)
	//		{
	//			const Unit & target	= state.getUnit(state.getEnemy(move.player()), move.index());
	//			double dpsHPValue = target.dpf() / target.currentHP();

	//			if (dpsHPValue > actionHighestDPS)
	//			{
	//				actionHighestDPS = dpsHPValue;
	//				actionMoveIndex = m;
	//				foundAction = true;
	//			}
	//		}
	//		else if (move.type() == ActionTypes::HEAL)
	//		{
	//			const Unit & target = state.getUnit(move.player(), move.index());
	//			double dpsHPValue = target.dpf() / target.currentHP();

	//			if (dpsHPValue > actionHighestDPS)
	//			{
	//				actionHighestDPS = dpsHPValue;
	//				actionMoveIndex = m;
	//				foundAction = true;
	//			}
	//		}
	//		else if (move.type() == ActionTypes::MOVE)
	//		{
	//			Position ourDest = Position(ourUnit.x() + Constants::Move_Dir[move.index()][0], ourUnit.y() + Constants::Move_Dir[move.index()][1]);
	//			size_t dist = closestUnit.getDistanceSqToPosition(ourDest, state.getTime());

	//			if (dist > furthestMoveDist)
	//			{
	//				furthestMoveDist = dist;
	//				furthestMoveIndex = m;
	//			}

	//			if (dist < closestMoveDist)
	//			{
	//				closestMoveDist = dist;
	//				closestMoveIndex = m;
	//			}
	//		}
	//	}

	//	// the move we will be returning
	//	size_t bestMoveIndex = 0;

	//	// if we have an attack move we will use that one
	//	if (foundAction)
	//	{
	//		bestMoveIndex = actionMoveIndex;
	//	}
	//	// otherwise use the closest move to the opponent
	//	else
	//	{
	//		// if we are in attack range of the unit, back up
	//		if (ourUnit.canAttackTarget(closestUnit, state.getTime()))
	//		{
	//			bestMoveIndex = furthestMoveIndex;
	//		}
	//		// otherwise get back into the fight
	//		else
	//		{
	//			bestMoveIndex = closestMoveIndex;
	//		}
	//	}
	//	
	//	moveVec.push_back(moves.getMove(u, bestMoveIndex));
	//}
}
