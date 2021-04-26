#include "blockDataBase.h"

BlockDataBase::BlockDataBase(): m_textureAtlas("DefaultPack"){
	m_blocks[(int)BlockId::AIR]     = std::make_unique<DefaultBlock>("air");
	m_blocks[(int)BlockId::GRASS]   = std::make_unique<DefaultBlock>("grass");
	m_blocks[(int)BlockId::DIRT]    = std::make_unique<DefaultBlock>("dirt");
	m_blocks[(int)BlockId::STONE]   = std::make_unique<DefaultBlock>("stone");
	m_blocks[(int)BlockId::OAKBARK] = std::make_unique<DefaultBlock>("oakBark");
	m_blocks[(int)BlockId::OAKLEAF] = std::make_unique<DefaultBlock>("oakLeaf");
	m_blocks[(int)BlockId::SAND]    = std::make_unique<DefaultBlock>("sand");
	m_blocks[(int)BlockId::WATER]   = std::make_unique<DefaultBlock>("water");
	m_blocks[(int)BlockId::CACTUS]   = std::make_unique<DefaultBlock>("cactus");
	m_blocks[(int)BlockId::ROSE]   = std::make_unique<DefaultBlock>("rose");
	m_blocks[(int)BlockId::TALLGRASS]   = std::make_unique<DefaultBlock>("tallGrass");
	m_blocks[(int)BlockId::DEADPLANT]   = std::make_unique<DefaultBlock>("deadPlant");
}

BlockDataBase& BlockDataBase::get() {
	static BlockDataBase bdb;
	return bdb;
}

const BlockData& BlockDataBase::getBlockData(BlockId id) const {
	return m_blocks[(int)id]->getBlockData();
}
const BlockType& BlockDataBase::getBlockType(BlockId id) const {
	return *m_blocks[(int)id];
}