#pragma once
#include <string>

enum class MoveType : int
{
	NONE = -1,
	UP = 0,
	DOWN,
	RIGHT,
	LEFT,
	LEFT_TOP_CORNER,
	LEFT_DOWN_CORNER,
	RIGHT_TOP_CORNER,
	RIGHT_DOWN_CORNER
};

class PluginLib
{
public:
	PluginLib(std::string name);
	virtual ~PluginLib() {};
	std::string GetName() { return this->name; }
	int GetRandomPawn();
	int GetFirstPawn();
	bool SetAction(int x, int y, int moveType);
	void ValidateMove(bool played = true) { this->hasPlayed = played; }
	void Reset();
	int GetPawnMove() { return this->moveType; }
	int GetPawnX() { return this->pawnX; }
	int GetPawnY() { return this->pawnY; }

private:
	bool hasPlayed = false;
	std::string name;
	int pawnX = 1;
	int pawnY = 2;
	int moveType = -1;
};