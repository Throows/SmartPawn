#pragma once
#include <iostream>
#include <vector>

#include <Engine/GamePlugins.hpp>

struct Pawn
{
	uint x;
	uint y;
	uint value;
};

enum class MoveType : int
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

class GameBoard
{
public:
	GameBoard(int width, int height);
	virtual ~GameBoard() = default;
	const std::vector<uint8_t>& GetBoard();
	void ShowBoard();
	bool isEmpty(int x, int y);
	int GetRemainingPawn(Teams team);
	void SetPawn(Pawn Pawn);
 	Pawn GetPawn(int x, int y);
	void PopulateBoard(int teamPawnNb);
	bool IsPawnDied();
	bool IsGameEnded() { return ended; };
	bool CalculateTie();
	bool CalculateWon();
	void SetEnded(bool state) { this->ended = state; };
	std::string GetStringMove(MoveType move);
	
private:
	std::vector<uint8_t> board;
	bool ended = false;
	int tieMove = 0;
	int pawnNumber = 0;
	const int width;
	const int height;

	char GetPluginChar(Teams team);
	int GetIndex(int x, int y) { return x + (y * this->width); };
	int GetRandom(int min, int max) { return rand() % max + min; };
};

} // Namespace SP