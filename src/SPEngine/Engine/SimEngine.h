#pragma once

#include "Core.h"
#include <Engine/SimPlManager.h>
#include <Engine/SimData.h>
#include <Engine/SimRecorder.h>

namespace SP
{
	class SimPLManager;
}

enum class PawnTeam;
struct PawnCoordinates;

namespace SP
{

	class SPPlugin;

	class SP_API SimEngine 
		: public std::enable_shared_from_this<SimEngine>
	{
	public:
		SimEngine();
		virtual ~SimEngine() = default;

		void InitEngine();
		void PlayNextTurn();

		float GetPercentageEnded();
		void CalculateEnded();

		void AddActionRecorder(PawnCoordinates coords, PawnCoordinates newCoords);

		std::shared_ptr<SimData> GetData() { return this->data; };
		std::shared_ptr<SimPLManager> GetPLManager() { return this->plugins; };

	private:
		std::shared_ptr<SimPLManager> plugins;
		std::shared_ptr<SimData> data;
		std::shared_ptr<SimRecorder> recorder;

		const unsigned int initalPawnNumber = 5;

	};
};