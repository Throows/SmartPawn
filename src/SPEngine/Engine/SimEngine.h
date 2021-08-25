#pragma once
#include "Core.h"
#include <Engine/SPPlugin.h>

typedef SP::SPPlugin (*PLUGIN)();

struct Plugin
{
	HMODULE handle;
	std::string name;
	PLUGIN RunInstance;
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

	private:
		Plugin pluginOne;
		Plugin PluginTwo;

		void PlaceRandomPawn();
	};
};