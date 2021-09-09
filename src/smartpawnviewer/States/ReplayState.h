#pragma once

#include <Core/pch.h>
#include <States/State.h>
#include <Core/RecordReader.h>
#include <GUI/Pawn.h>

namespace SP
{
	class ReplayState : public State
	{
	public:
		ReplayState(StatesPtr states, WindowPtr window, const std::string& recordFile);
		~ReplayState();

		virtual void OnUpdate() override;
		virtual void OnRender() override;
		void ProcessEvents(sf::Event& event) override;

		bool ExistPawn(int x, int y);
		std::shared_ptr<Pawn> GetPawn(int x, int y);
		void RemovePawn(int x, int y);

	private:
		void InitState();
		void UpdateReplay();
		bool isReplay = true;


		RecordReader reader;

		sf::Clock clock;

		std::shared_ptr<sf::Font> font;
		sf::Text title;
		std::unique_ptr<sf::Sprite> background;
		std::unique_ptr<sf::Sprite> grid;
		std::vector<std::shared_ptr<Pawn>> pawns;
		std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	};
}