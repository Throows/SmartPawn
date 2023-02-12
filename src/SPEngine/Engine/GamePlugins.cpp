#include "GamePlugins.h"

namespace SP
{

GamePlugins::GamePlugins()
{
}

GamePlugins::~GamePlugins()
{
}

void GamePlugins::RegisterPlugins()
{
	//TODO : Load plugins from available files
	std::string name = "BluePlugin";
	std::cout << "Making " << name << " Plugin !" << std::endl;
	PluginInfo pluginOne = {
		name,
		Teams::TEAM_ONE,
		1,
		0,
		pybind11::module_::import(name.c_str())
	};
	plugins.push_back(pluginOne);

	name = "RedPlugin";
	std::cout << "Making "<< name << " Plugin !" << std::endl;
	PluginInfo pluginTwo = {
		name,
		Teams::TEAM_TWO,
		2,
		0,
		pybind11::module_::import(name.c_str())
	};
	plugins.push_back(pluginTwo);
}

void GamePlugins::InitPlugins()
{
	// TODO mv plugininfo creation to here
}

const PluginInfo& GamePlugins::GetWaitingPlayer()
{
	int lastPlayerIndex = activePlayerIndex - 1;
	if (lastPlayerIndex < 0)
		lastPlayerIndex = plugins.size() - 1;
}

const PluginInfo& GamePlugins::GetPluginByTeam(Teams team)
{
	for (auto plugin : plugins) {
		if (plugin.team == team) {
			return plugin;
		}
	}
}

std::map<std::string, int> GamePlugins::GetTeamsName()
{
	std::map<std::string, int> map;
	for (auto plugin : plugins) {
		map.emplace(plugin.name, plugin.pawnID);
	}
	return map;
}

void GamePlugins::SwapTurn()
{
	activePlayerIndex++;
	if (activePlayerIndex >= plugins.size())
		activePlayerIndex = 0;
}

} // Namespace SP