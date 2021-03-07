#include "world.h"
#include "Block/chunkBlock/chunkBlock.h"
#include "worldConstant.h"
#include "../math/vector2XZ/vector2XZ.h"

namespace WorldSpace{
	constexpr int world_size = 8;

	VectorXZ getBlock(int x, int z) {
		return { x % CHUNK_SIZE, z % CHUNK_SIZE };
	}

	VectorXZ getChunk(int x, int z) {
		return { x / CHUNK_SIZE, z / CHUNK_SIZE };
	}

	bool isWorldOutOfBound(const VectorXZ& vecXZ) {
		if (vecXZ.x < 0) return true;
		if (vecXZ.z < 0) return true;
		if (vecXZ.x >= WorldSpace::world_size) return true;
		if (vecXZ.z >= WorldSpace::world_size) return true;

		return false;
	}
}
World::World():m_chunkManager(*this) {
	for (int x = 0; x < WorldSpace::world_size; x++) {
		for (int z = 0; z < WorldSpace::world_size; z++) {
			m_chunkManager.getChunk(x, z).load();
		}
	}
}

void World::update(const Camera& cam) {
	for (int x = 0; x < WorldSpace::world_size; x++) {
		for (int z = 0; z < WorldSpace::world_size; z++) {
			if (m_chunkManager.makeMesh(x, z)) {
				return;
			}
		}
	}
}

void World::renderWorld(MainRenderer& renderer) {
	
	for (auto& location : m_rebuildChunks) {
		ChunkSection& section = m_chunkManager.getChunk(location.x, location.z).getSection(location.y);
		section.makeMesh();
	}
	m_rebuildChunks.clear();
	const auto& chunks = m_chunkManager.getChunks();
	for (auto& chunk: chunks) {
		chunk.second.drawChunks(renderer);
	}
}
void World::setBlock(int x, int y, int z, ChunkBlock block) {
	if (y == 0)
		return;

	auto bP = WorldSpace::getBlock(x, z);
	auto cP = WorldSpace::getChunk(x, z);

	if (WorldSpace::isWorldOutOfBound(cP)) {
		return;
	}

	auto& c = m_chunkManager.getChunk(cP.x, cP.z);
	c.setBlock(bP.x, y, bP.z, block);
	if (c.hasLoaded()) {
		m_rebuildChunks.emplace(cP.x, y / CHUNK_SIZE, cP.z);
	}
}
ChunkBlock World::getBlock(int x, int y, int z) {
	auto bP = WorldSpace::getBlock(x, z);
	auto cP = WorldSpace::getChunk(x, z);
	
	if (WorldSpace::isWorldOutOfBound(cP)) {
		return BlockId::AIR;
	}
	return m_chunkManager.getChunk(cP.x, cP.z).getBlock(bP.x, y, bP.z);
}