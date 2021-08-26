#pragma once

#include "Core.h"
#include <vector>

struct PawnCoordinates
{
	unsigned int x;
	unsigned int y;
};

enum class MOVES
{
	UP,
	DOWN, 
	RIGHT,
	LEFT,
	LEFT_TOP_CORNER,
	LEFT_DOWN_CORNER,
	RIGHT_TOP_CORNER,
	RIGHT_DOWN_CORNER
};

namespace SP
{

	class SP_API SPData
	{
	public:
		SPData();
		~SPData();

		void SetAction(PawnCoordinates move, MOVES moveType, int pawnIdentifier);
		PawnCoordinates GetFirstPawn(unsigned int pawnType);
		std::vector<std::vector<int>>& GetBoard();
		bool isEmpty(int x, int y);
		int GetRemainingPawn(int identififer);

	private:
		std::vector<std::vector<int>> board;
		int pawnType;

		PawnCoordinates GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType);
	};
};