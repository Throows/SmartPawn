#pragma once
#include <iostream>
#include <vector>

#include "GamePlugins.hpp"

namespace SP
{

class GameBoard
{
public:
	GameBoard(unsigned int width, unsigned int height, unsigned int tieMoveMax);
	virtual ~GameBoard() = default;
	const std::vector<uint8_t>& GetBoard();
	void ShowBoard();
	bool IsEmpty(int x, int y);
	int GetRemainingPawn(Teams team);
	void SetPawn(Pawn Pawn);
 	uint GetPawn(int x, int y);
	void GetPawnByMove(Pawn& pawn, MoveType moveType);
	std::vector<Pawn> GetPawns();
	void PopulateBoard(const unsigned int& teamPawnNb);
	bool IsPawnDied();
	bool IsGameEnded() { return ended; };
	bool CalculateTie();
	bool CalculateWon();
	void SetEnded(bool state) { this->ended = state; }

	const unsigned int& GetBoardWidth() { return this->width; }
	const unsigned int& GetBoardHeight() { return this->height; }

	bool IsValidMove(Pawn& oldPawn, Pawn& newPawn);
	
private:
	std::vector<uint8_t> board;
	bool ended = false;
	unsigned int tieMove = 0;
	int pawnNumber = 0;
	const unsigned int width;
	const unsigned int height;
	const unsigned int tieMoveMax;

	char GetPluginChar(Teams team);
	int GetIndex(int x, int y) { return x + (y * this->width); };
	int GetRandom(int min, int max) { return rand() % max + min; };
};

} // Namespace SP