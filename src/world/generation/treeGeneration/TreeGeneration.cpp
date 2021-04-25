#include "TreeGeneration.h"

#include "../../chunk/chunk.h"

void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) {
	int height = rand.intInRange(4, 7);
	for (int trunkY = 0; trunkY < height; trunkY++) {
		chunk.setBlock(x, y + trunkY, z, BlockId::OAKBARK);
	}

	for (int lx = -2; lx < 2; lx++) {
		for (int ly = -2; ly < 2; ly++) {
			for (int lz = -2; lz < 2; lz++) {
				chunk.setBlock(lx + x, ly + y + height, lz + z, BlockId::OAKLEAF);
			}
		}
	}
}

void makeCactusTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) {
	for (int trunkY = 0; trunkY < rand.intInRange(4, 7); trunkY++) {
		chunk.setBlock(x, y + trunkY, z, BlockId::CACTUS);
	}
}