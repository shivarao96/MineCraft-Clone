#include "OceanBiome.h"
#include "../treeGeneration/TreeGeneration.h"

OceanBiome::OceanBiome(int seed) :Biome(getNoiseParam(), 50,50, seed)
{}

BlockId OceanBiome::getTopBlock(Rand& rand) const
{
    return BlockId::GRASS;
}

void OceanBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z) const
{
    rand.intInRange(0,5) < 3 ? makePamTree(chunk, rand, x, y, z) :
        makeCactusTree(chunk, rand, x, y, z);
}

NoiseParameters OceanBiome::getNoiseParam()
{
    NoiseParameters heightParams;
    heightParams.octaves = 7;
    heightParams.amplitude = 43;
    heightParams.smoothness = 55;
    heightParams.heightOffset = 0;
    heightParams.roughNess = 0.50;

    return heightParams;
}
