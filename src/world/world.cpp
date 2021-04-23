#include "world.h"
#include "Block/chunkBlock/chunkBlock.h"
#include "worldConstant.h"
#include "../math/vector2XZ/vector2XZ.h"
#include "../entity/camera/camera.h"
#include <iostream>

namespace WorldSpace{
	constexpr int render_distance = 16;
	constexpr int gravity = -3;
}

World::World():m_chunkManager(*this) {}

void World::update(const Camera& cam) {

	for (auto& event : m_events) {
		event->handleWorld(*this);
	}
	m_events.clear();
	updateChunks(); // updating the chunks which are edited by user.
	for (int x = 0; x < WorldSpace::render_distance; x++) { 
		for (int z = 0; z < WorldSpace::render_distance; z++) {
			if (m_chunkManager.makeMesh(x, z)) {
				return;
			}
		}
	}
}

void World::renderWorld(MainRenderer& renderer, const Camera& cam) {
	
	auto& chunks = m_chunkManager.getChunks();
	for (auto& chunk: chunks) {
		chunk.second.drawChunks(renderer, cam);
	}
}

void World::setBlock(int x, int y, int z, ChunkBlock block) {
	if (y <= 0)
		return;

	auto bP = getBlock(x, z);
	auto cP = getChunk(x, z);

	m_chunkManager.getChunk(cP.x, cP.z).setBlock(bP.x, y, bP.z, block);
}

ChunkBlock World::getBlock(int x, int y, int z) {
	auto bP = getBlock(x, z);
	auto cP = getChunk(x, z);
	
	return m_chunkManager.getChunk(cP.x, cP.z).getBlock(bP.x, y, bP.z);
}

ChunkManager& World::getChunkManager() {
	return m_chunkManager;
}

VectorXZ World::getBlock(int x, int z) {
	return { x % CHUNK_SIZE, z % CHUNK_SIZE };
}

VectorXZ World::getChunk(int x, int z) {
	return { x / CHUNK_SIZE, z / CHUNK_SIZE };
}

void World::updateChunks() {
	for (auto chunk : m_chunkSectionUpdates) {
		ChunkSection& c = *chunk.second;
		c.makeMesh();
		c.bufferMesh();
	}
	m_chunkSectionUpdates.clear();
}

void World::updateChunk(int blockX, int blockY, int blockZ) {
	
	auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, ChunkSection& chunksection) {
		m_chunkSectionUpdates.emplace(key, &chunksection);
	}; // short-hand function for adding chunk section into update

	auto cp = getChunk(blockX, blockZ); // get chunk
	auto cy = blockY / CHUNK_SIZE; // get the current block in y-axis

	addChunkToUpdateBatch({ cp.x, cy, cp.z }, m_chunkManager.getChunk(cp.x, cp.z).getSection(cy)); // add the chunkSection that need to be updated

	auto sectionBlockXZ = getBlock(blockX, blockZ);
	auto sectionBlockY  = blockY % CHUNK_SIZE;

	// for checking the chunksection in x-axis
	if (sectionBlockXZ.x == 0) { // if it is 0th index then update the previous section
		sf::Vector3i key(cp.x - 1, cy, cp.z);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}
	else if (sectionBlockXZ.x == CHUNK_SIZE - 1) { // if last chunksection then update the next chunksection 
		sf::Vector3i key(cp.x + 1, cy, cp.z);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}

	// for checking the chunksection in y-axis
	if (sectionBlockY == 0) { // if it is 0th index then update the previous section
		sf::Vector3i key(cp.x, cy - 1, cp.z);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}
	else if (sectionBlockY == CHUNK_SIZE - 1) { // if last chunksection then update the next chunksection 
		sf::Vector3i key(cp.x, cy + 1, cp.z);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}

	// for checking the chunksection in z-axis
	if (sectionBlockXZ.z == 0) { // if it is 0th index then update the previous section
		sf::Vector3i key(cp.x, cy, cp.z - 1);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}
	else if (sectionBlockXZ.z == CHUNK_SIZE - 1) {// if last chunksection then update the next chunksection
		sf::Vector3i key(cp.x, cy, cp.z + 1);
		addChunkToUpdateBatch(key, m_chunkManager.getChunk(key.x, key.z).getSection(key.y));
	}
}