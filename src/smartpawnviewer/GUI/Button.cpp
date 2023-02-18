#include "Button.hpp"

Button::Button(sf::Vector2f pos, sf::Vector2i size, const std::string& value, const sf::Font& font, sf::Texture& texture, sf::Vector2i idleBound, sf::Vector2i hoverBound, sf::Vector2i clickedBound)
	: pos(pos), size(size)
{
	this->text = std::make_shared<sf::Text>(value, font);
	m_status = Status::IDLE;

	this->statusBounds.emplace(Status::IDLE, idleBound);
	this->statusBounds.emplace(Status::HOVERED, hoverBound);
	this->statusBounds.emplace(Status::CLICKED, clickedBound);

	this->sprite = std::make_shared<sf::Sprite>(texture, sf::IntRect(idleBound, size));
	SetPosition(pos);
}

void Button::Update(sf::Vector2f& mousePos)
{
	UpdateState(mousePos);

	sf::Vector2i startingText = this->statusBounds.at(this->m_status);
	this->sprite->setTextureRect(sf::IntRect(startingText, size));
}

void Button::Render(sf::RenderTarget& window)
{
	window.draw(*sprite);
	window.draw(*text);
}

void Button::UpdateState(sf::Vector2f& mousePos)
{
	this->m_status = Status::IDLE;
	if (this->sprite->getGlobalBounds().contains(mousePos)) {
		this->m_status = Status::HOVERED;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			this->m_status = Status::CLICKED;
		}
	}
}

void Button::SetPosition(sf::Vector2f pos)
{
	this->pos = pos;
	this->sprite->setPosition(pos);

	float xTextPos = pos.x + ((sprite->getGlobalBounds().width - text->getGlobalBounds().width) / 2.0f);
	float yTextPos = pos.y + ((sprite->getGlobalBounds().height - text->getGlobalBounds().height) / 2.5f);
	this->text->setPosition(xTextPos, yTextPos);
}
