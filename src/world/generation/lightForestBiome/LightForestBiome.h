#pragma once
#ifndef __LIGHT_FOREST_BIOME__
#define __LIGHT_FOREST_BIOME__
#include "../biome/Biome.h"

class LightForestBiome final: public Biome
{
public:
	LightForestBiome(int seed);
	BlockId getTopBlock(Rand& rand)const;
	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
private:
	NoiseParameters getNoiseParam();
};

#endif // !__LIGHT_FOREST_BIOME__



