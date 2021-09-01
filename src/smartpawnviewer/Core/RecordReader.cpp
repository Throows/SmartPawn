#include <fstream>
#include <regex>
#include "RecordReader.h"

namespace SP
{
	RecordReader::RecordReader(const std::string& fileName)
	{
		std::string path = "./Records/";
		this->filePath = path + fileName;
	}

	void RecordReader::ReadSimulate()
	{
		std::ifstream file(this->filePath);
		if (!file.is_open()){
			std::cout << "Error at file " << this->filePath << " : " << strerror(errno) << std::endl;
		}

		std::string line;
		int lineCount = 0;
		int isRreadingBoard = true;
		while (std::getline(file, line))
		{
			if (line == "## BASE GRID") {
				isRreadingBoard = true;
				continue;
			}
			else if (line == "## STARTING RECORDING")
			{
				isRreadingBoard = false;
				continue;
			}

			if (isRreadingBoard)
			{
				std::vector<int> row;
				std::regex actionFormat;
				try
				{
					actionFormat = std::regex(R"(\{([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*),([0-9]*)\})");
				}
				catch (const std::regex_error& e)
				{
					std::cout << "Regex Error : " << e.what() << std::endl;

				}
				std::smatch result;
				if (!std::regex_match(line, result, actionFormat))
				{
					std::cout << "Error line : " << line << std::endl;
					return;
				}
				for (int i = 1; i < result.size(); i++) {
					row.push_back(std::stoi(result[i]));
				}
				this->board.push_back(row);
				row.clear();
			}
			else
			{
				Action action;
				std::regex actionFormat;
				try
				{
					actionFormat = std::regex(R"(\[([A-Za-z\s_]*)\]\s\-\>\s\{([0-9]*),([0-9]*)\}\s\:\s\{([0-9]*),([0-9]*)\})");
				}
				catch (const std::regex_error& e)
				{
					std::cout << "Regex Error : " << e.what() << std::endl;
						
				}
				std::smatch result;
				if (!std::regex_match(line, result, actionFormat))
				{
					std::cout << "Error line : " << line << std::endl;
					return;
				}
				
				action.team = GetTeam(result[1].str());
				action.fromX = std::stoi(result[2]);
				action.fromY = std::stoi(result[3]);
				action.toX = std::stoi(result[4]);
				action.toY = std::stoi(result[5]);
				this->actions.push_back(action);
			}
			lineCount++;
		}
		std::reverse(this->actions.begin(), this->actions.end());
	}


	Action RecordReader::NextAction()
	{
		Action action = this->actions.at(this->nextAction);
		this->nextAction++;
		return action;
	}

	bool RecordReader::HasNext()
	{
		return this->actions.size() > this->nextAction;
	}

	int RecordReader::GetTeam(std::string& teamName)
	{
		if (!Exist(teamName)) RegisterTeam(teamName);
		return this->teams.find(teamName)->second;
	}

	bool RecordReader::Exist(std::string& teamName)
	{
		if(this->teams.empty()) return false;
		if (this->teams.find(teamName)->first == teamName) return true;
		return false;
	}

	void RecordReader::RegisterTeam(std::string& teamName)
	{
		this->lastTeamNumber++;
		this->teams.emplace(teamName, lastTeamNumber);
	}
}