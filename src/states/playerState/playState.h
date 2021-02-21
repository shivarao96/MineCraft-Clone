#pragma once

#include"../baseState.h"
#include "../../entity/player/player.h"

class PlayState: public BaseState
{
public:
	PlayState(Application& app);
	void handleEvents(sf::Event& e);
	void handleInputs();
	void update(float deltaTime);
	void render(MainRenderer& mainRenderer);
private:
	Player m_player;
};

