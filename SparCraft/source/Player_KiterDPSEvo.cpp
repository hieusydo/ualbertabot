#include "Player_KiterDPSEvo.h"
#include "Population_Kiter.h"
#include "iostream"

using namespace SparCraft;

Player_KiterDPSEvo::Player_KiterDPSEvo (const IDType & playerID) 
{
	_playerID = playerID;
	_safeDist = 0; // default set it to 0, will set to random when initializing the population
}

//Player_KiterDPSEvo::Player_KiterDPSEvo(const IDType & playerID, size_t safeDist) {
//	_playerID = playerID;
//	_safeDist = safeDist;
//}
void Player_KiterDPSEvo::setSafeDist(size_t d) {
	_safeDist = d;
}

void Player_KiterDPSEvo::getMoves(GameState & state, const MoveArray & moves, std::vector<Action> & moveVec)
{
	moveVec.clear();

	// initialize population of safeDistances
	size_t popSize = 10;
	size_t numGen = 100;
	//Population_Kiter k = Population_Kiter(popSize, numGen);

	//size_t safeDist = k.evolveSafeDist(state);

	for (IDType u = 0; u < moves.numUnits(); ++u)
	{
		bool foundAction = false;
		IDType actionMoveIndex = 0;
		IDType furthestMoveIndex = 0;
		IDType closestMoveIndex	= 0;
		double actionHighestDPS	= 0;
		
		size_t furthestMoveDist = 0;
		unsigned long long closestMoveDist = std::numeric_limits<unsigned long long>::max();

		const Unit & ourUnit = state.getUnit(_playerID, u);
		const Unit & closestUnit = ourUnit.canHeal() ? state.getClosestOurUnit(_playerID, u) : state.getClosestEnemyUnit(_playerID, u);

		for (IDType m = 0; m < moves.numMoves(u); ++m)
		{
			const Action move = moves.getMove(u, m);
				
			if (move.type() == ActionTypes::ATTACK)
			{
				const Unit & target	= state.getUnit(state.getEnemy(move.player()), move.index());
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

			Position ourPos = Position(ourUnit.x(), ourUnit.y());
			size_t dist = closestUnit.getDistanceSqToPosition(ourPos, state.getTime());
			// change for evo
			if (dist < _safeDist){
				bestMoveIndex = furthestMoveIndex;
			}
			// otherwise get back into the fight
			else
			{
				bestMoveIndex = closestMoveIndex;
			}

			//if (ourUnit.canAttackTarget(closestUnit, state.getTime()))
			//{
			//	bestMoveIndex = furthestMoveIndex;
			//}
			//// otherwise get back into the fight
			//else
			//{
			//	bestMoveIndex = closestMoveIndex;
			//}
		}
		
		moveVec.push_back(moves.getMove(u, bestMoveIndex));
	}
}

Population_Kiter::~Population_Kiter() {
	for (Player_KiterDPSEvo* p : _populations) {
		delete p;
	}
	_populations.clear();
}