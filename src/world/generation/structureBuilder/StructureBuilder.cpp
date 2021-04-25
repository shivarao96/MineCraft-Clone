#include "StructureBuilder.h"
#include "../../chunk/chunk.h"

void StructureBuilder::build(Chunk& chunk)
{
	for (auto& block : m_blocks) {
		chunk.setBlock(block.x, block.y, block.z, block.id);
	}
}

void StructureBuilder::makeColumn(int x, int z, int yStart, int height, BlockId block)
{
	for (int y = yStart; y < yStart + height; y++) {
		m_blocks.emplace_back(block, x, y, z);
	}
}

void StructureBuilder::fill(int y, int xStart, int xEnd, int zStart, int zEnd, BlockId block)
{
	for (int x = xStart; x < xEnd; x++) {
		for (int z = zStart; z < zEnd; z++) {
			m_blocks.emplace_back(block, x, y, z);
		}
	}
}

void StructureBuilder::addBlock(int x, int y, int z, BlockId block)
{
	m_blocks.emplace_back(block, x,y,z );
}
