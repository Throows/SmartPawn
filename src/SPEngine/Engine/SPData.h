#pragma once

#include "Core.h"
#include <iostream>
#include <vector>

struct PawnCoordinates
{
	unsigned int x;
	unsigned int y;
};

enum class MOVES : int
{
	UP = 0,
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
		PawnCoordinates GetRandomPawn(unsigned int pawnType);
		std::vector<std::vector<int>>& GetBoard();
		bool isEmpty(int x, int y);
		int GetRemainingPawn(int identififer);
		void SetPawn(int x, int y, int pawn);
		std::string GetStringMove(MOVES move);

	private:
		std::vector<std::vector<int>> board;  // Vector of column
		int pawnType;

		PawnCoordinates GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType);
	};
};