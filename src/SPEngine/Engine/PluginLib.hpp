#pragma once
#include <string>
#include <vector>

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

struct Coordinates
{
	int x;
	int y;
};

class PluginLib
{
public:
	PluginLib(std::string name);
	virtual ~PluginLib() = default;
	std::string GetName() { return this->name; }
	Coordinates GetMyRandomPawn();
	Coordinates GetMyFirstPawn();
	Coordinates GetEnnemyRandomPawn();
	Coordinates GetEnnemyFirstPawn();
	bool SetAction(Coordinates pawn, MoveType moveType);
	void Reset();
	MoveType GetPawnMove() { return this->moveType; }
	Coordinates GetPawnCoordinates() { return this->pawnToMove; }

	std::vector<Coordinates> myPawns;
	std::vector<Coordinates> ennemyPawns;

private:
	std::string name;
	Coordinates pawnToMove;
	MoveType moveType = MoveType::NONE;
};