#pragma once
#include <Core/pch.h>

namespace SP
{
	class ProgressBar
	{
	public:
		ProgressBar(sf::Vector2f pos, sf::Vector2i size, sf::Texture& bgTexture, sf::Texture& barTexture);
		~ProgressBar() = default;

		void OnUpdate(sf::RenderWindow& window);
		void OnRender(sf::RenderWindow& window);

		void SetProgress(float progess);

		void AddProgress() { (progression < 1.0f) ? progression += 0.01f : progression = 1.0f; };

	private:
		sf::Vector2f pos;
		sf::Vector2f size;

		float progression;

		std::shared_ptr<sf::Sprite> bgSprite;
		std::shared_ptr<sf::Sprite> barSprite;
	};
}