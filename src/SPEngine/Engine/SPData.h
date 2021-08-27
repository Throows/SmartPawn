#pragma once

#include <iostream>
#include <vector>
#include "Core.h"
#include <Engine/SimEngine.h>

namespace SP
{
	class SimEngine;
}

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

enum class PawnTeam
{
	MY_TEAM,
	ENNEMY_TEAM
};

namespace SP
{

	class SP_API SPData
	{
	public:
		SPData(std::shared_ptr<SimEngine> engine);
		~SPData();

		void SetAction(PawnCoordinates move, MOVES moveType);
		PawnCoordinates GetFirstPawn(PawnTeam team);
		PawnCoordinates GetRandomPawn(PawnTeam team);
		std::vector<std::vector<int>>& GetBoard();
		bool isEmpty(int x, int y);
		int GetRemainingPawn(int identififer);
		void SetPawn(int x, int y);
		std::string GetStringMove(MOVES move);

	private:
		std::shared_ptr<SimEngine> engine;
		std::vector<std::vector<int>> board;  // Vector of column

		PawnCoordinates GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType);
	};
};