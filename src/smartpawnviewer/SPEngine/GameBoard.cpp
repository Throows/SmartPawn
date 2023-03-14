#include <SPEngine/GameBoard.hpp>
#include "Logger.hpp"

namespace SP
{

GameBoard::GameBoard(int width, int height) : 	width(width),
												height(width)
{
	this->board.resize(this->width * this->height, (uint8_t)Teams::NO_TEAM);
	SP_ENGINE_TRACE("GameBoard created with size {0}x{1}", this->width, this->height);
}

const std::vector<uint8_t>& GameBoard::GetBoard()
{
	return this->board;
}

bool GameBoard::IsEmpty(int x, int y)
{
	if (x > this->board.size() || y > this->board.size()) return false;
	else return GetPawn(x, y) == 0;
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

uint GameBoard::GetPawn(int x, int y)
{
	int coord = GetIndex(x, y);
	return this->board.at(coord);
}

void GameBoard::GetPawnByMove(Pawn& pawn, MoveType moveType)
{
	if(moveType == MoveType::UP ||
		moveType == MoveType::LEFT_TOP_CORNER ||
	 	moveType == MoveType::RIGHT_TOP_CORNER) {
		pawn.y--;
	}

	if(moveType == MoveType::DOWN ||
		moveType == MoveType::LEFT_DOWN_CORNER ||
	 	moveType == MoveType::RIGHT_DOWN_CORNER) {
		pawn.y++;
	}

	if (moveType == MoveType::LEFT ||
		moveType == MoveType::LEFT_DOWN_CORNER ||
		moveType == MoveType::LEFT_TOP_CORNER) {
		pawn.x--;
	}

	if (moveType == MoveType::RIGHT ||
		moveType == MoveType::RIGHT_DOWN_CORNER ||
		moveType == MoveType::RIGHT_TOP_CORNER) {
		pawn.x++;
	}
	if (pawn.x == UINT_MAX) pawn.x = this->width - 1;
	if (pawn.x >= this->width) pawn.x = 0;
	if (pawn.y == UINT_MAX) pawn.y = this->height - 1;
	if (pawn.y >= this->height) pawn.y = 0;
}

std::vector<Pawn> GameBoard::GetPawns()
{
    std::vector<Pawn> pawns{};
	// get the coordinte of the pawns from the board
	int id = 0, x, y;
	for(const auto& p : this->board) {
		if (p != static_cast<uint8_t>(Teams::NO_TEAM)) {
			x = id % this->width;
			y = id / this->width;
			pawns.push_back({static_cast<uint>(x), static_cast<uint>(y), p});
		}
		id++;
	}
	return pawns;
}

void GameBoard::PopulateBoard(const int& teamPawnNb)
{
	if(teamPawnNb > (this->width * this->height) / 2) {
		SP_ENGINE_ERROR("Too many pawns for the board size !");
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

// TODO Find better way to counter the infinite game
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

bool GameBoard::IsValidMove(Pawn &oldPawn, Pawn &newPawn)
{
	uint actualOldPawn = GameBoard::GetPawn(oldPawn.x, oldPawn.y);
	uint actualNewPawn = GameBoard::GetPawn(newPawn.x, newPawn.y);

	if (actualOldPawn == 0) {
		SP_ENGINE_WARN("You can't play an empty case !");
		return false;
	}
	if (actualOldPawn != newPawn.value) {
		SP_ENGINE_WARN("You can't play an ennemy pawn !");
		return false;
	}
	if (actualNewPawn != 0 && actualNewPawn == newPawn.value) {
		SP_ENGINE_WARN("You can't play your own pawn !");
		return false;
	}
	return true;
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
	bool first = true;
	int x = 0;
	for (const auto& pawn : this->board) {
		if ((x % this->width) == 0) {
			std::cout << (first ? "" : " |") << std::endl;
			std::cout << "-+---+---+---+---+---+---+---+---+---+---+-" << std::endl;
			x = 0;
			first = false;
		}
		std::cout << " | " << GetPluginChar(static_cast<Teams>(pawn));
		x++;
	}
	std::cout << " |" << std::endl;
	std::cout << "-+---+---+---+---+---+---+---+---+---+---+-" << std::endl;
}

} // namespace SP