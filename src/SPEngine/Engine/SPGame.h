#pragma once
#include <Engine/GameBoard.h>
#include <Engine/GameRecorder.h>

namespace SP
{

class SPGame 
{
public:
	SPGame();
	virtual ~SPGame() = default;

	void InitGame();
	void PlayNextTurn();
	float GetPercentageEnded();
	void CalculateEnded();
	void AddActionRecorder(Pawn coords, Pawn newCoords);

	std::shared_ptr<GameBoard> GetData() { return this->board; };
	std::shared_ptr<GamePlugins> GetPLManager() { return this->plugins; };

private:
	std::shared_ptr<GamePlugins> plugins;
	std::shared_ptr<GameBoard> board;
	std::shared_ptr<GameRecorder> recorder;
	const unsigned int initalPawnNumber = 5;
};

} // Namespace SP