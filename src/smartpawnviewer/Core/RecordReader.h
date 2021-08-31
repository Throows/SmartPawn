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