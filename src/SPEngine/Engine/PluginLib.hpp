#pragma once
#include <string>
namespace SP
{

class PluginLib
{
public:
	PluginLib(std::string name);
	virtual ~PluginLib() = default;
	void Update();
	std::string GetName() { return this->name; }
	int GetRandomPawn();
	int GetFirstPawn();
	bool SetAction(int x, int y, int moveType);

private:
	int GetCoordinatesByMove(int x, int y, int moveType);
	bool hasPlayed = false;
	std::string name;
};

} // Namespace SP