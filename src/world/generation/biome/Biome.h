#pragma once
#ifndef __BIOME__
#define __BIOME__

#include "../../../utility/randomGenerator/random.h"
#include "../../Block/BlockId.h"
#include "../../../utility/noiseGenerator/noiseGenerator.h"

class Chunk;

using Rand = Random<std::minstd_rand>;

struct Biome {
public:
	Biome(const NoiseParameters& noiseParam, int treeFrequency, int plantFrequency, int seed);
	virtual BlockId getTopBlock(Rand& rand)const = 0;
	virtual BlockId getPlant(Rand& rand)const = 0;
	virtual void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const = 0;
	
	int getHeight(int x, int z, int chunkX, int chunkZ)const;
	int getTreeFrequency()const;
	int getPlantFrequency() const;
protected:
	virtual NoiseParameters getNoiseParam() = 0;
private:
	NoiseGenerator m_noiseGenerator;
	int m_treeFrequency;
	int m_plantFrequency;
};


#endif // !__BIOME__


