#pragma once

#include <Core/pch.hpp>
#include <States/State.hpp>
#include <Core/RecordReader.hpp>
#include <GUI/Pawn.hpp>

namespace SPV
{
class ReplayState : public State
{
public:
	ReplayState(StateArgs* args, const std::string& recordFile);
	~ReplayState();
	void OnUpdate() override;
	void OnRender() override;
	void ProcessEvents(sf::Event& event) override;
	bool ExistPawn(int x, int y);
	Pawn* GetPawn(int x, int y);
	void RemovePawn(int x, int y);

	void InitState() override;
	
private:
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

} // Namespace SPV