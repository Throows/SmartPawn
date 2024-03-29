#pragma once

#include <Core/pch.hpp>

namespace SPV
{
class Pawn
{
public:
	Pawn(int coordX, int coordY, std::shared_ptr<sf::Texture> texture, int rect);
	Pawn();
	virtual ~Pawn() = default;

	//useless maybe later 
	void OnUpdate(sf::RenderWindow& window);
	void OnRender(sf::RenderWindow& window);
	void SetRect(int rectX);
	void SetRotation(int rota);
	bool IsCoords(int x, int y);
	void SetCoords(int x, int y);
	bool operator()(int x, int y);
	
private:
	int coordX;
	int coordY;
	std::unique_ptr<sf::Sprite> pawnTexture;
};

} // Namespace SPV