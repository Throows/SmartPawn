#pragma once
#include "PluginLib.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <filesystem>

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

typedef unsigned int uint;

namespace SP
{

struct Pawn
{
	uint x;
	uint y;
	uint value;
};

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
	std::string path;
	PluginLib plugin;
};

class GamePlugins 
{
public:
	GamePlugins() = default;
	~GamePlugins() = default;
	void InitPlugins();
	const PluginInfo &GetActivePlayer() { return plugins[activePlayerIndex]; };
	[[deprecated("Undefined behavior (if more than 2 players)")]] 
	const PluginInfo& GetWaitingPlayer();
	const PluginInfo& GetPluginByTeam(Teams team);
	std::map<std::string, int> GetTeamsName();
	void SwapTurn();
	void UpdatePawn(std::vector<Pawn> pawns);
	MoveType PlayRound(uint &x, uint &y);

private:
	std::vector<PluginInfo> plugins;
	int activePlayerIndex;

	void RegisterPlugin(std::string& name);
	void LoadPlugin(PluginInfo& plugin);
	bool IsPluginDir(const std::filesystem::directory_entry& dir);
	Teams GetFreeTeam();
};

} // Namespace SP