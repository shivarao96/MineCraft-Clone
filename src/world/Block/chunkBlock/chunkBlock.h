#pragma once

/*
	Following class return the texture based on id
	extension or wrapper to the block data and block type
*/

#include "../BlockId.h"

class BlockDataHolder;
class BlockType;

class ChunkBlock
{
public:
	ChunkBlock() = default;
	ChunkBlock(block_t id);
	ChunkBlock(BlockId id);

	const BlockDataHolder& getBlockData() const;
	const BlockType& getBlockType() const;

	bool operator==(ChunkBlock b) {
		return m_id == b.m_id;
	}

	bool operator!=(ChunkBlock b) {
		return m_id != b.m_id;
	}

	block_t m_id = 0;
};

