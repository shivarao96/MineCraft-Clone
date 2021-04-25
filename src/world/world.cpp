#include "world.h"
#include "Block/chunkBlock/chunkBlock.h"
#include "worldConstant.h"
#include "../math/vector2XZ/vector2XZ.h"
#include "../entity/camera/camera.h"
#include <iostream>
#include <mutex>

namespace WorldSpace{
	constexpr int render_distance = 16;
	constexpr int gravity = -3;
	std::mutex m_mutex;
}

World::World(const Camera& cam)
	:m_chunkManager(*this) 
	//, m_thread([&] {
	//	while (m_isRunning) {
	//		loadChunks(cam);
	//	}
	//})
{}

World::~World()
{
	//m_isRunning = false;
	//m_thread.join();
}

void World::update(const Camera& cam) {

	for (auto& event : m_events) {
		event->handleWorld(*this);
	}
	m_events.clear();


	updateChunks(); // updating the chunks which are edited by user.
	
	//loadChunks(cam);

	// !IMPORTANT !IMPORTANT !IMPORTANT
	// hide below code when loadchunks is uncommented.
	for (int x = 0; x < WorldSpace::render_distance; x++) { 
		for (int z = 0; z < WorldSpace::render_distance; z++) {
			if (m_chunkManager.makeMesh(x, z)) {
				return;
			}
		}
	}
}

void World::loadChunks(const Camera& cam)
{
	
	bool isMeshLoaded = false;
	int camX = cam.m_position.x / CHUNK_SIZE;
	int camZ = cam.m_position.z / CHUNK_SIZE;
	for (int i = 0; i < m_loadDistance; i++) {
		int minX = std::max(camX - i, 0);
		int minZ = std::max(camZ - i, 0);
		int maxX = camX + i;
		int maxZ = camZ + i;

		for (int x = minX; x < maxX; ++x) {
			for (int z = minZ; z < maxZ; ++z) {
				WorldSpace::m_mutex.lock();
				if (m_chunkManager.makeMesh(x, z)) {
					isMeshLoaded = true;
					WorldSpace::m_mutex.unlock();
					break;
				}
				WorldSpace::m_mutex.unlock();
			}
			if (isMeshLoaded) break;
		}
		if (isMeshLoaded) break;
	}

	if (!isMeshLoaded)m_loadDistance++;
	if (m_loadDistance >= WorldSpace::render_distance) m_loadDistance = 2;
}


void World::renderWorld(MainRenderer& renderer, const Camera& cam) {
	
	auto& chunks = m_chunkManager.getChunks();
	/*
	* Uncomment the code when multithreading is implemented
	* 
			WorldSpace::m_mutex.lock();
			for (auto itr = chunks.begin(); itr != chunks.end();) {

				Chunk& chunk = itr->second;

				int camX = cam.m_position.x;
				int camZ = cam.m_position.z;

				int minX = (camX / CHUNK_SIZE) - WorldSpace::render_distance;
				int minZ = (camZ / CHUNK_SIZE) - WorldSpace::render_distance;
				int maxX = (camX / CHUNK_SIZE) + WorldSpace::render_distance;
				int maxZ = (camZ / CHUNK_SIZE) + WorldSpace::render_distance;

				auto location = chunk.getChunkLocation();
				if (location.x > maxX || location.y > maxZ || location.x < minX || location.y < minZ) { // taboo
					itr = chunks.erase(itr);
					continue;
				}
				else {
					chunk.drawChunks(renderer, cam);
					itr++;
				}
		
			}
			WorldSpace::m_mutex.unlock();
	*/
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