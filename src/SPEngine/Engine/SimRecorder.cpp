#include <Engine/SimRecorder.h>
#include <chrono>
#include<ctime>
#include <iostream>
#include <stdio.h>
#include <filesystem>

namespace SP
{

	SimRecorder::SimRecorder()
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

	SimRecorder::~SimRecorder()
	{
	}

	void SimRecorder::StartRecording(std::vector<std::vector<int>>& board, std::map<std::string, int> teams)
	{
		file.open(filePath, std::ios::app);
		file << "## TEAMS" << std::endl;
		for (auto& entry : teams)
		{
			file << "[" << entry.first << "]{" << entry.second << "}" << std::endl;
		}

		file << "## BOARD" << std::endl;
		file << "{" << board.at(0).size() << ";" << board.size() << "}" << std::endl;

		file << "## PAWNS" << std::endl;
		for (int y = 0; y < board.size(); y++)
		{
			for (int x = 0; x < board.at(y).size(); x++)
			{
				file << "[" << board.at(y).at(x) << "]" << "{" << x << ";" << y << "}" << std::endl;
			}
		}
		
		file << "## STARTING RECORDING" << std::endl;
		file.close();
	}

	void SimRecorder::AddAction(std::string teamName, int oldXcoord, int oldYCoord, int xCoord, int yCoord)
	{
		std::string action = "[" + teamName + "]" + "{" + std::to_string(oldXcoord) + ";" + std::to_string(oldYCoord) + "}:{" + std::to_string(xCoord) + ";" + std::to_string(yCoord) + "}";
		this->lines.push_back(action);
	}

	void SimRecorder::SaveRecord()
	{
		file.open(filePath, std::ios::app);
		if (file.is_open()) {
			for (std::vector<std::string>::iterator it = this->lines.begin(); it != this->lines.end(); ++it)
			{
				file << it->c_str() << std::endl;
			}
		}
		else {
			std::cout << "Error at file " << this->filePath << " : " << strerror(errno) << std::endl;
		}
		std::cout << "Record saved ! Writed " << this->lines.size() << " lines !!" << std::endl;
		this->file.close();
	}

	std::string SimRecorder::formatNumber(int nb)
	{
		return nb < 10 ? "0" + std::to_string(nb) : std::to_string(nb);
	}
}