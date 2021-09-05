#pragma once
#include <Core/pch.h>

namespace SP
{
	class ListViewButton
	{
	public:
		ListViewButton(sf::Vector2f pos, sf::Vector2f size, const sf::Font& font, const std::string title);
		~ListViewButton() = default; 

		void OnUpdate(sf::RenderWindow& window, float offset, float topPos, float botPos);
		void OnRender(sf::RenderWindow& window);

		std::string GetValue() { return this->text->getString();  };

		bool isClicked = false;

	private:
		sf::RectangleShape background;
		std::shared_ptr<sf::Text> text;

		bool hide;

	};


	class ListView
	{
	public:
		ListView(sf::Vector2f pos, sf::Vector2f size);
		~ListView() = default;

		void AddButton(std::shared_ptr<ListViewButton> button);

		void OnUpdate(sf::RenderWindow& window);
		void OnRender(sf::RenderWindow& window);

		void ProcessEvents(sf::Event& event);
		
		bool hasClickedButton = false;

		std::string GetClickedButton() { return this->buttons.at(clickedButtonOffset)->GetValue() + ".txt"; };
		
	private:
		sf::RectangleShape background;
		std::vector<std::shared_ptr<ListViewButton>> buttons;
		sf::RectangleShape scrollBar;
		
		sf::Vector2f mouseOffset;
		bool isReleased = true;
		int clickedButtonOffset = 0;
	};

}