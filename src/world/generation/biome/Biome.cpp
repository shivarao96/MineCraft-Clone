#include "Biome.h"
#include "../treeGeneration/TreeGeneration.h"

GrassLandBiome::GrassLandBiome(int seed):m_noiseGenerator(seed)
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 80;
    heightParams.smoothness = 335;
    heightParams.heightOffset = -5;
    heightParams.roughNess = 0.56;
    m_noiseGenerator.setNoiseParameter(heightParams);
}

BlockId GrassLandBiome::getTopBlock(Rand& rand)
{
    return BlockId::GRASS;
}

void GrassLandBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    makeOakTree(chunk, rand, x, y, z);
}

int GrassLandBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_noiseGenerator.getHeight(x, z, chunkX, chunkZ);
}

int GrassLandBiome::getTreeFrequency()
{
    return 100;
}

LightForestBiome::LightForestBiome(int seed):m_noiseGenerator(seed)
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 120;
    heightParams.smoothness = 135;
    heightParams.heightOffset = -15;
    heightParams.roughNess = 0.52;
    m_noiseGenerator.setNoiseParameter(heightParams);
}

BlockId LightForestBiome::getTopBlock(Rand& rand)
{
    return rand.intInRange(0,10) > 8 ? BlockId::GRASS : BlockId::DIRT;
}

void LightForestBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    makeOakTree(chunk, rand, x, y, z);
}

int LightForestBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_noiseGenerator.getHeight(x, z, chunkX, chunkZ);
}

int LightForestBiome::getTreeFrequency()
{
    return 50;
}

DesertBiome::DesertBiome(int seed):m_noiseGenerator(seed)
{
    NoiseParameters heightParams;
    heightParams.octaves = 9;
    heightParams.amplitude = 70;
    heightParams.smoothness = 335;
    heightParams.heightOffset = 0;
    heightParams.roughNess = 0.53;
    m_noiseGenerator.setNoiseParameter(heightParams);
}

BlockId DesertBiome::getTopBlock(Rand& rand)
{
    return BlockId::SAND;
}

void DesertBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)
{
    makeOakTree(chunk, rand, x, y, z);
}

int DesertBiome::getHeight(int x, int z, int chunkX, int chunkZ)
{
    return m_noiseGenerator.getHeight(x,z,chunkX, chunkZ);
}

int DesertBiome::getTreeFrequency()
{
    return 200;
}
