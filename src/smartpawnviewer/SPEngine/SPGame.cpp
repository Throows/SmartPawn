#include <SPEngine/SPGame.hpp>

#include <iostream>

#include "Logger.hpp"

namespace SP
{

SPGame::SPGame(unsigned int pawnNB, unsigned int boardWidth, unsigned int boardHeigth, unsigned int tieMoveMax)
	: initalPawnNumber(pawnNB)
{
	srand((unsigned int)time(NULL));
	this->plugins = std::make_unique<GamePlugins>();
	this->board = std::make_unique<GameBoard>(boardWidth, boardHeigth, tieMoveMax);
	this->recorder = std::make_unique<GameRecorder>();
}

void SPGame::InitGame()
{
	this->plugins->InitPlugins();
	this->board->PopulateBoard(this->initalPawnNumber);
	this->recorder->RecordTeams(this->plugins->GetTeamsName());
	this->recorder->RecordBoard(this->board->GetBoardWidth(), this->board->GetBoardHeight());
	this->recorder->RecordInitialPawns(this->board->GetBoard(), this->board->GetBoardWidth(), this->board->GetBoardHeight());
	SP_ENGINE_TRACE("SPGame initialized !");
	this->board->ShowBoard();
}

void SPGame::PlayNextTurn()
{
	this->plugins->SwapTurn();
	this->plugins->UpdatePawn(this->board->GetPawns());

	Pawn oldPawn{
		.x = 0,
		.y = 0,
		.value = 0,
	};
	MoveType move = this->plugins->PlayRound(oldPawn.x, oldPawn.y);

	Pawn newPawn = oldPawn;
	newPawn.value = this->plugins->GetActivePlayer().pawnID;
	this->board->GetPawnByMove(newPawn, move);

	if (this->board->IsValidMove(oldPawn, newPawn)) {
		this->board->SetPawn(oldPawn); // Remove the old pawn from the board
		this->board->SetPawn(newPawn); // Add the new pawn to the board
		SPGame::AddActionRecorder(oldPawn, newPawn);
	}
	else {
		SP_ENGINE_WARN("Move Skipped because invalid");
	}
	SPGame::CalculateEnded();
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
	if (this->board->CalculateTie()) {
		SP_ENGINE_INFO("Sim ended by Equality");
		this->recorder->AddWinner("NO WINNER");
	}
	else if (this->board->CalculateWon()) {
		std::string winner = (this->plugins->GetActivePlayer().pawnRemaining == 0) 
								? this->plugins->GetActivePlayer().name 
								: this->plugins->GetLastPlayer().name;
		this->recorder->AddWinner(winner);
		SP_ENGINE_INFO("Player : {0} has won !", winner);
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