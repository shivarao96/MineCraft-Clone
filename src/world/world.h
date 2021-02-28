#pragma once

#include "chunk/iChunk/iChunk.h"
#include "chunk/chunk.h"
#include <vector>

class MainRenderer;

class World: public IChunk
{
public:
	World();
	void renderWorld(MainRenderer& renderer);
	void setBlock(int x, int y, int z, ChunkBlock block)override;
	ChunkBlock getBlock(int x, int y, int z)const override;
private:
	std::vector<Chunk> m_chunks;
};

