#include "playerDigEvent.h"
#include "../../world.h"
#include <iostream>
#include "../../../item/material/Material.h"
#include "../../../entity/player/player.h"

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
		auto block = world.getBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z);
		const auto& material = Material::toMaterial((BlockId)block.m_id);
		m_pPlayer->addItem(material);

		world.updateChunk(m_digSpot.x, m_digSpot.y, m_digSpot.z);
		world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, BlockId::AIR);
		break;
	}
	case sf::Mouse::Button::Right: {
		auto& item = m_pPlayer->getHeldItems();
		auto& material = item.getMaterial();

		if (material.materialId == Material::ID::Nothing || item.getNumInStack() == 0) {
			return;
		}
		else {
			item.remove();
			world.updateChunk(m_digSpot.x, m_digSpot.y, m_digSpot.z);
			world.setBlock(m_digSpot.x, m_digSpot.y, m_digSpot.z, material.toBlockId());
			break;
		}

	}
	default:
		break;
	}
}
