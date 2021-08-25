#include <iostream>
#include <SPBluePlugin.h>

std::unique_ptr<SPBluePlugin> bluePlugin;

SPBluePlugin::SPBluePlugin() : SP::SPPlugin()
{

}

int SPBluePlugin::NotVirtualTest()
{
	//this->test();
	return 7;
}

extern "C" SP_API void InitPlugin()
{
	bluePlugin = std::make_unique<SPBluePlugin>();
	std::cout << "plugin initialized !" << std::endl;
}

extern "C" SP_API void RunIntelligenceTurn()
{
	//TODO update bluePlugin

	std::cout << "Info : " << bluePlugin->GetInfo() << std::endl;
	bluePlugin->SetAction();
}
