#pragma once

#include "../BlockId.h"

class BlockDataHolder;
class BlockType;

/*
	Following class helps us to query the block type info based
	on block id.
*/

class ChunkBlock
{
public:

	ChunkBlock() = default;
	ChunkBlock(block_t id); // sets up the block id
	ChunkBlock(BlockId id); // sets up the block id

	/*
	* Method(ChunkBlock): get the block BlockDataHolder 
	*	info from the BlockDataBase(go through the def for more
	*	info)
	*/
	const BlockDataHolder& getBlockData() const;
	/*
	* Method(ChunkBlock): get the block BlockType
	*/
	const BlockType& getBlockType() const;

	bool operator==(ChunkBlock b) {
		return m_id == b.m_id;
	}

	bool operator!=(ChunkBlock b) {
		return m_id != b.m_id;
	}

	block_t m_id = 0;
};

