#include "MenuLayer.h"
#include <glad/glad.h>

namespace SP
{
	MenuLayer::MenuLayer() : Layer("MenuLayer")
	{
	}

	void MenuLayer::OnUpdate()
	{

	}

	void MenuLayer::OnRender()
	{

		glClearColor(1.0f, 0.7f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void MenuLayer::InitLayer()
	{
	}
}
