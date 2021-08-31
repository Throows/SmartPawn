#include "SPPlugin.h"

namespace SP
{
	SPPlugin::SPPlugin(std::shared_ptr<SimEngine> engine)
	{
		this->engine = engine;
	}

	PawnCoordinates SPPlugin::GetRandomPawn(PawnTeam team)
	{
		PawnCoordinates coords;
		coords.x = 0;
		coords.y = 0;
		while (this->engine->GetData()->GetBoard().at(coords.x).at(coords.y) != engine->GetPLManager()->GetTeam(team).pawnIdentifier)
		{
			coords.x = rand() % 10;
			coords.y = rand() % 10;
		}
		return coords;
			 	
	}


	PawnCoordinates SPPlugin::GetFirstPawn(PawnTeam team)
	{
		PawnCoordinates pawnCoordinates;
		pawnCoordinates.x = 0;
		pawnCoordinates.y = 0;

		for (auto& row : this->engine->GetData()->GetBoard())
		{
			pawnCoordinates.y = 0;
			for (auto& col : row)
			{
				if (col == this->engine->GetPLManager()->GetTeam(team).pawnIdentifier) return pawnCoordinates;
				pawnCoordinates.y++;
			}
			pawnCoordinates.x++;
		}
		return pawnCoordinates;
	}

	void SPPlugin::SetAction(PawnCoordinates coords, MOVES move)
	{
		if (this->engine->GetData()->GetBoard().at(coords.x).at(coords.y) != this->engine->GetPLManager()->GetActivePlayer().pawnIdentifier)
		{
			std::cout << "Il est interdi de bouger un pion ennemi ! " << std::endl;
			return;
		}
		this->engine->GetData()->SetPawn(coords.x, coords.y , 0);
		PawnCoordinates newCoords = GetCoordinatesByMove(coords, move);
		this->engine->GetData()->SetPawn(newCoords.x, newCoords.y, this->engine->GetPLManager()->GetActivePlayer().pawnIdentifier);

		this->engine->AddActionRecorder(coords, newCoords);
	}

	PawnCoordinates SPPlugin::GetCoordinatesByMove(PawnCoordinates coord, MOVES moveType)
	{
		PawnCoordinates newCoords;
		newCoords.x = coord.x;
		newCoords.y = coord.y;
		if (moveType == MOVES::UP || moveType == MOVES::LEFT_TOP_CORNER || moveType == MOVES::RIGHT_TOP_CORNER) newCoords.y = (coord.y + 9) % 10;
		if (moveType == MOVES::DOWN || moveType == MOVES::LEFT_DOWN_CORNER || moveType == MOVES::RIGHT_DOWN_CORNER) newCoords.y = (coord.y + 11) % 10;
	
		if (moveType == MOVES::RIGHT || moveType == MOVES::RIGHT_DOWN_CORNER || moveType == MOVES::RIGHT_TOP_CORNER) newCoords.x = (coord.x + 11) % 10;
		if (moveType == MOVES::LEFT || moveType == MOVES::LEFT_DOWN_CORNER || moveType == MOVES::LEFT_TOP_CORNER) newCoords.x = (coord.x + 9) % 10;
		return newCoords;
	}

}