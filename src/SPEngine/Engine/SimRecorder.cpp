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
		auto time = std::chrono::system_clock::now();
		std::time_t date = std::chrono::system_clock::to_time_t(time);
		std::string year = std::to_string(1900 + std::localtime(&date)->tm_year);
		std::string month = std::to_string(1 + std::localtime(&date)->tm_mon);
		std::string day = std::to_string(std::localtime(&date)->tm_mday);
		std::string hour = std::to_string(std::localtime(&date)->tm_hour);
		std::string min = std::to_string(std::localtime(&date)->tm_min);

		this->fileName = std::string("Recording-");
		this->fileName.append(year).append("_").append(month).append("_").append(day).append("-").append(hour).append("-").append(min);
		this->fileName.append(".txt");
	}

	SimRecorder::~SimRecorder()
	{
	}

	void SimRecorder::StartRecording(std::vector<std::vector<int>>& board)
	{
		this->lines.push_back("## BASE GRID");
		for (auto& column : board)
		{
			std::string line = "{";
			bool first = true;
			for (auto& row : column)
			{
				if (first) first = false;
				else line += ",";
				line += std::to_string(row);
			}
			line += "}";
			this->lines.push_back(line);
		}

		this->lines.push_back("## STARTING RECORDING");
	}

	void SimRecorder::AddAction(std::string teamName, int oldXcoord, int oldYCoord, int xCoord, int yCoord)
	{
		std::string action = std::string();
		action.append("[").append(teamName).append("]").append(" -> {").append(std::to_string(oldXcoord)).append(",").append(std::to_string(oldYCoord)).append("} : {").append(std::to_string(xCoord)).append(",").append(std::to_string(yCoord)).append("}");
		this->lines.push_back(action);
	}

	void SimRecorder::SaveRecord()
	{
		std::filesystem::create_directories("./Records");
		std::ofstream fileStream = std::ofstream(std::string("Records/").append(this->fileName));
	
		if (fileStream.is_open()) {
			for (std::vector<std::string>::iterator it = this->lines.begin(); it != this->lines.end(); ++it)
			{
				fileStream << it->c_str() << std::endl;
			}
		}
		else {
			std::cout << "Error at file " << this->fileName << " : " << strerror(errno) << std::endl;
		}
		std::cout << "Record saved ! Writed " << this->lines.size() << " lines !!" << std::endl;
		fileStream.close();
	}
}