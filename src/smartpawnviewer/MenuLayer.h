#pragma once
#include "Layer.h"

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