#include "TreeGeneration.h"
#include "../../chunk/chunk.h"
#include "../structureBuilder/StructureBuilder.h"

void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) {
	
	StructureBuilder builder;
	
	int height = rand.intInRange(4, 7);
	int leafSize = 2;
	int newY = height + y;

	builder.fill(newY, x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockId::OAKLEAF);
	builder.fill(newY - 1, x - leafSize, x + leafSize, z - leafSize, z + leafSize, BlockId::OAKLEAF);

	for (int zNew = -leafSize + 1; zNew <= leafSize - 1; zNew++) {
		builder.addBlock(x, newY + 1, z + zNew, BlockId::OAKLEAF);
	}

	for (int xNew = -leafSize + 1; xNew <= leafSize - 1; xNew++) {
		builder.addBlock(x + xNew, newY + 1, z, BlockId::OAKLEAF);
	}
	
	builder.makeColumn(x, z, y, height, BlockId::OAKBARK);
	builder.build(chunk);
}

void makePamTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
	StructureBuilder builder;

	int height = rand.intInRange(7, 9);
	int diameter = rand.intInRange(4, 6);

	for (int xLeaf = -diameter; xLeaf < diameter; xLeaf++)
	{
		builder.addBlock(xLeaf + x, y + height, z, BlockId::OAKLEAF);
	}
	for (int zLeaf = -diameter; zLeaf < diameter; zLeaf++)
	{
		builder.addBlock(x, y + height, zLeaf + z, BlockId::OAKLEAF);
	}

	builder.addBlock(x, y + height - 1, z + diameter, BlockId::OAKLEAF);
	builder.addBlock(x, y + height - 1, z - diameter, BlockId::OAKLEAF);
	builder.addBlock(x + diameter, y + height - 1, z, BlockId::OAKLEAF);
	builder.addBlock(x - diameter, y + height - 1, z, BlockId::OAKLEAF);
	builder.addBlock(x, y + height + 1, z, BlockId::OAKLEAF);

	builder.makeColumn(x, z, y, height, BlockId::OAKBARK);
	builder.build(chunk);
}

void makeCactusTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) {
	for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++) {
		chunk.setBlock(x, y + trunkY, z, BlockId::CACTUS);
	}
}