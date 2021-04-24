#pragma once
#ifndef __TERRAIN_GENERATION__
#define __TERRAIN_GENERATION__

#include <array>
#include "../worldConstant.h"
#include "../../utility/noiseGenerator/noiseGenerator.h"
#include "../../utility/randomGenerator/random.h"

class Chunk;

class TerrainGeneration
{
public:
	TerrainGeneration();
	void generateTerrainFor(Chunk& chunk);
private:
	void setBlocks(int maxHeight);
	void setTopBlock(int x, int y, int z);

	void getHeightMap();
	void getBiomeMap();

	std::array<int, CHUNK_AREA> m_heightMap;
	std::array<int, CHUNK_AREA> m_biomeMap;

	Random<std::minstd_rand> m_random;

	static void setUpNoise();
	static NoiseGenerator m_heightNoiseGen;
	static NoiseGenerator m_biomeNoiseGen;
	Chunk* m_pChunk  = nullptr;
};
#endif // !__TERRAIN_GENERATION__



