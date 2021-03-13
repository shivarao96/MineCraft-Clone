#pragma once

#include <SFML/Graphics.hpp>
#include "../IWorldEvent.h"
#include <glm/glm.hpp>

class Player;

class PlayerDigEvent: public IWorldEvent
{
public:
	PlayerDigEvent(
		sf::Mouse::Button btn,
		const glm::vec3& location,
		Player& player
	);
	void handleWorld(World& world);
private:
	void dig(World& world);

	sf::Mouse::Button m_buttonPress;
	glm::vec3 m_digSpot;
	Player* m_pPlayer;
};

