#include "ListView.h"

namespace SP
{
	ListView::ListView(sf::Vector2f pos, sf::Vector2f size)
	{
		this->background = sf::RectangleShape(size);
		this->background.setPosition(pos);

		this->background.setFillColor(sf::Color(240, 150, 60, 100));
		this->background.setOutlineThickness(2.0f);

		this->scrollBar = sf::RectangleShape(sf::Vector2f(20.0f, (size.y/2.0f)));
		this->scrollBar.setFillColor(sf::Color::White);
		this->scrollBar.setPosition(sf::Vector2f((pos.x + size.x - 20.0f), pos.y));
	}

	void ListView::AddButton(std::shared_ptr<ListViewButton> button)
	{
		this->buttons.push_back(std::move(button));
	}

	void ListView::OnUpdate(sf::RenderWindow& window)
	{
		sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
		float offset = 0;
		if (this->scrollBar.getGlobalBounds().contains(mousePos) || !isReleased) 
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->isReleased = false;
				offset = (this->mouseOffset.y - mousePos.y);
			}
			else this->isReleased = true;
			
		}
		this->mouseOffset = mousePos;

		float newPos = this->scrollBar.getPosition().y - offset;

		if (newPos < this->background.getPosition().y) {
			offset = 0;
		}
		else if ((newPos + this->scrollBar.getSize().y) > (this->background.getPosition().y + this->background.getSize().y)) {
			offset = 0;
		}
			
		this->scrollBar.move(sf::Vector2f(0.0f, -offset));

		int i = 0;
		this->hasClickedButton = false;
		this->clickedButtonOffset = i;
		for (auto& button : this->buttons)
		{
			button->OnUpdate(window, offset*2, this->background.getPosition().y, this->background.getPosition().y + this->background.getSize().y);
			if (button->isClicked)
			{
				this->hasClickedButton = true;
				this->clickedButtonOffset = i;
			}
			i++;
		}
	}

	void ListView::OnRender(sf::RenderWindow& window)
	{
		window.draw(this->background);
		window.draw(this->scrollBar);
		for (auto& button : this->buttons)
		{
			button->OnRender(window);
		}
	}


	void ListView::ProcessEvents(sf::Event& event)
	{

	}

	ListViewButton::ListViewButton(sf::Vector2f pos, sf::Vector2f size, const sf::Font& font, const std::string title)
	{
		this->text = std::make_shared<sf::Text>(title, font);
		this->text->setCharacterSize(15);
		this->text->setPosition(pos.x + ((260.0f - text->getLocalBounds().width)/2), pos.y + 15);

		this->background = sf::RectangleShape(size);
		this->background.setPosition(pos);
		this->isClicked = false;
		this->background.setFillColor(sf::Color(240, 150, 60, 200));
	}

	void ListViewButton::OnUpdate(sf::RenderWindow& window, float offset, float topPos, float botPos)
	{
		this->background.move(0.0f, offset);
		this->text->move(0.0f, offset);
		if (topPos > this->background.getPosition().y || botPos < (this->background.getPosition().y + this->background.getSize().y)) this->hide = true;
		else this->hide = false;
		
		this->isClicked = false;
		if (this->background.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->isClicked = true;
				this->background.setFillColor(sf::Color(240, 150, 60, 0));
			}
			else
			{
				this->background.setFillColor(sf::Color(240, 150, 60, 255));
			}
		}
		else
		{
			this->background.setFillColor(sf::Color(240, 150, 60, 200));
		}

	}

	void ListViewButton::OnRender(sf::RenderWindow& window)
	{
		if (!hide) {
			window.draw(this->background);
			window.draw(*this->text);
		}
	}

}