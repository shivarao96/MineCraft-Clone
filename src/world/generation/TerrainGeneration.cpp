#include "TerrainGeneration.h"
#include "../chunk/chunk.h"
#include "./treeGeneration/TreeGeneration.h"

namespace Generation {
	int seed = 50424;
};

NoiseGenerator TerrainGeneration::m_heightNoiseGen(Generation::seed);
NoiseGenerator TerrainGeneration::m_biomeNoiseGen(Generation::seed * 2);

TerrainGeneration::TerrainGeneration() {
	setUpNoise();
}
void TerrainGeneration::generateTerrainFor(Chunk& chunk) {
	m_pChunk = &chunk;
	auto location = chunk.getChunkLocation();
	getHeightMap();
	getBiomeMap();
	m_random.setSeed((location.x + location.y) << 2);
	int maxHeight = *std::max_element(m_heightMap.begin(), m_heightMap.end());
	maxHeight = std::max(maxHeight, WATER_LEVEL);
	setBlocks(maxHeight);
}

void TerrainGeneration::setBlocks(int maxHeight)
{
	std::vector<sf::Vector3i> trees;

	for (int y = 0; y < maxHeight + 1; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				int height = m_heightMap[x * CHUNK_SIZE + z];
				if (y > height) {
					if (y <= WATER_LEVEL)
					{
						m_pChunk->setBlock(x, y, z, BlockId::WATER);
					}
					continue;
				}
				else if (y == height) {
					if (y >= WATER_LEVEL) {
						if (m_random.intInRange(0, 200) == 99) {
							trees.emplace_back(x,y,z );
						}
						setTopBlock(x, y, z);
					}
					else {
						m_pChunk->setBlock(x, y, z, 
							(m_random.intInRange(0, 10) < 5) ? BlockId::SAND : BlockId::DIRT 
						);
					}
				}
				else if (y > height / 3 + 4) {
					m_pChunk->setBlock(x, y, z, BlockId::DIRT);
				}
				else {
					m_pChunk->setBlock(x, y, z, BlockId::STONE);
				}
			}
		}
	}

	for (auto& tree: trees) {
		makeOakTree(*m_pChunk, m_random, tree.x, tree.y, tree.z);
	}
}

void TerrainGeneration::setTopBlock(int x, int y, int z)
{
	int biome = m_biomeMap[x * CHUNK_SIZE + z];
	if (biome < 100) {
		m_pChunk->setBlock(x, y, z, BlockId::GRASS);
	}
	else {
		m_pChunk->setBlock(x, y, z, BlockId::SAND);
	}
}

void TerrainGeneration::getHeightMap()
{
	auto location = m_pChunk->getChunkLocation();
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			m_heightMap[x * CHUNK_SIZE + z] = m_heightNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
		}
	}
}

void TerrainGeneration::getBiomeMap()
{
	auto location = m_pChunk->getChunkLocation();
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			m_biomeMap[x * CHUNK_SIZE + z] = m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
		}
	}
}

void TerrainGeneration::setUpNoise()
{
	static bool noiseGen = false;
	if (!noiseGen) {
		noiseGen = true;
		NoiseParameters heightParams;
		heightParams.octaves = 7;
		heightParams.amplitude = 70;
		heightParams.smoothness = 235;
		heightParams.heightOffset = -5;
		heightParams.roughNess = 0.53;

		NoiseParameters biomeParmams;
		biomeParmams.octaves = 5;
		biomeParmams.amplitude = 90;
		biomeParmams.smoothness = 735;
		biomeParmams.heightOffset = -5;
		biomeParmams.roughNess = 0.6;

		m_heightNoiseGen.setNoiseParameter(heightParams);
		m_biomeNoiseGen.setNoiseParameter(biomeParmams);
	}
}
