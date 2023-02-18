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