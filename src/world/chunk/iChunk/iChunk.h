#pragma once

class ChunkBlock;

struct IChunk {
	virtual void setBlock(int x, int y, int z, ChunkBlock block) = 0;
	virtual ChunkBlock getBlock(int x, int y, int z) const       = 0;
};