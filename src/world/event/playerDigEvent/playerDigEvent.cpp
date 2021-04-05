#include "playerDigEvent.h"
#include "../../world.h"
#include <iostream>

PlayerDigEvent::PlayerDigEvent(sf::Mouse::Button btn, const glm::vec3& location, Player& player)
	:m_buttonPress(btn)
	,m_digSpot(location)
	,m_pPlayer(&player)
{
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
		world.updateChunk(m_digSpot.x, m_digSpot.y, m_digSpot.z);
		world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, BlockId::AIR);
		break;
	}
	case sf::Mouse::Button::Right: {
		world.updateChunk(m_digSpot.x, m_digSpot.y, m_digSpot.z);
		world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, BlockId::STONE);
		break;
	}
	default:
		break;
	}
}
