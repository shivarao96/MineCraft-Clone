#pragma once

/*
BlockDataBase contains the info about all the block info
it is a singleton class.
*/

#include <array>
#include "../BlockId.h"
#include "../blockType/blockType.h"
#include "../../../utility/singleton.h";
#include "../../../texture/textureAtlas/textureAtlas.h"

class BlockDataBase: public Singleton
{	
public:
	static BlockDataBase& get(); // get singular instance

	const BlockData& getBlockData(BlockId id) const; // get blockdata based on blockid(air. dirt...etc)
	const BlockType& getBlockType(BlockId id) const; // get blocktype based on blockid(air. dirt...etc)

	TextureAtlas m_textureAtlas;
private:
	BlockDataBase();

	std::array<
		std::unique_ptr<BlockType>,
		(unsigned)BlockId::NUM_TYPES
	> m_blocks;	
};

