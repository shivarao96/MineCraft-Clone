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
	void editBlock(int x, int y, int z, ChunkBlock block);
	void addBlock(const sf::Vector2i& newPos);
private:
	std::vector<Chunk> m_chunks;
	std::vector<Chunk*> m_changedChunks;
};

