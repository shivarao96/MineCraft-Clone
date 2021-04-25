#pragma once
#ifndef __TERRAIN_GENERATION__
#define __TERRAIN_GENERATION__

#include <array>
#include "../worldConstant.h"
#include "../../utility/noiseGenerator/noiseGenerator.h"
#include "../../utility/randomGenerator/random.h"
#include "./biome/Biome.h"
#include <string>
#include "../../utility/array2D/Array2D.h"
#include "grassLandBiome/GrassLandBiome.h"
#include "lightForestBiome/LightForestBiome.h"
#include "desertBiome/DesertBiome.h"

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

	Array2D<int, CHUNK_SIZE> m_heightMap;
	Array2D<int, (CHUNK_SIZE + 1)> m_biomeMap;

	Random<std::minstd_rand> m_random;

	static void setUpNoise();
	static NoiseGenerator m_biomeNoiseGen;
	Chunk* m_pChunk  = nullptr;

	GrassLandBiome m_grassLandBiome;
	LightForestBiome m_lightForestBiome;
	DesertBiome m_desertForestBiome;
};
#endif // !__TERRAIN_GENERATION__



