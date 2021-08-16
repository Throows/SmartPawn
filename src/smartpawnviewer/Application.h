#pragma once

#include "SPpch.h"
#include "SimGameLayer.h"
#include "MenuLayer.h"
#include "Logger.h"

namespace SP {

	class Application
	{
	public:
		Application(const unsigned int width = 960, const unsigned int height = 480);
		virtual ~Application();
		void Run();

	protected:
		void AddLayer(Layer* layer) {layers.push_back(layer);}

	private:
		unsigned int m_width;
		unsigned int m_height;
		bool m_running = true;

		std::vector<Layer*> layers;


		void Init();
		void RegisterCallbacks();
	};
}