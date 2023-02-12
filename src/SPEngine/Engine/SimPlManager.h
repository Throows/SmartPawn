#pragma once
#include <Engine/SPPlugin.h>
#include <iostream>
#include <map>
#include <pybind11/pybind11.h>

namespace SP
{
	class SPPlugin;
}

enum class PawnTeam
{
	MY_TEAM,
	ENNEMY_TEAM
};

typedef void (*INITPLUGIN)(std::shared_ptr<SP::SPPlugin> api);
typedef void (*PLUGIN)();

struct Plugin
{
	std::string name;
	unsigned int pawnIdentifier;
	unsigned int pawnRemaining;
	pybind11::module_ pluginScript;

	bool operator==(Plugin a)
	{
		return a.name == name;
	}

	void SetRemainingPawn(int pawn)
	{
		pawnRemaining = pawn;
	}
};

namespace SP
{
	class SimPLManager 
	{
	public:
		SimPLManager();
		~SimPLManager();

		void RegisterPlugins();
		void InitPlugins(std::shared_ptr<SPPlugin> api);

		Plugin GetActivePlayer() { return *this->activePlayer; };
		Plugin GetWaitingPlayer() { return *this->inactivePlayer; };
		Plugin GetTeam(PawnTeam team);
		std::map<std::string, int> GetTeams();

		void SwapTurn();

	private:
		std::shared_ptr<Plugin> inactivePlayer;
		std::shared_ptr<Plugin> activePlayer;

	};
}