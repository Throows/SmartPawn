#include "Pawn.h"

namespace SP
{
	Pawn::Pawn(int coordX, int coordY, std::shared_ptr<sf::Texture> texture, int rect) : coordX(coordX), coordY(coordY)
	{
		this->pawnTexture = std::make_unique<sf::Sprite>(*texture, sf::IntRect(rect, 0, 35, 35));
		float x = 54 + (4 * coordX + 35 * coordX) + 17.5f;
		float y = 44 + (4 * coordY + 35 * coordY) + 17.5f;

		this->pawnTexture->setPosition(x, y);
		this->pawnTexture->setOrigin(sf::Vector2f(17.5f, 17.5f));
		int rota = rand() % 4;
		SetRotation(rota);
	}

	Pawn::Pawn() : coordX(-1), coordY(-1)
	{
	}

	void Pawn::OnUpdate(sf::RenderWindow& window)
	{
	}

	void Pawn::OnRender(sf::RenderWindow& window)
	{
		window.draw(*this->pawnTexture);
	}

	void Pawn::SetRect(int rectX)
	{
		sf::IntRect rect(rectX, 0, 35, 35);
		this->pawnTexture->setTextureRect(rect);
	}

	void Pawn::SetRotation(int rota)
	{
		switch (rota)
		{
		case 1:
			this->pawnTexture->setRotation(0);
			break;
		case 2:
			this->pawnTexture->setRotation(90);
			break;
		case 3:
			this->pawnTexture->setRotation(180);
			break;
		case 4:
			this->pawnTexture->setRotation(270);
			break;
		default:
			this->pawnTexture->setRotation(0);
			break;
		}

	}
	bool Pawn::IsCoords(int x, int y)
	{
		return (this->coordX == x) && (this->coordY == y);
	}

	void Pawn::SetCoords(int x, int y)
	{
		this->coordX = x;
		this->coordY = y;

		float xcoord = 54 + (4 * coordX + 35 * coordX) + 17.5f;
		float ycoord = 44 + (4 * coordY + 35 * coordY) + 17.5f;

		this->pawnTexture->setPosition(xcoord, ycoord);
	}

	bool Pawn::operator()(int x, int y)
	{
		return IsCoords(x, y);
	}
}