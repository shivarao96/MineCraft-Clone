#include "GrassLandBiome.h"
#include "../treeGeneration/TreeGeneration.h"

GrassLandBiome::GrassLandBiome(int seed):Biome(getNoiseParam(), 100, seed)
{}

BlockId GrassLandBiome::getTopBlock(Rand & rand) const
{
	return BlockId::GRASS;
}

void GrassLandBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) const
{
	makeOakTree(chunk, rand, x, y, z);
}

NoiseParameters GrassLandBiome::getNoiseParam()
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 90;
    heightParams.smoothness = 335;
    heightParams.heightOffset = -5;
    heightParams.roughNess = 0.50;
    return heightParams;
}
