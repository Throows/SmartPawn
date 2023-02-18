#pragma once
#include <Engine/PluginLib.hpp>

#include <iostream>
#include <vector>
#include <map>

#include <pybind11/pybind11.h>

namespace SP
{

enum class Teams
{
	NO_TEAM = 0,
	TEAM_ONE,
	TEAM_TWO
};

struct PluginInfo
{
	std::string name;
	Teams team;
	unsigned int pawnID;
	unsigned int pawnRemaining;
	pybind11::module_ pluginScript;
	PluginLib plugin;
};

class GamePlugins 
{
public:
	GamePlugins();
	virtual ~GamePlugins() = default;
	void InitPlugins();
	const PluginInfo& GetActivePlayer() { return plugins[activePlayerIndex]; };
	const PluginInfo& GetWaitingPlayer();
	const PluginInfo& GetPluginByTeam(Teams team);
	std::map<std::string, int> GetTeamsName();
	void SwapTurn();

private:
	std::vector<PluginInfo> plugins;
	int activePlayerIndex;

	void RegisterPlugin(std::string& name, Teams team, unsigned int pawnID);
};

} // Namespace SP