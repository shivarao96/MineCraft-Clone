#include "LightForestBiome.h"
#include "../treeGeneration/TreeGeneration.h"

LightForestBiome::LightForestBiome(int seed):Biome(getNoiseParam(), 55, 50, seed) {

}
BlockId LightForestBiome::getTopBlock(Rand& rand)const {
    return rand.intInRange(0, 10) < 8 ?
        BlockId::GRASS :
        BlockId::DIRT;
}
void LightForestBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const {
    makeOakTree(chunk, rand, x, y, z);
}
NoiseParameters LightForestBiome::getNoiseParam() {
    NoiseParameters heightParams;
    heightParams.octaves = 5;
    heightParams.amplitude = 100;
    heightParams.smoothness = 195;
    heightParams.heightOffset = -30;
    heightParams.roughNess = 0.52;

    return heightParams;
}