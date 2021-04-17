#pragma once

class ChunkBlock;

/*
* abstract class to implement set and get action on a block
*/
struct IChunk {
	virtual void setBlock(int x, int y, int z, ChunkBlock block) = 0;
	virtual ChunkBlock getBlock(int x, int y, int z) const       = 0;
};