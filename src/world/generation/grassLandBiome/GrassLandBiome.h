#pragma once
#ifndef __GRASS_LAND_BIOME__
#define __GRASS_LAND_BIOME__

#include "../biome/Biome.h"

class GrassLandBiome final: public Biome {
public:
	GrassLandBiome(int seed);
	BlockId getTopBlock(Rand& rand)const;
	BlockId getPlant(Rand& rand)const;
	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
private:
	NoiseParameters getNoiseParam();
};
#endif // !__GRASS_LAND_BIOME__

