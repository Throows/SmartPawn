#pragma  once
#include <sstream>
#include <fstream>
#include <vector>
#include <map>

namespace SP
{
	class GameRecorder
	{	
	public:
		GameRecorder();
		~GameRecorder();

		void StartRecording(const std::vector<uint8_t>& board, std::map<std::string, int> teams);
		void AddAction(std::string teamName, int oldXcoord, int oldYCoord, int xCoord, int yCoord);
		void AddWinner(std::string winner);
		void SaveRecord();
	private:
		std::string filePath;
		std::ofstream file;
		std::vector<std::string> lines;
		std::string winner;

		std::string formatNumber(int nb);
	};
}