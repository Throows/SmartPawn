#pragma once
#include <Core/pch.hpp>
#include <regex>

typedef std::function<void(std::smatch&)> ReaderFun;

struct Action
{
	int team, fromX, fromY, toX, toY;
};

inline 
std::ostream& operator<<(std::ostream& os, const Action& action)
{
	os << "Action(Team:" << action.team << ", Fx:" << action.fromX << ", Fy:" << action.fromY << ", Tx:" << action.toX << ", Ty:" << action.toY << ")";
	return os;
}

enum class RecordCategory
{
	TEAMS = 0,
	BOARD,
	PAWNS,
	RECORD,
	WINNER,
	READ_ERROR
};

struct ReaderState
{
	std::regex regex;
	ReaderFun readerFunction;
	int expectedResults;
};

namespace SPV
{

typedef std::function<bool(std::string&)> CategoryLineReader;
class RecordReader
{
public:
	RecordReader(const std::string& fileName);
	virtual ~RecordReader() = default;

	void ReadSimulate();
	bool HasNext();
	const Action& GetNextAction() { return this->actions.back(); }
	bool Exist(std::string& teamName);
	bool ExistPawn(int x, int y) { return this->board.at(RecordReader::GetIndex(x, y)) != 0; }
	void UpdateBoard();
	int GetTeam(std::string& teamName);
	const std::string& GetWinner() { return this->winnerTeam; }
	std::vector<uint8_t>& GetBoard() { return this->board; }
	const int& GetWidth() { return this->width; }


	bool ReadTeams(std::string& line);
	bool ReadBoard(std::string& line);
	bool ReadPawns(std::string& line);
	bool ReadRecord(std::string& line);
	bool ReadError(std::string& line);
	bool ReadWinner(std::string& line);

private:
	std::map<std::string, int> teams;
	std::vector<uint8_t> board;
	std::vector<Action> actions;
	std::string filePath;
	std::string winnerTeam;
	int width = 0;
	int height = 0;

	RecordCategory GetStateFromString(const std::string &str);
	CategoryLineReader GetCategoryLineReader(const RecordCategory& category);
	bool IsSectionLine(const std::string& line);

	int GetIndex(int x, int y) { return x + (y * this->width); };
};

} // Namespace SPV