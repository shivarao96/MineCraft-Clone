#pragma once
#ifndef __DESERT_BIOME__
#define __DESERT_BIOME__

#include "../biome/Biome.h"

class DesertBiome final: public Biome
{
public:
	DesertBiome(int seed);
	BlockId getTopBlock(Rand& rand)const;
	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
	BlockId getPlant(Rand& rand) const
	{
		return rand.intInRange(0, 5) < 3 ? BlockId::ROSE : BlockId::TALLGRASS;
	}
private:
	NoiseParameters getNoiseParam();
};

#endif // !__DESERT_BIOME__


