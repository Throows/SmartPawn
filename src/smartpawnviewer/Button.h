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
	Button(sf::Vector2f pos, sf::Vector2i size, const std::string& value, const sf::Font& font, sf::Texture& texture, sf::Vector2i idleBound, sf::Vector2i hoverBound, sf::Vector2i clickedBound);
	virtual ~Button() = default;

	Status GetState() { return m_status; }

	void SetPosition(sf::Vector2f pos);

	void Update(sf::Vector2f& mousePos);
	void Render(sf::RenderTarget& window);


private:
	sf::Vector2f pos;
	sf::Vector2i size;

	std::shared_ptr<sf::Sprite> sprite;
	std::map<Status, sf::Vector2i> statusBounds;

	std::shared_ptr<sf::Text> text;

	Status m_status;


	void UpdateState(sf::Vector2f& mousePos);
};