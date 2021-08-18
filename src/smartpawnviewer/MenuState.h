#pragma once
#include "State.h"
#include "Button.h"

namespace SP
{
	class MenuState : public State
	{
	public:
		MenuState(StatesPtr states, WindowPtr window);
		~MenuState() = default;

		virtual void OnUpdate() override;
		virtual void OnRender() override;

	private:
		void InitState();

		std::vector<Button> buttons;

		sf::Text title;
		std::unique_ptr<sf::Sprite> background;
		std::map<std::string, std::shared_ptr<sf::Texture>> textures;
		std::shared_ptr<sf::Font> font;
	};
}