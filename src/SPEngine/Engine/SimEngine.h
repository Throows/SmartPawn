#pragma once

#include <windows.h>
#include <libloaderapi.h>
#include <Engine/SPData.h>
#include "Core.h"

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

		float GetPercentageEnded();

		void ShowBoard();

		void CalculateEnded();
		bool isEnded() { return this->ended; };

	private:
		Plugin pluginOne;
		Plugin pluginTwo;

		std::shared_ptr<SPData> data;

		bool ended = false;

		void PlaceRandomPawn();
		int GetRandom(int min, int max);
		char GetPluginChar(int teamIdentifier);
	};
};