#include "ProgressBar.hpp"

namespace SPV
{

ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2i size, sf::Texture& bgTexture, sf::Texture& barTexture)
	: pos(pos), size(size)
{
	this->barSprite = std::make_shared<sf::Sprite>(barTexture);
	this->bgSprite = std::make_shared<sf::Sprite>(bgTexture);
	this->bgSprite->setPosition(pos);
	this->barSprite->setPosition(sf::Vector2f(pos.x + 10, pos.y + 10));
	this->progression = 0.0f;
}

void ProgressBar::OnUpdate(sf::RenderWindow& window)
{
	sf::IntRect rect(0, 0, 280*this->progression, 40);
	if (this->progression >= 1.0f)
		this->barSprite->setColor(sf::Color::Green);
	this->barSprite->setTextureRect(rect);
}

void ProgressBar::OnRender(sf::RenderWindow& window)
{
	window.draw(*bgSprite);
	window.draw(*barSprite);
}

void ProgressBar::SetProgress(float progess)
{
	this->progression = progess;
}

} // Namespace SPV