#include "GamePlugins.hpp"

#define NB_MAX_PLAYER 2
namespace SP
{

GamePlugins::GamePlugins()
{
}

void GamePlugins::InitPlugins()
{
	// Check the folder for plugins
	if (!std::filesystem::exists("Plugins") || !std::filesystem::is_directory("Plugins")) {
		std::cout << "No plugins folder found !" << std::endl;
		return;
	}

	pybind11::scoped_interpreter scope{}; // Is it a good idea to put it here ?

	for (const auto& dir : std::filesystem::directory_iterator("Plugins")) {
		if (IsPluginDir(dir)) {
			std::string name = dir.path().filename().string();
			GamePlugins::RegisterPlugin(name);
		}
	}

	for (auto& plugin : plugins) {
		LoadPlugin(plugin);
	}
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

MoveType GamePlugins::PlayRound(uint &x, uint &y)
{
	pybind11::scoped_interpreter scope{};
	PluginInfo activePlayer = GetActivePlayer();
	// Update PluginLib
	//activePlayer.plugin.SetBoard(board.GetBoard());
	PluginLib plugin = PluginLib{activePlayer.name};
	//pybind11::setattr(plugin, "board", board.GetBoard());

	try {
		auto pModule = pybind11::module_::import(("Plugins." + activePlayer.name + "." + activePlayer.name).c_str());
		int errCode = pModule.attr("PlayRound")(plugin).cast<int>();
		std::cout << "End program with code : " << errCode << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	x = plugin.GetPawnX();
	y = plugin.GetPawnY();
	return static_cast<MoveType>(plugin.GetPawnMove());
}

void GamePlugins::RegisterPlugin(std::string& name)
{
	std::cout << "Making " << name << " Plugin !" << std::endl;
	std::string scriptName = "Plugins." + name + "." + name;
	Teams team = GamePlugins::GetFreeTeam();
	if (team == Teams::NO_TEAM) {
		std::cout << "No team available for " << name << " !" << std::endl;
		return;
	}

	PluginInfo pluginOne = {
		.name = name,
		.team = team,
		.pawnID = 0,
		.pawnRemaining = 0,
		.pluginScript = pybind11::module_::import(scriptName.c_str()),
		.plugin = PluginLib{name},
	};
	plugins.push_back(pluginOne);
}

void GamePlugins::LoadPlugin(PluginInfo &plugin)
{
	try {
		plugin.pluginScript.attr("InitPlugin")(&plugin.plugin);
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	std::cout << "Plugin " << plugin.plugin.GetName() << " loaded !" << std::endl;
}

bool GamePlugins::IsPluginDir(const std::filesystem::directory_entry &path)
{
	std::string dirName = path.path().filename().string();
	return (path.is_directory() && std::filesystem::exists(path.path().string() + "/" + dirName + ".py"));
}

Teams GamePlugins::GetFreeTeam()
{
    for (const auto& team : {Teams::TEAM_ONE, Teams::TEAM_TWO}) {
		bool isFree = true;
		for (const auto& plugin : plugins) {
			if (plugin.team == team) {
				isFree = false;
				break;
			}
		}
		if (isFree)
			return team;
	}
	return Teams::NO_TEAM;
}

} // Namespace SP