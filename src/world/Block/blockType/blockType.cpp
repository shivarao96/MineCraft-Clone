#include "blockType.h"


BlockType::BlockType(const std::string& fileName)
	: m_blockData(fileName)
{

}

const BlockData& BlockType::getBlockData() const 
{
	return m_blockData;
}