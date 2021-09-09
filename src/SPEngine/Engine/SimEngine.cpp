#include <iostream>

#include <Engine/SimEngine.h>

namespace SP
{
    SimEngine::SimEngine()
    {
		srand((unsigned int)time(NULL));
		this->plugins = std::make_shared<SimPLManager>();
		this->data = std::make_shared <SimData>();
		this->recorder = std::make_shared<SimRecorder>();
		this->plugins->RegisterPlugins();
    }

	void SimEngine::InitEngine()
	{

		//TODO Init plugins
		std::shared_ptr<SPPlugin> api = std::make_shared<SPPlugin>(shared_from_this());

		this->plugins->InitPlugins(api);
		this->data->PlaceRandomPawn(this->initalPawnNumber, this->plugins->GetActivePlayer().pawnIdentifier, this->plugins->GetWaitingPlayer().pawnIdentifier);

		this->recorder->StartRecording(this->data->GetBoard(), this->plugins->GetTeams());
		std::cout << "SimEngine initialized !\n";

		std::cout << "Starting with board : " << std::endl;
		this->data->ShowBoard();
	}

	void SimEngine::PlayNextTurn()
	{

		this->plugins->SwapTurn();
		Plugin plugin = this->plugins->GetActivePlayer();
		plugin.RunInstance();

		CalculateEnded();
		if (this->data->IsGameEnded())
		{
			std::cout << "Player : " << plugin.name << " has won ! " << std::endl;
		}
	}

	float SimEngine::GetPercentageEnded()
	{
		float plOneEndingPercent, plTwoEndingPercent;
		plOneEndingPercent = 1 - (this->data->GetRemainingPawn(1) / (float) this->initalPawnNumber);
		plTwoEndingPercent = 1 - (this->data->GetRemainingPawn(2) / (float) this->initalPawnNumber);
		if (this->data->IsGameEnded()) plOneEndingPercent = 1.0f;
		return plTwoEndingPercent > plOneEndingPercent ? plTwoEndingPercent : plOneEndingPercent;
	}

	void SimEngine::CalculateEnded()
	{
		if (this->data->CalculateTie())
		{
			std::cout << "Sim ended by Equality" << std::endl;
			this->recorder->AddWinner("NO WINNER");
		}
		else if (this->data->CalculateWon(this->plugins->GetActivePlayer().pawnIdentifier, this->plugins->GetWaitingPlayer().pawnIdentifier))
		{

			this->plugins->GetActivePlayer().SetRemainingPawn(this->data->GetRemainingPawn(this->plugins->GetActivePlayer().pawnIdentifier));
			this->plugins->GetWaitingPlayer().SetRemainingPawn(this->data->GetRemainingPawn(this->plugins->GetWaitingPlayer().pawnIdentifier));

			std::string winner = this->plugins->GetActivePlayer().pawnRemaining == 0 ? this->plugins->GetActivePlayer().name : this->plugins->GetWaitingPlayer().name;
			this->recorder->AddWinner(winner);
			std::cout << "Sim ended !" << std::endl;
		}
		else return;


		this->data->ShowBoard();
		
		this->recorder->SaveRecord();

	}

	void SimEngine::AddActionRecorder(PawnCoordinates coords, PawnCoordinates newCoords)
	{
		this->recorder->AddAction(this->plugins->GetActivePlayer().name, coords.x, coords.y, newCoords.x, newCoords.y);
	}
}

extern SP_API std::shared_ptr<SP::SimEngine> CreateEngine()
{
	return std::make_shared<SP::SimEngine>();
}