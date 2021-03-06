#pragma once

#include "chunk/iChunk/iChunk.h"
#include "chunk/chunk.h"
#include <vector>
#include "./chunk/chunkManager/chunkManager.h"
#include <unordered_set>

class MainRenderer;

class World
{
public:
	World();
	void renderWorld(MainRenderer& renderer);
	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);
	//void editBlock(int x, int y, int z, ChunkBlock block);
	//void addBlock(const sf::Vector2i& newPos);
private:
	//std::vector<Chunk> m_chunks;
	//std::vector<Chunk*> m_changedChunks;
	ChunkManager m_chunkManager;
	std::unordered_set<sf::Vector3i> m_rebuildChunks;
};

