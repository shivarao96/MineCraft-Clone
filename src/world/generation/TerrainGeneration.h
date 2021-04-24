#pragma once
#ifndef __TERRAIN_GENERATION__
#define __TERRAIN_GENERATION__

#include <array>
#include "../worldConstant.h"
#include "../../utility/noiseGenerator/noiseGenerator.h"
#include "../../utility/randomGenerator/random.h"
#include "./biome/Biome.h"
#include <string>
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
	void getHeightln(int xMin, int zMin, int xMax, int zMax);
	const Biome& getBiomeAt(int x, int z) const;

	std::array<int, CHUNK_AREA> m_heightMap;
	std::array<int, (CHUNK_SIZE + 1)* (CHUNK_SIZE + 1)> m_biomeMap;

	Random<std::minstd_rand> m_random;

	static void setUpNoise();
	static NoiseGenerator m_biomeNoiseGen;
	Chunk* m_pChunk  = nullptr;

	GrassLandBiome m_grassLandBiome;
	LightForestBiome m_lightForestBiome;
	DesertBiome m_desertForestBiome;
};
#endif // !__TERRAIN_GENERATION__



