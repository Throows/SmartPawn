#include <SPEngine.h>

class SmartPawnViewer : public SP::Application
{
public:
	SmartPawnViewer()
	{
		SP_APP_INFO("Hello From application !");
	}

	~SmartPawnViewer()
	{

	}
};

SP::Application* SP::CreateApplication()
{
	return new SmartPawnViewer();
}