#pragma once

#include "State.hpp"
#include <GUI/ProgressBar.hpp>
#include <SPEngine.hpp>

namespace SPV
{
class SimGameState : public State
{
public:
	SimGameState(StatesPtr states, WindowPtr window);
	virtual ~SimGameState() = default;

	void OnUpdate() override;
	void OnRender() override;
	void ProcessEvents(sf::Event& event) override;
	void SetExitedState() override;

	void InitState() override;
	
private:
	std::shared_ptr<ProgressBar> progressBar;
	sf::Clock clock;
	std::shared_ptr<SP::SPGame> engine;
	std::vector<sf::Text> title;
	std::unique_ptr<sf::Sprite> background;
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;
	std::shared_ptr<sf::Font> font;
};

} // Namespace SPV