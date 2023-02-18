#include <Engine/GameRecorder.hpp>
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <cmath>

namespace SP
{

GameRecorder::GameRecorder()
{
	std::filesystem::create_directories("./Records");
	auto time = std::chrono::system_clock::now();
	std::time_t date = std::chrono::system_clock::to_time_t(time);
	int year = 1900 + std::localtime(&date)->tm_year;
	int month = 1 + std::localtime(&date)->tm_mon;
	int day = std::localtime(&date)->tm_mday;
	int hour = std::localtime(&date)->tm_hour;
	int min = std::localtime(&date)->tm_min;
	this->filePath = "Records/REC-" + std::to_string(year) + "-" + formatNumber(month) + "-" + formatNumber(day) + "_" + formatNumber(hour) + "_" + formatNumber(min) + ".txt";
	file = std::ofstream(this->filePath, std::ios::app);
	file.close();
}

void GameRecorder::StartRecording(const std::vector<uint8_t>& board, std::map<std::string, int> teams)
{
	file.open(filePath, std::ios::app);
	file << "## TEAMS" << std::endl;
	for (auto& entry : teams) {
		file << "[" << entry.first << "]{" << entry.second << "}" << std::endl;
	}
	file << "## BOARD" << std::endl;
	file << "{" << std::sqrt(board.size()) << ";" << std::sqrt(board.size()) << "}" << std::endl;
	file << "## PAWNS" << std::endl;
	int x = 0, y = 0; // TODO: get x and y from board
	for (auto& pawn : board) {
		if (pawn != 0)
			file << "[" << pawn << "]" << "{" << x << ";" << y << "}" << std::endl;
	}
	
	file << "## STARTING RECORDING" << std::endl;
	file.close();
}

void GameRecorder::AddAction(std::string teamName, int oldXcoord, int oldYCoord, int xCoord, int yCoord)
{
	std::string action = "[" + teamName + "]" + "{" + std::to_string(oldXcoord) + ";" + std::to_string(oldYCoord) + "}:{" + std::to_string(xCoord) + ";" + std::to_string(yCoord) + "}";
	this->lines.push_back(action);
}

void GameRecorder::AddWinner(std::string winner)
{
	this->winner = winner;
}

void GameRecorder::SaveRecord()
{
	file.open(filePath, std::ios::app);
	if (file.is_open()) {
		for (std::vector<std::string>::iterator it = this->lines.begin(); it != this->lines.end(); ++it) {
			file << it->c_str() << std::endl;
		}
	}
	else {
		std::cout << "Error at file " << this->filePath << " : " << strerror(errno) << std::endl;
	}
	file << "## WINNER" << std::endl;
	file << "[" << this->winner << "]" << std::endl;
	std::cout << "Record saved ! Writed " << this->lines.size() << " lines !!" << std::endl;
	this->file.close();
}

std::string GameRecorder::formatNumber(int nb)
{
	return nb < 10 ? "0" + std::to_string(nb) : std::to_string(nb);
}

} // Namespace SP