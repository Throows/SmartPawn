#include <SPEngine.h>

class SmartPawnViewer : public SP::Application
{
public:
	SmartPawnViewer() {
		SP::Logger::GetAppLogger();
		SP_INFO("Hello From application !");
	}

	~SmartPawnViewer() {

	}
};

SP::Application* SP::CreateApplication()
{
	return new SmartPawnViewer();
}