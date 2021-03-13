#include "world.h"
#include "Block/chunkBlock/chunkBlock.h"
#include "worldConstant.h"
#include "../math/vector2XZ/vector2XZ.h"
#include <iostream>

namespace WorldSpace{
	constexpr int world_size = 8;

	bool isWorldOutOfBound(const VectorXZ& vecXZ) {
		if (vecXZ.x < 0) return true;
		if (vecXZ.z < 0) return true;
		if (vecXZ.x >= WorldSpace::world_size) return true;
		if (vecXZ.z >= WorldSpace::world_size) return true;

		return false;
	}
}

World::World():m_chunkManager(*this) {}

void World::update(const Camera& cam) {

	for (auto& event : m_events) {
		event->handleWorld(*this);
	}
	m_events.clear();

	for (int x = 0; x < WorldSpace::world_size; x++) {
		for (int z = 0; z < WorldSpace::world_size; z++) {
			if (!m_chunkManager.chunkExistAt(x, z)) {
				m_chunkManager.loadChunk(x, z);
			}
			if (m_chunkManager.makeMesh(x, z)) {
				return;
			}
		}
	}
}

void World::renderedUpdatedSections() {
	for (auto& location : m_rebuildChunks) {
		ChunkSection& section = m_chunkManager.getChunk(location.x, location.z).getSection(location.y);
		section.makeMesh();
		section.bufferMesh();
	}
	m_rebuildChunks.clear();
}

void World::renderWorld(MainRenderer& renderer) {
	
	auto& chunks = m_chunkManager.getChunks();
	for (auto& chunk: chunks) {
		chunk.second.drawChunks(renderer);
	}
}
void World::setBlock(int x, int y, int z, ChunkBlock block) {
	if (y <= 0)
		return;

	auto bP = getBlock(x, z);
	auto cP = getChunk(x, z);

	if (WorldSpace::isWorldOutOfBound(cP)) {
		return;
	}

	m_chunkManager.getChunk(cP.x, cP.z).setBlock(bP.x, y, bP.z, block);
	
	if (m_chunkManager.getChunk(cP.x, cP.z).hasLoaded()) {
		std::cout << "rebuild" << std::endl;
		m_rebuildChunks.emplace(cP.x, y / CHUNK_SIZE, cP.z);
	}
	renderedUpdatedSections();
}
ChunkBlock World::getBlock(int x, int y, int z) {
	auto bP = getBlock(x, z);
	auto cP = getChunk(x, z);
	
	if (WorldSpace::isWorldOutOfBound(cP)) {
		return BlockId::AIR;
	}
	return m_chunkManager.getChunk(cP.x, cP.z).getBlock(bP.x, y, bP.z);
}

const ChunkManager& World::getChunkManager() const {
	return m_chunkManager;
}

VectorXZ World::getBlock(int x, int z) {
	return { x % CHUNK_SIZE, z % CHUNK_SIZE };
}

VectorXZ World::getChunk(int x, int z) {
	return { x / CHUNK_SIZE, z / CHUNK_SIZE };
}