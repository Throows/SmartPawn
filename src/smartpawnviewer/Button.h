#pragma once
#include "SPpch.h"

enum class State : int
{
	DISABLED = -1,
	IDLE,
	HOVERED,
	CLICKED
};

class Button
{
public:
	Button(unsigned int xPos, unsigned int yPos, unsigned int width, unsigned int height);
	virtual ~Button() = default;

	State GetState() { return m_state; }

private:
	unsigned int m_xPos;
	unsigned int m_yPos;
	unsigned int m_width;
	unsigned int m_height;

	// TEXT, TEXTURE, other attributes
	std::string value;

	State m_state;
};