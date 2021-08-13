#pragma once
#include "Layer.h"

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