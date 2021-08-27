#include <iostream>

#include <Engine/SimEngine.h>

namespace SP
{
    SimEngine::SimEngine()
    {
		pluginOne.handle = LoadLibrary("SPIntelligenceBlue.dll");
		pluginTwo.handle = LoadLibrary("SPIntelligence.dll");
		if (pluginOne.handle == NULL)
		{
			throw std::runtime_error("Could not load plugin !");
		}
		std::shared_ptr<SimEngine> enginePTR(std::move(this));
		this->data = std::make_shared<SPData>(enginePTR);
		for (int columnCount = 0; columnCount < 10; columnCount++)
		{
			std::vector<int> column;
			for (int row = 0; row < 10; row++)
			{
				column.push_back(0);
			}
			this->data->GetBoard().push_back(column);
		}
    }

	SimEngine::~SimEngine()
	{
		this->data->GetBoard().clear();
		FreeLibrary(pluginOne.handle);
		FreeLibrary(pluginTwo.handle);
	}

	void SimEngine::InitEngine()
	{
		std::cout << "Making Blue Plugin !" << std::endl;

		INITPLUGIN initBluePlugin;
		initBluePlugin = (INITPLUGIN)GetProcAddress(pluginOne.handle, "InitPlugin");

		if (!initBluePlugin) std::cout << "error : " << GetLastError() << std::endl;
		else initBluePlugin(this->data);

		pluginOne.name = "Blue Plugin";
		pluginOne.isPlayed = false;
		pluginOne.pawnIdentifier = 1;
		pluginOne.pawnRemaining = 0;
		pluginOne.RunInstance = (PLUGIN)GetProcAddress(pluginOne.handle, "RunIntelligenceTurn");

		std::cout << "Making Red Plugin !" << std::endl;

		INITPLUGIN initRedPlugin;
		initRedPlugin = (INITPLUGIN)GetProcAddress(pluginTwo.handle, "InitPlugin");

		if (!initRedPlugin) std::cout << "error : " << GetLastError() << std::endl;
		else initRedPlugin(this->data);

		pluginTwo.name = "Red Plugin";
		pluginTwo.isPlayed = false;
		pluginTwo.pawnIdentifier = 2;
		pluginTwo.pawnRemaining = 0;
		pluginTwo.RunInstance = (PLUGIN)GetProcAddress(pluginTwo.handle, "RunIntelligenceTurn");

		std::cout << "SimEngine initialized !\n";

		srand((unsigned int)time(NULL));
		PlaceRandomPawn();
		ShowBoard();

		this->recorder = std::make_shared<SimRecorder>();
		this->recorder->StartRecoring();

	}

	void SimEngine::PlayNextTurn()
	{
		CalculateEnded();
		if (!isEnded())
		{
			pluginOne.isPlaying = true;
			pluginOne.isPlayed = false;
			pluginOne.RunInstance();
			pluginOne.isPlaying = false;
			std::cout << "Plugin One Played !\n";
			ShowBoard();
		}
		else std::cout << "PLUGIN TWO HAS WON" << std::endl;

		CalculateEnded();
		if (!isEnded())
		{
			pluginTwo.isPlaying = true;
			pluginTwo.isPlayed = false;
			pluginTwo.RunInstance();
			pluginTwo.isPlaying = false;
			std::cout << "Plugin Two Played !\n";
			ShowBoard();
		}
		else std::cout << "PLUGIN ONE HAS WON" << std::endl;
	}

	Plugin SimEngine::GetActivePlayer()
	{
		if (pluginOne.isPlaying && !pluginOne.isPlayed) return pluginOne;
		return pluginTwo;
	}

	Plugin SimEngine::GetWaitingPlayer()
	{
		if (!pluginOne.isPlaying) return pluginOne;
		return pluginTwo;
	}

	Plugin SimEngine::GetTeam(PawnTeam team)
	{
		if (team == PawnTeam::MY_TEAM) return GetActivePlayer();
		else return GetWaitingPlayer();
	}

	float SimEngine::GetPercentageEnded()
	{
		float plOneEndingPercent, plTwoEndingPercent;
		plOneEndingPercent = 1 - (this->data->GetRemainingPawn(1) / 20.0f);
		plTwoEndingPercent = 1 - (this->data->GetRemainingPawn(2) / 20.0f);
		if (this->isEnded()) plOneEndingPercent = 1.0f;
		return plTwoEndingPercent > plOneEndingPercent ? plTwoEndingPercent : plOneEndingPercent;
	}

	void SimEngine::ShowBoard()
	{

		std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
		int boardSize = this->data->GetBoard().front().size();

		for (int i = 0; i < boardSize; i++) 
		{
			std::cout << "  | " << GetPluginChar(this->data->GetBoard().at(0).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(1).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(2).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(3).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(4).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(5).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(6).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(7).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(8).at(i)) << " | "
				<< GetPluginChar(this->data->GetBoard().at(9).at(i)) << " | " << std::endl;
			std::cout << "--+---+---+---+---+---+---+---+---+---+---+--" << std::endl;
		}
	}

	void SimEngine::CalculateEnded()
	{
		int oldPOPawn = pluginOne.pawnRemaining;
		int oldPTPawn = pluginTwo.pawnRemaining;
		pluginOne.pawnRemaining = this->data->GetRemainingPawn(pluginOne.pawnIdentifier);
		pluginTwo.pawnRemaining = this->data->GetRemainingPawn(pluginTwo.pawnIdentifier);

		if (oldPOPawn == pluginOne.pawnRemaining && oldPTPawn == pluginTwo.pawnRemaining) equalityMove++;
		else equalityMove = 0;

		if (pluginOne.pawnRemaining == 0 || pluginTwo.pawnRemaining == 0 || this->equalityMove >= 100) this->ended = true;

		if (this->ended == true)
		{
			if (this->equalityMove >= 50) std::cout << "ended by Equality" << std::endl;
			this->recorder->SaveRecord();
		}

	}

	void SimEngine::AddActionRecorder(PawnCoordinates coords, PawnCoordinates newCoords)
	{

		this->recorder->AddAction(this->GetActivePlayer().name, coords.x, coords.y, newCoords.x, newCoords.y);
	}

	char SimEngine::GetPluginChar(int teamIdentifier)
	{
		switch (teamIdentifier)
		{
		case 1:
			return 'X';
		case 2 :
			return 'O';
		default:
			return ' ';
			break;
		}
	}

	void SimEngine::PlaceRandomPawn()
	{
		while (pluginOne.pawnRemaining < 20 || pluginTwo.pawnRemaining < 20)
		{
			int x = GetRandom(0, 9);
			int y = GetRandom(0, 9);
			if (this->data->isEmpty(x, y))
			{
				if (pluginOne.pawnRemaining < 20) {
					this->data->GetBoard().at(x).at(y) = pluginOne.pawnIdentifier;
					pluginOne.pawnRemaining++;
				}
				else
				{
					this->data->GetBoard().at(x).at(y) = pluginTwo.pawnIdentifier;
					pluginTwo.pawnRemaining++;
				}
			}
		}
	}

	int SimEngine::GetRandom(int min, int max)
	{
		return rand() % max + min;
	}

}

SP_API std::shared_ptr<SP::SimEngine> CreateEngine()
{
	return std::make_shared<SP::SimEngine>();

}