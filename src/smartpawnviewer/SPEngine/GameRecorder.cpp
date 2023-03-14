#include <SPEngine/GameRecorder.hpp>

#include <chrono>
#include <ctime>
#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <cmath>

#include "Logger.hpp"

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
	// check if exist
	std::ifstream fileCheck(this->filePath);
	int i = 1;
	while (fileCheck.good()) {
		fileCheck.close();
		this->filePath = "Records/REC-" + std::to_string(year) + "-" + formatNumber(month) + "-" + formatNumber(day) + "_" + formatNumber(hour) + "_" + formatNumber(min) + "_(" + std::to_string(i) + ").txt";
		fileCheck = std::ifstream(this->filePath);
		i++;
	}
	fileCheck.close();
	file = std::ofstream(this->filePath, std::ios::app);
	file.close();
}

void GameRecorder::RecordTeams(const std::map<std::string, int> &teams)
{
	file.open(filePath, std::ios::app);
	file << "## TEAMS" << std::endl;
	for (auto& entry : teams) {
		file << "[" << entry.first << "]{" << entry.second << "}" << std::endl;
	}
	file.close();
}

void GameRecorder::RecordBoard(int bWidth, int bHeigth)
{
	file.open(filePath, std::ios::app);
	file << "## BOARD" << std::endl;
	file << "{" << bWidth << ";" << bHeigth << "}" << std::endl;
	file.close();
}

void GameRecorder::RecordInitialPawns(const std::vector<uint8_t> &board, int bWidth, int bHeigth)
{
	file.open(filePath, std::ios::app);
	file << "## PAWNS" << std::endl;
	int id = 0, x, y;
	for (const auto& pawn : board) {
		if (pawn != 0) {
			x = id % bWidth;
			y = id / bHeigth;
			file << "[" << static_cast<int>(pawn) << "]" << "{" << x << ";" << y << "}" << std::endl;
		}
		id++;
	}
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
	file << "## STARTING RECORDING" << std::endl;
	if (file.is_open()) {
		for (std::vector<std::string>::iterator it = this->lines.begin(); it != this->lines.end(); ++it) {
			file << it->c_str() << std::endl;
		}
	}
	else {
		SP_ENGINE_ERROR("At file {0} : {1}", this->filePath, strerror(errno));
	}
	file << "## WINNER" << std::endl;
	file << "[" << this->winner << "]" << std::endl;
	SP_ENGINE_TRACE("Record saved ! Writed {0} lines", this->lines.size());
	this->file.close();
}

std::string GameRecorder::formatNumber(int nb)
{
	return nb < 10 ? "0" + std::to_string(nb) : std::to_string(nb);
}

} // Namespace SP