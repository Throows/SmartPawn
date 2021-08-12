#include <SPEngine.h>

class SmartPawnViewer : public SP::Application
{
public:
	SmartPawnViewer() {

	}

	~SmartPawnViewer() {

	}
};

SP::Application* SP::CreateApplication()
{
	return new SmartPawnViewer();
}