#include <Engine/GameBoard.h>

namespace SP
{
GameBoard::GameBoard(int width, int height) :	width(10),
												height(10)
{
	this->board.resize(this->width * this->height, (uint8_t) Teams::NO_TEAM);
	std::cout << "Data created !" << std::endl;
}

const std::vector<uint8_t>& GameBoard::GetBoard()
{
	return this->board;
}

bool GameBoard::isEmpty(int x, int y)
{
	if (x > this->board.size() || y > this->board.size()) return false;
	else return GetPawn(x, y).value == 0;
}

int GameBoard::GetRemainingPawn(Teams team)
{
	int remainingPawn = 0;
	for (auto& pawn : this->board)
		if (pawn == (uint8_t) team) remainingPawn++;
	return remainingPawn;
}

void GameBoard::SetPawn(Pawn pawn)
{
	int coord = GetIndex(pawn.x, pawn.y);
	this->board.at(coord) = pawn.value;
}

Pawn GameBoard::GetPawn(int x, int y)
{
	int coord = GetIndex(x, y);
	return {
		static_cast<uint>(x),
		static_cast<uint>(y),
		this->board.at(coord)
	};
}

void GameBoard::PopulateBoard(int teamPawnNb)
{
	if(teamPawnNb > (this->width * this->height) / 2) {
		std::cout << "Too many pawns for the board size !" << std::endl;
		return;
	}

	int pawnA = 0, pawnB = 0;
	while (pawnA < teamPawnNb || pawnB < teamPawnNb) {
		int coord = GetRandom(0, this->width * this->height);
		if (this->board.at(coord) == static_cast<uint8_t>(Teams::NO_TEAM)) {
			if (pawnA < teamPawnNb) {
				this->board.at(coord) = static_cast<uint8_t>(Teams::TEAM_ONE);
				pawnA++;
			}
			else {
				this->board.at(coord) = static_cast<uint8_t>(Teams::TEAM_TWO);
				pawnB++;
			}
		}
	}
}

// TODO Best way to counter the infinite game
bool GameBoard::IsPawnDied()
{
	int remainingPawn = GetRemainingPawn(Teams::NO_TEAM);
	bool isPawnDied = !(this->pawnNumber == remainingPawn);
	this->pawnNumber = remainingPawn;
	return isPawnDied;
}

bool GameBoard::CalculateTie()
{
	if (!IsPawnDied()) tieMove++;
	else tieMove = 0;
	if (this->tieMove >= 100) this->ended = true;
	return this->ended;
}

bool GameBoard::CalculateWon()
{
	this->ended = (GetRemainingPawn(Teams::TEAM_ONE) == 0 || GetRemainingPawn(Teams::TEAM_TWO) == 0);
	return this->ended;
}

char GameBoard::GetPluginChar(Teams team)
{
	switch (team)
	{
	case Teams::TEAM_ONE:
		return 'X';
	case Teams::TEAM_TWO:
		return 'O';
	default:
		return ' ';
		break;
	}
}

void GameBoard::ShowBoard()
{
	std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
	int x = 1;
	for (auto& pawn : this->board) {
		std::cout << "  | " << GetPluginChar(static_cast<Teams>(pawn)) << " | ";

		if (x % this->width == 0) {
			std::cout << std::endl;
			std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
			x = 0;
		}
		x++;
	}
}

std::string GameBoard::GetStringMove(MoveType move)
{
	switch (move)
	{
	case MoveType::UP:
		return "UP";
		break;
	case MoveType::DOWN:
		return "DOWN";
		break;
	case MoveType::RIGHT:
		return "RIGHT";
		break;
	case MoveType::LEFT:
		return "LEFT";
		break;
	case MoveType::LEFT_TOP_CORNER:
		return "LEFT_TOP_CORNER";
		break;
	case MoveType::LEFT_DOWN_CORNER:
		return "LEFT_DOWN_CORNER";
		break;
	case MoveType::RIGHT_TOP_CORNER:
		return "RIGHT_TOP_CORNER";
		break;
	case MoveType::RIGHT_DOWN_CORNER:
		return "RIGHT_DOWN_CORNER";
		break;
	default:
		return "NONE";
		break;
	}
}

} // namespace SP