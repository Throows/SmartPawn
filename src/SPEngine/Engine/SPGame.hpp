#pragma once
#include <Engine/GameBoard.hpp>
#include <Engine/GameRecorder.hpp>

#ifdef SP_PLATFORM_WIN
#define EXPORT __declspec(dllexport)
#elif SP_PLATFORM_DARWIN
#define EXPORT __attribute__((visibility("default")))
#endif

namespace SP
{
class EXPORT SPGame 
{
public:
	SPGame(uint pawnNb, uint boardWidth, uint boardHeight);
	virtual ~SPGame() = default;

	void InitGame();
	void PlayNextTurn();
	float GetPercentageEnded();
	void CalculateEnded();
	void AddActionRecorder(Pawn coords, Pawn newCoords);

	GameBoard * const GetData() { return this->board.get(); }
	GamePlugins * const GetPLManager() { return this->plugins.get(); }

private:
	std::unique_ptr<GamePlugins> plugins;
	std::unique_ptr<GameBoard> board;
	std::unique_ptr<GameRecorder> recorder;
	const uint initalPawnNumber;
};

} // Namespace SP