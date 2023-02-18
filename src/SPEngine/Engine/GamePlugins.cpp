#include "GamePlugins.hpp"

namespace SP
{

GamePlugins::GamePlugins()
{
}

void GamePlugins::InitPlugins()
{
	
}

const PluginInfo& GamePlugins::GetWaitingPlayer()
{
	int lastPlayerIndex = activePlayerIndex - 1;
	if (lastPlayerIndex < 0)
		lastPlayerIndex = plugins.size() - 1;
	
	return plugins.at(lastPlayerIndex);
}

const PluginInfo& GamePlugins::GetPluginByTeam(Teams team)
{
	for (auto& plugin : plugins) {
		if (plugin.team == team) {
			return plugin;
		}
	}
	return plugins.front();
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

void GamePlugins::RegisterPlugin(std::string& name, Teams team, unsigned int pawnID)
{
	std::cout << "Making " << name << " Plugin !" << std::endl;
	PluginInfo pluginOne = {
		.name = name,
		.team = team,
		.pawnID = pawnID,
		.pawnRemaining = 0,
		.pluginScript = pybind11::module_::import(name.c_str()),
		.plugin = PluginLib{},
	};
	plugins.push_back(pluginOne);
	
}

} // Namespace SP