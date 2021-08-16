#include "Button.h"

Button::Button(sf::Vector2f pos, sf::Vector2f scale, const std::string& value, const sf::Font& font, sf::Texture& texture, sf::IntRect idleBound, sf::IntRect hoverBound, sf::IntRect clickedBound)
	: pos(pos), scale(scale)
{
	this->text = sf::Text(value, font);
	m_status = Status::IDLE;

	this->statusBounds.emplace(0, idleBound);
	this->statusBounds.emplace(1, hoverBound);
	this->statusBounds.emplace(2, clickedBound);

	this->sprite.setTexture(texture);

}

void Button::Update()
{
	this->sprite.setTextureRect(this->statusBounds.at(static_cast<int>(this->m_status)));
	this->sprite.setPosition(pos);
	this->sprite.setScale(scale);
}

void Button::Render(std::shared_ptr<sf::RenderWindow> window)
{
	window->draw(sprite);
	window->draw(text);
}
