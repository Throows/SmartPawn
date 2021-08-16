#pragma once
#include "SPpch.h"

enum class Status : int
{
	DISABLED = 0,
	IDLE = 0,
	HOVERED,
	CLICKED
};

class Button
{
public:
	Button(sf::Vector2f pos, sf::Vector2f scale, const std::string& value, const sf::Font& font, sf::Texture& texture, sf::IntRect idleBound, sf::IntRect hoverBound, sf::IntRect clickedBound);
	virtual ~Button() = default;

	Status GetState() { return m_status; }

	void Update();
	void Render(std::shared_ptr<sf::RenderWindow> window);


private:
	sf::Vector2f pos;
	sf::Vector2f scale;

	sf::Sprite sprite;
	std::map<int, sf::IntRect> statusBounds;

	sf::Text text;

	Status m_status;
};