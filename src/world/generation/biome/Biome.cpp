#include "Biome.h"
//#include "../treeGeneration/TreeGeneration.h"
//
//GrassLandBiome::GrassLandBiome(int seed):m_noiseGenerator(seed)
//{
//    NoiseParameters heightParams;
//    heightParams.octaves = 9;
//    heightParams.amplitude = 90;
//    heightParams.smoothness = 335;
//    heightParams.heightOffset = -5;
//    heightParams.roughNess = 0.50;
//    m_noiseGenerator.setNoiseParameter(heightParams);
//}
//
//BlockId GrassLandBiome::getTopBlock(Rand& rand)const
//{
//    return BlockId::GRASS;
//}
//
//void GrassLandBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const
//{
//    makeOakTree(chunk, rand, x, y, z);
//}
//
//int GrassLandBiome::getHeight(int x, int z, int chunkX, int chunkZ)const
//{
//    return m_noiseGenerator.getHeight(x, z, chunkX, chunkZ);
//}
//
//int GrassLandBiome::getTreeFrequency()const
//{
//    return 100;
//}
//
//LightForestBiome::LightForestBiome(int seed):m_noiseGenerator(seed)
//{
//    NoiseParameters heightParams;
//    heightParams.octaves = 9;
//    heightParams.amplitude = 100;
//    heightParams.smoothness = 195;
//    heightParams.heightOffset = -15;
//    heightParams.roughNess = 0.50;
//    m_noiseGenerator.setNoiseParameter(heightParams);
//}
//
//BlockId LightForestBiome::getTopBlock(Rand& rand)const
//{
//    return rand.intInRange(0,10) > 8 ? BlockId::GRASS : BlockId::DIRT;
//}
//
//void LightForestBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const
//{
//    makeOakTree(chunk, rand, x, y, z);
//}
//
//int LightForestBiome::getHeight(int x, int z, int chunkX, int chunkZ)const
//{
//    return m_noiseGenerator.getHeight(x, z, chunkX, chunkZ);
//}
//
//int LightForestBiome::getTreeFrequency()const
//{
//    return 50;
//}
//
//DesertBiome::DesertBiome(int seed):m_noiseGenerator(seed)
//{
//    NoiseParameters heightParams;
//    heightParams.octaves = 9;
//    heightParams.amplitude = 80;
//    heightParams.smoothness = 335;
//    heightParams.heightOffset = 0;
//    heightParams.roughNess = 0.53;
//    m_noiseGenerator.setNoiseParameter(heightParams);
//}
//
//BlockId DesertBiome::getTopBlock(Rand& rand)const
//{
//    return BlockId::SAND;
//}
//
//void DesertBiome::makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const
//{
//    makeOakTree(chunk, rand, x, y, z);
//}
//
//int DesertBiome::getHeight(int x, int z, int chunkX, int chunkZ)const
//{
//    return m_noiseGenerator.getHeight(x,z,chunkX, chunkZ);
//}
//
//int DesertBiome::getTreeFrequency()const
//{
//    return 200;
//}

Biome::Biome(const NoiseParameters& noiseParam, int treeFrequency, int seed)
    :m_noiseGenerator(seed)
    ,m_treeFrequency(treeFrequency)
{
    m_noiseGenerator.setNoiseParameter(noiseParam);
}

int Biome::getHeight(int x, int z, int chunkX, int chunkZ) const
{
    return m_noiseGenerator.getHeight(x,z,chunkX,chunkZ);
}

int Biome::getTreeFrequency() const
{
    return m_treeFrequency;
}
