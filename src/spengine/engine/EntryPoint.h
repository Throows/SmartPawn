#pragma once

extern SP::Application* CreateApplication();

#ifdef SP_PLATFORM_WIN
	
extern SP::Application* SP::CreateApplication();
	
int main(int argc, char** argv) {
	
	auto app = SP::CreateApplication();
	app->Run();
	delete app;
}

#elif SP_PLATFORM_DARWIN
	int main(int argc, char** argv) {

		auto app = SP::CreateApplication();
		app->Run();
		delete app;
	}
#endif

