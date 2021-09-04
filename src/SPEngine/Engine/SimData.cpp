#include <Engine/SimData.h>

namespace SP
{

	SimData::SimData()
	{
		for (int columnCount = 0; columnCount < 10; columnCount++)
		{
			std::vector<int> column;
			for (int row = 0; row < 10; row++)
			{
				column.push_back(0);
			}
			this->board.push_back(column);
		}

		std::cout << "Data created !\n";
	}

	std::vector<std::vector<int>>& SimData::GetBoard()
	{
		return this->board;
	}

	bool SimData::isEmpty(int x, int y)
	{
		if (x > this->board.size() || y > this->board.size()) return false;
		else return GetPawn(x, y) == 0;
	}

	int SimData::GetRemainingPawn(int identififer)
	{
		int remainingPawn = 0;
		for (auto& row : this->board)
			for (auto& col : row) if (col == identififer) remainingPawn++;
			
		if (identififer == 0) remainingPawn = (this->board.size() * this->board.size()) - remainingPawn;
		return remainingPawn;
	}

	void SimData::SetPawn(int x, int y, int identifier)
	{
		this->board.at(y).at(x) = identifier;
	}

	int SimData::GetPawn(int x, int y)
	{
		return this->board.at(y).at(x);
	}

	void SimData::PlaceRandomPawn(int pawnNumber, int identifierOne, int identifierTwo)
	{
		int pawnA = 0, pawnB = 0;
		while (pawnA < 20 || pawnB < 20)
		{
			int x = GetRandom(0, 10);
			int y = GetRandom(0, 10);
			if (isEmpty(x, y))
			{
				if (pawnA < 20) {
					SetPawn(x, y, identifierOne);
					pawnA++;
				}
				else
				{
					SetPawn(x, y, identifierTwo);
					pawnB++;
				}
			}
		}
	}

	int SimData::GetRandom(int min, int max)
	{
		return rand() % max + min;
	}

	bool SimData::IsPawnDied()
	{
		int remainingPawn = GetRemainingPawn(0);
		bool isPawnDied = !(this->pawnNumber == remainingPawn);
		this->pawnNumber = remainingPawn;
		return isPawnDied;
	}

	bool SimData::CalculateTie()
	{
		if (!IsPawnDied()) tieMove++;
		else tieMove = 0;

		if (this->tieMove >= 100) this->ended = true;
		return this->ended;

	}

	bool SimData::CalculateWon(int identifierOne, int identifierTwo)
	{
		this->ended = (GetRemainingPawn(identifierOne) == 0) || (GetRemainingPawn(identifierTwo) == 0);
		return this->ended;
	}

	char SimData::GetPluginChar(int teamIdentifier)
	{
		switch (teamIdentifier)
		{
		case 1:
			return 'X';
		case 2:
			return 'O';
		default:
			return ' ';
			break;
		}
	}

	void SimData::ShowBoard()
	{

		std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
		for (auto& row : this->board)
		{
			std::cout << "  | ";
			for (auto& i : row) {
				std::cout << GetPluginChar(i) << " | ";
			}
			std::cout << std::endl;
			std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
		}
	}


	std::string SimData::GetStringMove(MOVES move)
	{
		switch (move)
		{
		case MOVES::UP:
			return "UP";
			break;
		case MOVES::DOWN:
			return "DOWN";
			break;
		case MOVES::RIGHT:
			return "RIGHT";
			break;
		case MOVES::LEFT:
			return "LEFT";
			break;
		case MOVES::LEFT_TOP_CORNER:
			return "LEFT_TOP_CORNER";
			break;
		case MOVES::LEFT_DOWN_CORNER:
			return "LEFT_DOWN_CORNER";
			break;
		case MOVES::RIGHT_TOP_CORNER:
			return "RIGHT_TOP_CORNER";
			break;
		case MOVES::RIGHT_DOWN_CORNER:
			return "RIGHT_DOWN_CORNER";
			break;
		default:
			return "NONE";
			break;
		}
	}
}