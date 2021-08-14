#include "Application.h"

namespace SP{

	Application::Application(const unsigned int width, const unsigned int height)
	{
		this->m_width = width;
		this->m_height = height;
		this->layers.push_back(new SimGameLayer());
		this->layers.push_back(new MenuLayer());

		this->Init();

	}

	Application::~Application()
	{
		for (Layer* layer : this->layers)
		{
			delete layer;
		}
	}

	void Application::Run()
	{
		while (m_running) {

			if (this->layers.back()->isExitedState()) this->layers.pop_back();
			if (!this->layers.empty())
			{
				this->layers.back()->OnUpdate();
				this->layers.back()->OnRender();
			}
			else
			{
				m_running = false;
			}


			glfwSwapBuffers(this->window);
			glfwPollEvents();
		}

		glfwSetWindowShouldClose(this->window, true);
		glfwDestroyWindow(this->window);
		glfwTerminate();
	}

	void Application::Init()
	{
		if (glfwInit() != GLFW_TRUE) 
		{
			std::runtime_error err("could not initialize GLFW\n");
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->window = glfwCreateWindow(m_width, m_height, "OpenGL Application", nullptr, nullptr);

		glfwMakeContextCurrent(this->window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::runtime_error err("Failed to initialize GLAD\n");
		}

		glEnable(GL_DEPTH_TEST);

		glfwSetWindowUserPointer(this->window, this);
		RegisterCallbacks();

		glViewport(0, 0, m_width, m_height);
	}

	void Application::RegisterCallbacks()
	{
		glfwSetFramebufferSizeCallback(this->window, [](GLFWwindow* window, int width, int height) {
			static_cast<Application*>(glfwGetWindowUserPointer(window))->FrameBufferSizeCallback(window, width, height);
			});

		glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			static_cast<Application*>(glfwGetWindowUserPointer(window))->InputsCallback(window, key, scancode, action, mods);
			});
	}

	void Application::FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
		m_width = width;
		m_height = height;
	}

	void Application::InputsCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
			layers.back()->SetExitedState();
		}
	}
}