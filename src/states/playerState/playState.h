#pragma once

#include"../baseState.h"
#include "../../entity/player/player.h"
#include "../../world/chunk/chunkSection/chunkSection.h"
#include "../../world/world.h"
#include "../../utility/fpsCounter/fpsCounter.h"

class PlayState: public BaseState
{
public:
	PlayState(Application& app);
	void handleEvents(sf::Event& e) override;
	void handleInputs() override;
	void update(float deltaTime) override;
	void render(MainRenderer& mainRenderer) override;
	bool isStateInitialized() const override;
	void onOpen() override;
private:
	FPSCounter m_fpsCounter;
	Player m_player;
	World m_world;
	sf::RectangleShape m_crossHair;
	sf::Texture m_chTexture;

	bool isStateInit = false;
};

