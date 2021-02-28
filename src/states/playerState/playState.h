#pragma once

#include"../baseState.h"
#include "../../entity/player/player.h"
#include "../../world/chunk/chunkSection/chunkSection.h"
#include "../../world/world.h"


class PlayState: public BaseState
{
public:
	PlayState(Application& app);
	void handleEvents(sf::Event& e);
	void handleInputs();
	void update(float deltaTime);
	void render(MainRenderer& mainRenderer);
	bool isStateInitialized() const;
private:
	Player m_player;
	World m_world;
	bool isStateInit = false;
};

