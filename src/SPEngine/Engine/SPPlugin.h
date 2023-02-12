#pragma once
#include <Engine/SimEngine.h>

namespace SP
{
	class SimEngine;
	class SimPLManager;
}

enum class MOVES;
enum class PawnTeam;
struct PawnCoordinates;

namespace SP
{
	class SPPlugin
	{
	public:
		SPPlugin(std::shared_ptr<SimEngine> engine);
		virtual ~SPPlugin() = default;

		PawnCoordinates GetRandomPawn(PawnTeam team);
		PawnCoordinates GetFirstPawn(PawnTeam team);

		void SetAction(PawnCoordinates coords, MOVES move);

	private:
		std::shared_ptr<SimEngine> engine;
		PawnCoordinates GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType);
	};
}