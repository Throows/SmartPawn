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
	virtual ~GameRecorder() = default;

	void RecordTeams(const std::map<std::string, int>& teams);
	void RecordBoard(int bWidth, int bHeigth);
	void RecordInitialPawns(const std::vector<uint8_t>& board, int xCoord, int yCoord);
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

} // Namespace SP