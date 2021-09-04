#pragma once

#include <Core/pch.h>

struct Action
{
	int team, fromX, fromY, toX, toY;
};

namespace SP
{
	class RecordReader
	{
	public:
		RecordReader(const std::string& fileName);
		~RecordReader() = default;

		void ReadSimulate();
		Action NextAction();
		bool HasNext();

		bool Exist(std::string& teamName);
		//bool ExistPawn(int x, int y) { return this->board.at(y).at(x) != 0; };
		void MoveTo(int fromX, int fromY, int toX, int toY);
		void RegisterTeam(std::string& teamName);
		int GetTeam(std::string& teamName);

		std::vector<std::vector<int>>& GetBoard() { return this->board; };

	private:
		std::map<std::string, int> teams;
		std::vector<std::vector<int>> board;
		std::vector<Action> actions;
		std::string filePath;
		int nextAction = 0;
		int lastTeamNumber = 0;
	};
}