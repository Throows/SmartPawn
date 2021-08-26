#include <iostream>
#include <SPBluePlugin.h>

std::unique_ptr<SPBluePlugin> bluePlugin;

SPBluePlugin::SPBluePlugin(std::shared_ptr<SP::SPData> data)
{
	this->data = std::move(data);
}

MOVES SPBluePlugin::FindNearestPawnToMove(PawnCoordinates from, PawnCoordinates to)
{
	int diffX, diffY;
	diffX = from.x - to.x;
	diffY = from.y - to.y;

	if (diffX < 0)
	{
		if (diffY < 0)
		{
			return MOVES::RIGHT_DOWN_CORNER;
		}
		else if (diffY == 0)
		{
			return MOVES::DOWN;
		}
		else
		{
			return MOVES::LEFT_DOWN_CORNER;
		}
	}
	else if (diffX == 0)
	{
		if (diffY < 0)
		{
			return MOVES::LEFT;
		}
		else
		{
			return MOVES::RIGHT;
		}
	}
	else
	{
		if (diffY < 0)
		{
			return MOVES::RIGHT_TOP_CORNER;
		}
		else if (diffY == 0)
		{
			return MOVES::UP;
		}
		else
		{
			return MOVES::LEFT_TOP_CORNER;
		}
	}
}

extern "C" SP_API void InitPlugin(std::shared_ptr<SP::SPData> data)
{
	bluePlugin = std::make_unique<SPBluePlugin>(data);
	std::cout << "plugin initialized !" << std::endl;
}

extern "C" SP_API void RunIntelligenceTurn()
{
	PawnCoordinates myTeam = bluePlugin->GetData()->GetRandomPawn(1);
	PawnCoordinates enemyTeam = bluePlugin->GetData()->GetFirstPawn(2);
	MOVES move = bluePlugin->FindNearestPawnToMove(myTeam, enemyTeam);

	bluePlugin->GetData()->SetAction(myTeam, move, 1);
}

extern "C" SP_API void shudownPlugin()
{

}