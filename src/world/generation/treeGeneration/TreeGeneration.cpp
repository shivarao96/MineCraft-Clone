#include "TreeGeneration.h"

#include "../../chunk/chunk.h"

void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) {
	for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++) {
		chunk.setBlock(x, y + trunkY, z, BlockId::OAKBARK);
	}
}