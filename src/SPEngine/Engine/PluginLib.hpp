#pragma once

namespace SP
{

class PluginLib
{
public:
	PluginLib(); // TODO add plugin data  (name, team, pawnID, pawnRemaining, pluginScript, plugin)
	virtual ~PluginLib() = default;
	void Update();
	int GetRandomPawn();
	int GetFirstPawn();
	bool SetAction(int x, int y, int moveType);

private:
	int GetCoordinatesByMove(int x, int y, int moveType);
	bool hasPlayed = false;
};

} // Namespace SP