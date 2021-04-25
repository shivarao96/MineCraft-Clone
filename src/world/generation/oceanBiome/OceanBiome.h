#pragma once
#ifndef __OCEAN_BIOME__
#define __OCEAN_BIOME__

#include "../biome/Biome.h"

class OceanBiome final: public Biome
{
public:
	OceanBiome(int seed);
	BlockId getTopBlock(Rand& rand)const;
	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
private:
	NoiseParameters getNoiseParam();
};

#endif // ! __OCEAN_BIOME__




