#pragma once
#include "Layer.h"
namespace SP
{
	class MenuLayer : public Layer
	{
	public:
		MenuLayer();
		~MenuLayer() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitLayer();
	};
}