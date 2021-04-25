#pragma once
#ifndef __BIOME__
#define __BIOME__

#include "../../../utility/randomGenerator/random.h"
#include "../../Block/BlockId.h"
#include "../../../utility/noiseGenerator/noiseGenerator.h"

class Chunk;

using Rand = Random<std::minstd_rand>;

//struct Biome
//{
//	virtual BlockId getTopBlock(Rand& rand)const = 0;
//	virtual void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const = 0;
//	virtual int getHeight(int x, int z, int chunkX, int chunkZ)const = 0;
//	virtual int getTreeFrequency()const = 0;
//};
//// grass land biome
//class GrassLandBiome: public Biome
//{
//public:
//	GrassLandBiome(int seed);
//	BlockId getTopBlock(Rand& rand)const;
//	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
//	int getHeight(int x, int z, int chunkX, int chunkZ)const;
//	int getTreeFrequency()const;
//private:
//	NoiseGenerator m_noiseGenerator;
//};
//
//// light forest
//class LightForestBiome: public Biome
//{
//public:
//	LightForestBiome(int seed);
//	BlockId getTopBlock(Rand& rand)const;
//	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
//	int getHeight(int x, int z, int chunkX, int chunkZ)const;
//	int getTreeFrequency()const;
//private:
//	NoiseGenerator m_noiseGenerator;
//};
//// desert
//class DesertBiome : public Biome
//{
//public:
//	DesertBiome(int seed);
//	BlockId getTopBlock(Rand& rand)const;
//	void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const;
//	int getHeight(int x, int z, int chunkX, int chunkZ)const;
//	int getTreeFrequency()const;
//private:
//	NoiseGenerator m_noiseGenerator;
//};
#endif // !__BIOME__



struct Biome {
public:
	Biome(const NoiseParameters& noiseParam, int treeFrequency, int seed);
	virtual BlockId getTopBlock(Rand& rand)const = 0;
	virtual void makeTrees(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z)const = 0;
	int getHeight(int x, int z, int chunkX, int chunkZ)const;
	int getTreeFrequency()const;
protected:
	virtual NoiseParameters getNoiseParam() = 0;
private:
	NoiseGenerator m_noiseGenerator;
	int m_treeFrequency;
};