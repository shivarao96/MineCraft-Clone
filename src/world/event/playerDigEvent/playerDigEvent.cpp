#include "playerDigEvent.h"
#include "../../world.h"
#include <iostream>

PlayerDigEvent::PlayerDigEvent(sf::Mouse::Button btn, const glm::vec3& location, Player& player)
	:m_buttonPress(btn)
	,m_digSpot(location)
	,m_pPlayer(&player)
{
	std::cout << "X: " << location.x << " Z: " << location.z << std::endl;
}

void PlayerDigEvent::handleWorld(World& world)
{
	auto chunkLocation = World::getChunk(m_digSpot.x, m_digSpot.y);
	if (world.getChunkManager().chunkLoadedAt(chunkLocation.x, chunkLocation.z)) {
		dig(world);
	}
}

void PlayerDigEvent::dig(World& world)
{
	switch (m_buttonPress)
	{
	case sf::Mouse::Button::Left: {
		world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, BlockId::AIR);
		break;
	}
	case sf::Mouse::Button::Right: {
		world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, BlockId::STONE);
		break;
	}
	default:
		break;
	}
}
