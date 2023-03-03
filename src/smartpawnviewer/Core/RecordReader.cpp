
#include "RecordReader.hpp"

#include <fstream>

const std::map<const std::string, RecordCategory> categoryMap = {
	{"TEAMS", RecordCategory::TEAMS},
	{"BOARD", RecordCategory::BOARD},
	{"PAWNS", RecordCategory::PAWNS},
	{"STARTING RECORDING", RecordCategory::RECORD},
	{"WINNER", RecordCategory::WINNER},
};

namespace SPV
{

RecordReader::RecordReader(const std::string& fileName)
{
	std::string path = "./Records/";
	this->filePath = path + fileName;
}

void RecordReader::ReadSimulate()
{
	std::ifstream file(this->filePath);
	if (!file.is_open()) {
		std::cout << "Error at file " << this->filePath << " : " << strerror(errno) << std::endl;
	}

	std::string line;
	int lineCount = 0;
	RecordCategory lastCategory = RecordCategory::READ_ERROR;
	CategoryLineReader lineReader = nullptr;
	while (std::getline(file, line)) {
		if (RecordReader::IsSectionLine(line)) {
			lastCategory = RecordReader::GetStateFromString(line);
			lineReader = RecordReader::GetCategoryLineReader(lastCategory);
			continue;
		}
		if (!lineReader) {
			throw std::runtime_error("Error while trying to find the reader");
		}
		if (!lineReader(line)) {
			throw std::runtime_error("Error while trying to Read the line");
		}
		lineCount++;
	}
	std::reverse(this->actions.begin(), this->actions.end());
}

bool RecordReader::HasNext()
{
	return !this->actions.empty();
}

void RecordReader::UpdateBoard()
{
	Action& action = this->actions.back();
	int coordsTo = RecordReader::GetIndex(action.toX, action.toY);
	int coordsFrom = RecordReader::GetIndex(action.fromX, action.fromY);
	this->board.at(coordsTo) = this->board.at(coordsFrom);
	this->board.at(coordsFrom) = 0;
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
	std::string stateStr = str.substr(3, str.length() - 1);

	auto it = categoryMap.find(stateStr);
	if (it != categoryMap.end()) {
		return it->second;
	}
	return RecordCategory::READ_ERROR;
}

bool RecordReader::Exist(std::string& teamName)
{
	if(this->teams.empty()) return false;
	return this->teams.find(teamName)->first == teamName;
}

bool RecordReader::ReadTeams(std::string& line)
{
	std::smatch result;
	if (!std::regex_match(line, result, std::regex(R"(\[([A-Za-z\s_]*)\]\{([0-9]*)\})"))) {
		std::cout << "Error line : " << line << std::endl;
		std::cout << "Regex does not match !\n";
		return false;
	}
	if (result.size() == 3) {
		this->teams.emplace(result[1], std::stoi(result[2]));
		return true;
	}
	return false;
}

bool RecordReader::ReadBoard(std::string& line)
{
	std::smatch result;
	if (!std::regex_match(line, result, std::regex(R"(\{([0-9]*)\;([0-9]*)\})"))) {
		std::cout << "Error line : " << line << std::endl;
		std::cout << "Regex does not match !\n";
		return false;
	}
	if (result.size() == 3) {
		this->width = std::stoi(result[1]);
		this->height = std::stoi(result[2]);
		this->board.clear();
		this->board.resize(this->width * this->height, 0);
		return true;
	}
	return false;
}

bool RecordReader::ReadPawns(std::string& line)
{
	std::smatch result;
	if (!std::regex_match(line, result, std::regex(R"(\[([0-9]*)\]\{([0-9]*)\;([0-9]*)\})"))) {
		std::cout << "Error line : " << line << std::endl;
		std::cout << "Regex does not match !\n";
		return false;
	}
	if (result.size() == 4) {
		int team = std::stoi(result[1]);
		int coord = RecordReader::GetIndex(std::stoi(result[2]), std::stoi(result[3]));
		this->board.at(coord) = team;
		return true;
	}
	return false;
}

bool RecordReader::ReadRecord(std::string& line)
{
	std::smatch result;
	if (!std::regex_match(line, result, std::regex(R"(\[([A-Za-z\s_]*)\]\{([0-9]*)\;([0-9]*)\}\:\{([0-9]*)\;([0-9]*)\})"))) {
		std::cout << "Error line : " << line << std::endl;
		std::cout << "Regex does not match !\n";
		return false;
	}
	if (result.size() == 6) {
		auto teamStr = result[1].str();
		Action action{
			.team = GetTeam(teamStr),
			.fromX = std::stoi(result[2]),
			.fromY = std::stoi(result[3]),
			.toX = std::stoi(result[4]),
			.toY = std::stoi(result[5]),
		};
		this->actions.push_back(action);
		return true;
	}
	return false;
}

bool RecordReader::ReadError(std::string& line)
{
	std::cout << "Error at line : " << line << std::endl;
	return true;
}

bool RecordReader::ReadWinner(std::string& line)
{
	std::smatch result;
	if (!std::regex_match(line, result, std::regex(R"(\[([A-Za-z\s_]*)\])"))) {
		std::cout << "Error line : " << line << std::endl;
		std::cout << "Regex does not match !\n";
		return false;
	}
	if (result.size() == 2) {
		std::string team = result[1].str();
		this->winnerTeam = (team == "NO WINNER") ?  "EQUALITÉ" : team;
		return true;
	}
	return false;
}

CategoryLineReader RecordReader::GetCategoryLineReader(const RecordCategory& category)
{
    switch (category)
	{
	case RecordCategory::TEAMS:
		return [this](std::string& line) { return RecordReader::ReadTeams(line); };
		break;
	case RecordCategory::BOARD:
		return [this](std::string& line) { return RecordReader::ReadBoard(line); };
		break;
	case RecordCategory::PAWNS:
		return [this](std::string& line) { return RecordReader::ReadPawns(line); };
		break;
	case RecordCategory::RECORD:
		return [this](std::string& line) { return RecordReader::ReadRecord(line); };
		break;
	case RecordCategory::WINNER:
		return [this](std::string& line) { return RecordReader::ReadWinner(line); };
		break;
	default:
		return [this](std::string& line) { return RecordReader::ReadError(line); };
		break;
	}
}

bool RecordReader::IsSectionLine(const std::string &line)
{
	return line.find("##") != std::string::npos;
}

} // Namespace SPV