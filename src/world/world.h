#pragma once

#include "chunk/iChunk/iChunk.h"
#include "chunk/chunk.h"
#include <vector>
#include "./chunk/chunkManager/chunkManager.h"
#include <unordered_set>

class MainRenderer;
class Camera;

class World
{
public:
	World();
	void renderWorld(MainRenderer& renderer);
	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);
	void update(const Camera& cam);
private:

	ChunkManager m_chunkManager;
	std::unordered_set<sf::Vector3i> m_rebuildChunks;
};

