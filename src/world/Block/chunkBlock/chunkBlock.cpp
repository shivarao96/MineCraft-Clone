#include "chunkBlock.h"
#include "../blockDataBase/blockDataBase.h"

ChunkBlock::ChunkBlock(block_t id):m_id(id) {}
ChunkBlock::ChunkBlock(BlockId id):m_id(static_cast<block_t>(id)) {}

const BlockData& ChunkBlock::getBlockData() const {
	return BlockDataBase::get().getBlockData((BlockId)m_id);
}
const BlockType& ChunkBlock::getBlockType() const {
	return BlockDataBase::get().getBlockType((BlockId)m_id);
}