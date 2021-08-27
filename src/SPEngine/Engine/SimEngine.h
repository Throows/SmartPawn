#pragma once

#include <windows.h>
#include <libloaderapi.h>
#include "Core.h"
#include <Engine/SPData.h>
#include <Engine/SimRecorder.h>

namespace SP
{
	class SPData;
}
enum class PawnTeam;
struct PawnCoordinates;

typedef void (*INITPLUGIN)(std::shared_ptr<SP::SPData> simData);
typedef void (*PLUGIN)();

struct Plugin
{
	std::string name;
	unsigned int pawnIdentifier;
	unsigned int pawnRemaining;
	HMODULE handle;
	PLUGIN RunInstance;
	bool isPlaying;
	bool isPlayed;
};

namespace SP
{
	class SP_API SimEngine
	{
	public:
		SimEngine();
		~SimEngine();

		void InitEngine();
		void PlayNextTurn();

		Plugin GetActivePlayer();
		Plugin GetWaitingPlayer();
		Plugin GetTeam(PawnTeam team);

		float GetPercentageEnded();

		void ShowBoard();

		void CalculateEnded();
		bool isEnded() { return this->ended; };

		void AddActionRecorder(PawnCoordinates coords, PawnCoordinates newCoords);

	private:
		Plugin pluginOne;
		Plugin pluginTwo;

		int equalityMove = 0;

		std::shared_ptr<SPData> data;
		std::shared_ptr<SimRecorder> recorder;

		bool ended = false;

		void PlaceRandomPawn();
		int GetRandom(int min, int max);
		char GetPluginChar(int teamIdentifier);
	};
};