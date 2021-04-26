#include "DesertBiome.h"
#include "../treeGeneration/TreeGeneration.h"

DesertBiome::DesertBiome(int seed) :Biome(getNoiseParam(), 175,50, seed) {

}
BlockId DesertBiome::getTopBlock(Rand& rand)const {
    return BlockId::SAND;
}
void DesertBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const {
    makeCactusTree(chunk, rand, x, y, z);
}
NoiseParameters DesertBiome::getNoiseParam() {
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 80;
    heightParams.smoothness = 335;
    heightParams.heightOffset = 0;
    heightParams.roughNess = 0.53;

    return heightParams;
}