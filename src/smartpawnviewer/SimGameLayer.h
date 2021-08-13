#pragma once
#include "Layer.h"

namespace SP
{
	class SimGameLayer : public Layer
	{
	public:
		SimGameLayer();
		~SimGameLayer() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitLayer();
	};
}