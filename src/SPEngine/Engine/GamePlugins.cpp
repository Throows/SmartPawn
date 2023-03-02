#include "GamePlugins.hpp"

#define NB_MAX_PLAYER 2
namespace SP
{

void GamePlugins::InitPlugins()
{
	// Check the folder for plugins
	if (!std::filesystem::exists("Plugins") || !std::filesystem::is_directory("Plugins")) {
		std::cout << "No plugins folder found !" << std::endl;
		return;
	}

	pybind11::scoped_interpreter scope{};

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

void GamePlugins::UpdatePawn(std::vector<Pawn> pawns)
{
	PluginInfo& activePlayer = plugins[activePlayerIndex];
	activePlayer.plugin.Reset();
	activePlayer.pawnRemaining = 0;
	for (const auto &pawn : pawns) {
		if (pawn.value == static_cast<uint>(activePlayer.team)) {
			activePlayer.pawnRemaining++;
			activePlayer.plugin.myPawns.push_back({static_cast<int>(pawn.x), static_cast<int>(pawn.y)});
		}
		else {
			activePlayer.plugin.ennemyPawns.push_back({static_cast<int>(pawn.x), static_cast<int>(pawn.y)});
		}
	}
}

MoveType GamePlugins::PlayRound(uint &x, uint &y)
{
	pybind11::scoped_interpreter scope{};

	try {
		auto pModule = pybind11::module_::import(plugins[activePlayerIndex].path.c_str());
		int errCode = pModule.attr("PlayRound")(&(plugins[activePlayerIndex].plugin)).cast<int>();
		std::cout << "End program with code : " << errCode << std::endl;
	}
	catch (const std::exception &e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
	Coordinates pawn = plugins[activePlayerIndex].plugin.GetPawnCoordinates();
	std::cout << "Pawn coordinates : " << pawn.x << " " << pawn.y << std::endl;
	std::cout << "move : " << (int)plugins[activePlayerIndex].plugin.GetPawnMove() << std::endl;
	x = pawn.x;
	y = pawn.y;
	return plugins[activePlayerIndex].plugin.GetPawnMove();
}

void GamePlugins::RegisterPlugin(std::string& name)
{
	std::cout << "Making " << name << " Plugin !" << std::endl;
	Teams team = GamePlugins::GetFreeTeam();
	if (team == Teams::NO_TEAM) {
		std::cout << "No team available for " << name << " !" << std::endl;
		return;
	}

	PluginInfo plugin = {
		.name = name,
		.team = team,
		.pawnID = (uint) team,
		.path = "Plugins." + name + "." + name,
		.plugin = PluginLib{name},
	};
	plugins.push_back(plugin);
}

void GamePlugins::LoadPlugin(PluginInfo &plugin)
{
	try {
		auto pModule = pybind11::module_::import(plugin.path.c_str());
		pModule.attr("InitPlugin")(&plugin.plugin);
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