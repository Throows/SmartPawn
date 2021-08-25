#include <windows.h>
#include <libloaderapi.h>
#include <iostream>

#include <Engine/SimEngine.h>

namespace SP
{
    SimEngine::SimEngine()
    {
		pluginOne.handle = LoadLibrary("SPIntelligence.dll");
		if (pluginOne.handle == NULL)
		{
			throw std::runtime_error("Could not load plugin !");
		}

    }

	SimEngine::~SimEngine()
	{
		FreeLibrary(pluginOne.handle);
	}

	void SimEngine::InitEngine()
	{
		std::cout << "Making Blue Plugin !" << std::endl;

		PLUGIN initBluePlugin;
		initBluePlugin = (PLUGIN)GetProcAddress(pluginOne.handle, "InitPlugin");

		if (!initBluePlugin) std::cout << "error : " << GetLastError() << std::endl;
		else initBluePlugin();

		pluginOne.name = "Blue Plugin";
		pluginOne.isPlayed = false;
		pluginOne.RunInstance = (PLUGIN)GetProcAddress(pluginOne.handle, "RunIntelligenceTurn");




		std::cout << "SimEngine initialized !\n";
	}

	void SimEngine::PlaceRandomPawn()
	{

	}

}

SP_API std::shared_ptr<SP::SimEngine> CreateEngine()
{
	return std::make_shared<SP::SimEngine>();

}