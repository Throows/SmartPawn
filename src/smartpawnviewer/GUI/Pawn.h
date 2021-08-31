#pragma once

#include <Core/pch.h>

namespace SP
{
	class Pawn
	{
	public:
		Pawn(int coordX, int coordY, std::shared_ptr<sf::Texture> texture, int rect);
		~Pawn() = default;

		//useless maybe later 
		//void OnUpdate(sf::RenderWindow& window);
		void OnRender(sf::RenderWindow& window);

		void SetRect(int rectX);
		void SetRotation(int rota);

	private:
		int coordX;
		int coordY;
		std::unique_ptr<sf::Sprite> pawnTexture;
	};
}