#pragma  once

#include "Core.h"
#include <sstream>
#include <fstream>
#include <vector>

namespace SP
{
	class SimRecorder
	{	
	public:
		SimRecorder();
		~SimRecorder();

		void StartRecording(std::vector<std::vector<int>>& board);
		void AddAction(std::string teamName, int oldXcoord, int oldYCoord, int xCoord, int yCoord);
		void SaveRecord();
	private:
		std::string fileName;
		std::vector<std::string> lines;
	};
}