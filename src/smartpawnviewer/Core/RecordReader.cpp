#include <fstream>
#include "RecordReader.h"

namespace SP
{

	RecordReader::RecordReader(const std::string& fileName)
	{
		std::string path = "./Records/";
		this->filePath = path + fileName;

		ReaderState teamState{
			std::regex(R"(\[([A-Za-z\s_]*)\]\{([0-9]*)\})"),
			[=](std::smatch& result) { this->ReadTeams(result); },
			2,
		};
		this->states.emplace(RecordCategory::TEAMS, teamState);

		ReaderState boardState{
			std::regex(R"(\{([0-9]*)\;([0-9]*)\})"),
			[=](std::smatch& result) { this->ReadBoard(result); },
			2,
		};
		this->states.emplace(RecordCategory::BOARD, boardState);

		ReaderState pawnState{
			std::regex(R"(\[([0-9]*)\]\{([0-9]*)\;([0-9]*)\})"),
			[=](std::smatch& result) { this->ReadPawns(result); },
			3,
		};
		this->states.emplace(RecordCategory::PAWNS, pawnState);

		ReaderState recordState{
			std::regex(R"(\[([A-Za-z\s_]*)\]\{([0-9]*)\;([0-9]*)\}\:\{([0-9]*)\;([0-9]*)\})"),
			[=](std::smatch& result) { this->ReadRecord(result); },
			5,
		};
		this->states.emplace(RecordCategory::RECORD, recordState);

		ReaderState winnerState{
			std::regex(R"(\[([A-Za-z\s_]*)\])"),
			[=](std::smatch& result) { this->ReadWinner(result); },
			1,
		};
		this->states.emplace(RecordCategory::WINNER, winnerState);

		ReaderState errorState{
			std::regex(R"((.*))"),
			[=](std::smatch& result) { this->ReadTeams(result); },
			1,
		};
		this->states.emplace(RecordCategory::READ_ERROR, errorState);

	}

	void RecordReader::ReadSimulate()
	{
		std::ifstream file(this->filePath);
		if (!file.is_open()){
			std::cout << "Error at file " << this->filePath << " : " << strerror(errno) << std::endl;
		}

		std::string line;
		int lineCount = 0;
		ReaderState activeReader = this->states.at(RecordCategory::READ_ERROR);
		while (std::getline(file, line))
		{
			if (line.find("##") != std::string::npos) {
				std::string rawState = line.substr(3, line.length()-1);
				this->actualCategory = GetStateFromString(rawState);
				activeReader = this->states.at(this->actualCategory);
				continue;
			}

			std::smatch result;
			if (!std::regex_match(line, result, activeReader.regex))
			{
				std::cout << "Error line : " << line << std::endl;
				return;
			}
			if (result.size()-1 == activeReader.expectedResults)
			{
				(activeReader.readerFunction)(result);
			}
			else
			{
				std::cout << "Unexpected result with size : " << result.size() << std::endl;
				throw std::runtime_error("");
			}
			lineCount++;
		}
		std::reverse(this->actions.begin(), this->actions.end());
	}


	Action RecordReader::GetAction()
	{
		return this->actions.back();
	}

	bool RecordReader::HasNext()
	{
		return !this->actions.empty();
	}

	void RecordReader::UpdateBoard()
	{
		Action action = GetAction();
		this->board.at(action.toY).at(action.toX) = this->board.at(action.fromY).at(action.fromX);
		this->board.at(action.fromY).at(action.fromX) = 0;
		this->actions.pop_back();
	}

	int RecordReader::GetTeam(std::string& teamName)
	{
		 std::map<std::string, int>::iterator team = this->teams.find(teamName);
		 // prevent last team (default value)
		 if (team->first == teamName) return team->second;
		 throw std::runtime_error("Could not find team ! ");
	}

	RecordCategory RecordReader::GetStateFromString(const std::string& str)
	{
		if (str == "TEAMS") return RecordCategory::TEAMS;
		else if (str == "BOARD") return RecordCategory::BOARD;
		else if (str == "PAWNS") return RecordCategory::PAWNS;
		else if (str == "STARTING RECORDING") return RecordCategory::RECORD;
		else if (str == "WINNER") return RecordCategory::WINNER;
		else return RecordCategory::READ_ERROR;

	}

	bool RecordReader::Exist(std::string& teamName)
	{
		if(this->teams.empty()) return false;
		return this->teams.find(teamName)->first == teamName;
	}

	void RecordReader::ReadTeams(std::smatch& result)
	{
		this->teams.emplace(result[1], std::stoi(result[2]));
	}

	void RecordReader::ReadBoard(std::smatch& result)
	{
		for (int y = 0; y < std::stoi(result[2]); y++)
		{
			std::vector<int> row(std::stoi(result[1]), 0);
			this->board.push_back(row);
		}
	}

	void RecordReader::ReadPawns(std::smatch& result)
	{
		int team = std::stoi(result[1]);
		int x = std::stoi(result[2]);
		int y = std::stoi(result[3]);

		this->board.at(y).at(x) = team;
	}

	void RecordReader::ReadRecord(std::smatch& result)
	{
		Action action;
		action.team = GetTeam(result[1].str());
		action.fromX = std::stoi(result[2]);
		action.fromY = std::stoi(result[3]);
		action.toX = std::stoi(result[4]);
		action.toY = std::stoi(result[5]);
		this->actions.push_back(action);
	}

	void RecordReader::ReadError(std::smatch& result)
	{
		std::cout << "Error : " << result[0] << std::endl;
	}

	void RecordReader::ReadWinner(std::smatch& result)
	{
		std::string team = result[1].str();
		std::cout << "Team :" << team << std::endl;
 		if(team == "NO WINNER") this->winnerTeam = "EQUALITÉ";
		else this->winnerTeam = team;
	}
}

