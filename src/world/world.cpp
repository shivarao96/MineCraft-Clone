#include "world.h"
#include "Block/chunkBlock/chunkBlock.h"
#include "worldConstant.h"
#include <iostream>

namespace WorldSpace{
	constexpr int world_size = 8;

	struct VectorXZ
	{
		int x;
		int z;
	};

	VectorXZ getBlock(int x, int z) {
		return { x % CHUNK_SIZE, z % CHUNK_SIZE };
	}

	VectorXZ getChunk(int x, int z) {
		return { x / CHUNK_SIZE, z / CHUNK_SIZE };
	}

	bool isWorldOutOfBound(VectorXZ vecXZ) {
		if (vecXZ.x < 0) return true;
		if (vecXZ.z < 0) return true;
		if (vecXZ.x >= WorldSpace::world_size) return true;
		if (vecXZ.z >= WorldSpace::world_size) return true;

		return false;
	}
}
World::World() {
	for (int x = 0; x < WorldSpace::world_size; x++) {
		for (int z = 0; z < WorldSpace::world_size; z++) {
			m_chunks.emplace_back(*this, sf::Vector2i(x, z));
		}
	}
	for (auto& chunk : m_chunks) {
		chunk.makeMesh();
	}
}
void World::renderWorld(MainRenderer& renderer) {
	
	for (auto& changedChunk : m_changedChunks) {
		changedChunk->makeMesh();
	}
	m_changedChunks.clear();
	
	for (auto& chunk : m_chunks) {
		chunk.drawChunks(renderer);
	}
}
void World::setBlock(int x, int y, int z, ChunkBlock block) {
	WorldSpace::VectorXZ bP = WorldSpace::getBlock(x, z);
	WorldSpace::VectorXZ cP = WorldSpace::getChunk(x, z);

	if (WorldSpace::isWorldOutOfBound(cP)) {
		return;
	}

	m_chunks.at(cP.x * WorldSpace::world_size + cP.z).setBlock(bP.x, y, bP.z, block);
}
ChunkBlock World::getBlock(int x, int y, int z) const {
	WorldSpace::VectorXZ bP = WorldSpace::getBlock(x, z);
	WorldSpace::VectorXZ cP = WorldSpace::getChunk(x, z);
	
	if (WorldSpace::isWorldOutOfBound(cP)) {
		return BlockId::AIR;
	}
	return m_chunks.at(cP.x * WorldSpace::world_size + cP.z).getBlock(bP.x, y, bP.z);
}
void World::editBlock(int x, int y, int z, ChunkBlock block) {
	WorldSpace::VectorXZ cP = WorldSpace::getChunk(x, z);

	if (WorldSpace::isWorldOutOfBound(cP)) {
		return;
	}

	setBlock(x, y, z, block);
	m_changedChunks.push_back(&m_chunks.at(cP.x * WorldSpace::world_size + cP.z));
	
	if (((x + 1) % CHUNK_SIZE) == 0) {
		int xSize = (x + 1) / CHUNK_SIZE;
		if (xSize < WorldSpace::world_size ) {
			m_changedChunks.push_back(&m_chunks.at(xSize * WorldSpace::world_size + cP.z));
		}
	}
	if (((z + 1) % CHUNK_SIZE) == 0) {
		int zSize = (z + 1) / CHUNK_SIZE;
		if (zSize < WorldSpace::world_size) {
			m_changedChunks.push_back(&m_chunks.at(cP.x * WorldSpace::world_size + zSize));
		}
	}
	
}
void World::addBlock(const sf::Vector2i& newPos) {
	m_chunks.emplace_back(*this, newPos);
}