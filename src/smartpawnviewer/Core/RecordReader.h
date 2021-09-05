#pragma once
#include <Core/pch.h>
#include <regex>

using ReaderFun = std::function<void(std::smatch&)>;

struct Action
{
	int team, fromX, fromY, toX, toY;
};

enum class RecordCategory
{
	TEAMS = 0,
	BOARD,
	PAWNS,
	RECORD,
	READ_ERROR
};

struct ReaderState
{
	std::regex regex;
	ReaderFun readerFunction;
	int expectedResults;
};


namespace SP
{
	class RecordReader
	{
	public:
		RecordReader(const std::string& fileName);
		~RecordReader() = default;

		void ReadSimulate();
		Action GetAction();
		bool HasNext();

		bool Exist(std::string& teamName);
		bool ExistPawn(int x, int y) { return this->board.at(y).at(x) != 0; };
		void UpdateBoard();
		int GetTeam(std::string& teamName);

		std::vector<std::vector<int>>& GetBoard() { return this->board; };

		RecordCategory GetStateFromString(const std::string& str);

		void ReadTeams(std::smatch& result);
		void ReadBoard(std::smatch& result);
		void ReadPawns(std::smatch& result);
		void ReadRecord(std::smatch& result);
		void ReadError(std::smatch& result);

	private:
		std::map<std::string, int> teams;
		std::vector<std::vector<int>> board;
		std::vector<Action> actions;
		std::string filePath;

		RecordCategory actualCategory;
		std::map<RecordCategory, ReaderState> states;	

	};
}