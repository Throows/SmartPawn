#include <Engine/SPGame.h>

#include <iostream>

namespace SP
{

SPGame::SPGame()
{
	srand((unsigned int)time(NULL));
	this->plugins = std::make_shared<GamePlugins>();
	this->board = std::make_shared <GameBoard>(10, 10);
	this->recorder = std::make_shared<GameRecorder>();
	this->plugins->RegisterPlugins();
}

void SPGame::InitGame()
{
	this->plugins->InitPlugins();
	this->board->PopulateBoard(this->initalPawnNumber);
	this->recorder->StartRecording(this->board->GetBoard(), this->plugins->GetTeamsName());
	std::cout << "SPGame initialized !\n";
	std::cout << "Starting with board : " << std::endl;
	this->board->ShowBoard();
}

void SPGame::PlayNextTurn()
{
	this->plugins->SwapTurn();
	SPGame::CalculateEnded();
	if (this->board->IsGameEnded()) {
		std::cout << "Player : has won ! " << std::endl; // TODO
	}
}

float SPGame::GetPercentageEnded()
{
	float plOneEndingPercent, plTwoEndingPercent;
	plOneEndingPercent = 1 - (this->board->GetRemainingPawn(Teams::TEAM_ONE) / (float) this->initalPawnNumber);
	plTwoEndingPercent = 1 - (this->board->GetRemainingPawn(Teams::TEAM_TWO) / (float) this->initalPawnNumber);
	if (this->board->IsGameEnded()) plOneEndingPercent = 1.0f;
	return plTwoEndingPercent > plOneEndingPercent ? plTwoEndingPercent : plOneEndingPercent;
}

void SPGame::CalculateEnded()
{
	if (this->board->CalculateTie())
	{
		std::cout << "Sim ended by Equality" << std::endl;
		this->recorder->AddWinner("NO WINNER");
	}
	else if (this->board->CalculateWon())
	{
		//this->plugins->GetActivePlayer().SetRemainingPawn(this->board->GetRemainingPawn(this->plugins->GetActivePlayer().pawnIdentifier));
		//this->plugins->GetWaitingPlayer().SetRemainingPawn(this->board->GetRemainingPawn(this->plugins->GetWaitingPlayer().pawnIdentifier));
		std::string winner = this->plugins->GetActivePlayer().pawnRemaining == 0 ? this->plugins->GetActivePlayer().name : this->plugins->GetWaitingPlayer().name;
		this->recorder->AddWinner(winner);
		std::cout << "Sim ended !" << std::endl;
	}
	else return;
	this->board->ShowBoard();
	
	this->recorder->SaveRecord();
}
void SPGame::AddActionRecorder(Pawn coords, Pawn newCoords)
{
	this->recorder->AddAction(this->plugins->GetActivePlayer().name, coords.x, coords.y, newCoords.x, newCoords.y);
}

} // Namespace SP