#pragma once
#include <SPEngine/GameBoard.hpp>
#include <SPEngine/GameRecorder.hpp>

/*#ifdef SP_PLATFORM_WIN
#	ifdef DDL_EXPORT
#		define SP_API __declspec(dllexport)
#	else
#		define SP_API __declspec(dllimport)
#	endif	
#elif SP_PLATFORM_DARWIN
#	define SP_API __attribute__((visibility("default")))
#endif*/

namespace SP
{
class SPGame 
{
public:
	SPGame(unsigned int pawnNb, unsigned int boardWidth, unsigned int boardHeight, unsigned int tieMoveMax);
	virtual ~SPGame() = default;

	void InitGame();
	void PlayNextTurn();
	float GetPercentageEnded();
	void CalculateEnded();
	void AddActionRecorder(Pawn coords, Pawn newCoords);

	GameBoard* GetData() const { return this->board.get(); }
	GamePlugins* GetPLManager() const { return this->plugins.get(); }

private:
	std::unique_ptr<GamePlugins> plugins;
	std::unique_ptr<GameBoard> board;
	std::unique_ptr<GameRecorder> recorder;
	const uint initalPawnNumber;
};

} // Namespace SP