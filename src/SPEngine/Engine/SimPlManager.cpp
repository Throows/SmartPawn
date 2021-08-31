#include "SimPlManager.h"

namespace SP
{
	SimPLManager::SimPLManager()
	{
		this->activePlayer = std::make_shared<Plugin>();
		this->inactivePlayer = std::make_shared<Plugin>();
	}

	SimPLManager::~SimPLManager()
	{
		FreeLibrary(activePlayer->handle);
		FreeLibrary(inactivePlayer->handle);
	}


	void SimPLManager::RegisterPlugins()
	{

		activePlayer->handle = LoadLibrary("SPIntelligenceBlue.dll");
		inactivePlayer->handle = LoadLibrary("SPIntelligence.dll");
		if (activePlayer->handle == NULL || inactivePlayer->handle == NULL)
		{
			throw std::runtime_error("Could not load plugin file !");
		}

		std::cout << "Making Blue Plugin !" << std::endl;

		activePlayer->name = "Blue Plugin";
		activePlayer->pawnIdentifier = 1;
		activePlayer->pawnRemaining = 0;
		PLUGIN activePlayerRunInstance = (PLUGIN)GetProcAddress(activePlayer->handle, "RunIntelligenceTurn");
		if (!activePlayerRunInstance) std::cout << "Error : " << GetLastError() << std::endl;
		activePlayer->RunInstance = activePlayerRunInstance;

		std::cout << "Making Red Plugin !" << std::endl;

		inactivePlayer->name = "Red Plugin";
		inactivePlayer->pawnIdentifier = 2;
		inactivePlayer->pawnRemaining = 0;
		PLUGIN inactivePlayerRunInstance = (PLUGIN)GetProcAddress(inactivePlayer->handle, "RunIntelligenceTurn");
		if (!inactivePlayerRunInstance) std::cout << "Error : " << GetLastError() << std::endl;
		inactivePlayer->RunInstance = inactivePlayerRunInstance;

	}

	void SimPLManager::InitPlugins(std::shared_ptr<SPPlugin> api)
	{
		INITPLUGIN initBluePlugin;
		initBluePlugin = (INITPLUGIN)GetProcAddress(activePlayer->handle, "InitPlugin");

		if (!initBluePlugin) std::cout << "error : " << GetLastError() << std::endl;
		else initBluePlugin(api);

		INITPLUGIN initRedPlugin;
		initRedPlugin = (INITPLUGIN)GetProcAddress(inactivePlayer->handle, "InitPlugin");

		if (!initRedPlugin) std::cout << "error : " << GetLastError() << std::endl;
		else initRedPlugin(api);
	}

	Plugin SimPLManager::GetTeam(PawnTeam team)
	{
		if (team == PawnTeam::MY_TEAM) return this->GetActivePlayer();
		else return this->GetWaitingPlayer();
	}

	void SimPLManager::SwapTurn()
	{
		activePlayer.swap(inactivePlayer);
	}

	
}