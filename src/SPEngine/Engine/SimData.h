#pragma once

#include <iostream>
#include <vector>
#include "Core.h"

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

	class SP_API SimData
	{
	public:
		SimData();
		virtual ~SimData() = default;

		std::vector<std::vector<int>>& GetBoard();
		char GetPluginChar(int identifier);
		void ShowBoard();

		bool isEmpty(int x, int y);
		int GetRemainingPawn(int identififer);
		void SetPawn(int x, int y, int identifier);
		void PlaceRandomPawn(int pawnNumber, int identifierOne, int identifierTwo);
		int GetRandom(int min, int max);
		bool IsPawnDied();

		bool IsGameEnded() { return ended; };
		bool CalculateTie();
		bool CalculateWon(int identifierOne, int identifierTwo);
		void SetEnded(bool state) { this->ended = state; };


	private:
		std::vector<std::vector<int>> board;  // Vector of column
		bool ended = false;
		int tieMove = 0;
		int pawnNumber = 0;

	};
};