#include "chunkManager.h"

#include "../../world.h"
#include <iostream>

ChunkManager::ChunkManager(World& world):m_world(&world) {

}
Chunk& ChunkManager::getChunk(int x, int z) {
	if (!chunkExistAt(x,z)) {
		VectorXZ key{ x,z };
		Chunk chunk {*m_world, {x,z}};
		m_chunkMap.emplace(key, std::move(chunk));
	}
	return m_chunkMap.at({ x,z });
}

ChunkMap& ChunkManager::getChunks() {
	return m_chunkMap;
}

bool ChunkManager::makeMesh(int x, int z) {
	for (int nx = -1; nx <= 1; nx++) {// need to remove
		for (int nz = -1; nz <= 1; nz++) {
			getChunk(x + nx, z + nz).load();
		}
	}
	return getChunk(x, z).makeMesh();
}

bool ChunkManager::chunkLoadedAt(int x, int z) const
{
	if (!chunkExistAt(x, z))
		return false;

	return m_chunkMap.at({x, z}).hasLoaded();
}
bool ChunkManager::chunkExistAt(int x, int z) const
{
	return m_chunkMap.find({x,z}) != m_chunkMap.end();
}

void ChunkManager::loadChunk(int x, int z)
{
	getChunk(x, z).load();
}

void ChunkManager::unLoadChunk(int x, int z)
{
	// @TODO saving chunks into the file.
}
