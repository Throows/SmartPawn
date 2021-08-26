#include <iostream>
#include <Engine/SPData.h>

namespace SP
{

	SPData::SPData()
	{
		std::cout << "Data created !\n";
	}

	SPData::~SPData()
	{
	}

	void SPData::SetAction(PawnCoordinates move, MOVES moveType, int pawnIdentifier)
	{
		this->board.at(move.x).at(move.y) = 0;
		PawnCoordinates newCoords = GetCoordinatesByMove(move, moveType);
		this->board.at(newCoords.x).at(newCoords.y) = pawnIdentifier;
	}

	PawnCoordinates SPData::GetFirstPawn(unsigned int pawnType)
	{
		PawnCoordinates pawnCoordinates;
		pawnCoordinates.x = 0;
		pawnCoordinates.y = 0;

		for (auto& row : this->board)
		{
			pawnCoordinates.y = 0;
			for (auto& col : row)
			{
				if (col == pawnType) return pawnCoordinates;
				pawnCoordinates.y++;
			}
			pawnCoordinates.x++;
		}
		return pawnCoordinates;
	}

	std::vector<std::vector<int>>& SPData::GetBoard()
	{
		return this->board;
	}

	bool SPData::isEmpty(int x, int y)
	{
		if (x > this->board.size() || y > this->board.size()) return false;
		else return this->board.at(x).at(y) == 0;
	}

	int SPData::GetRemainingPawn(int identififer)
	{
		int remainingPawn = 0;
		for (auto& row : this->board)
			for (auto& col : row) if (col == identififer) remainingPawn++;
			
		return remainingPawn;
	}

	PawnCoordinates SPData::GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType)
	{
		PawnCoordinates newCoords;
		newCoords.x = coord.x;
		newCoords.y = coord.y;
		if (moveType == MOVES::UP || moveType == MOVES::LEFT_TOP_CORNER || moveType == MOVES::RIGHT_TOP_CORNER) newCoords.x = (coord.x + 1) % 10;
		if (moveType == MOVES::DOWN || moveType == MOVES::LEFT_DOWN_CORNER || moveType == MOVES::RIGHT_DOWN_CORNER) newCoords.x = (coord.x - 1) % 10;

		if (moveType == MOVES::RIGHT || moveType == MOVES::RIGHT_DOWN_CORNER || moveType == MOVES::RIGHT_TOP_CORNER) newCoords.y = (coord.y - 1) % 10;
		if (moveType == MOVES::LEFT || moveType == MOVES::LEFT_DOWN_CORNER || moveType == MOVES::LEFT_TOP_CORNER) newCoords.y = (coord.y + 1) % 10;
		return newCoords;
	}

}