#include "Biome.h"

Biome::Biome(const NoiseParameters& noiseParam, int treeFrequency, int plantFrequency, int seed)
    :m_noiseGenerator(seed)
    ,m_treeFrequency(treeFrequency)
    ,m_plantFrequency(plantFrequency)
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

int Biome::getPlantFrequency() const
{
    return m_plantFrequency;
}
