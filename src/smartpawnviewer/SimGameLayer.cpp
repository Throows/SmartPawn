#include "SimGameLayer.h"
#include <glad/glad.h>

SimGameLayer::SimGameLayer() : Layer("SimGameLayer")
{

}

void SimGameLayer::OnUpdate()
{
}

void SimGameLayer::OnRender()
{
	glClearColor(1.0f, 0.7f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SimGameLayer::InitLayer()
{
}
