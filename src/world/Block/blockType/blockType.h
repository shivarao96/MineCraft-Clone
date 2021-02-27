#pragma once

/*
 Following class is same as blockData
*/

#include "../blockData/blockData.h"

class BlockType: public NonCopyable
{
public:
	BlockType(const std::string& fileName);
	
	const BlockData& getBlockData() const;
private:
	BlockData m_blockData;
};

class DefaultBlock : public BlockType {
public:
	DefaultBlock(const std::string& fileName): BlockType(fileName) 
	{}
};

