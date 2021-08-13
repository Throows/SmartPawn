#pragma once
#include "SPpch.h"
namespace SP
{
	class Layer
	{
	public:
		Layer(const std::string& name);
		virtual ~Layer() = default;

		virtual void OnUpdate() {}
		virtual void OnRender() {}

		virtual bool isExitedState() { return this->isExited; }
		virtual void SetExitedState() { this->isExited = true; }

	protected:
		std::string m_layerName;
		bool isExited = false;
	};
}