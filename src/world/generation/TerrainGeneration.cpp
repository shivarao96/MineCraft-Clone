#include "TerrainGeneration.h"
#include "../chunk/chunk.h"
#include "./treeGeneration/TreeGeneration.h"
#include "../../math/bilinear-interpolation/BilinearInterpolation.h"

namespace Generation {
	int seed = RandomSingleton::get().intInRange(424, 325322);;
};

NoiseGenerator TerrainGeneration::m_biomeNoiseGen(Generation::seed * 2);

TerrainGeneration::TerrainGeneration()
	: m_grassLandBiome(Generation::seed)
	,m_lightForestBiome(Generation::seed)
	,m_desertForestBiome(Generation::seed)
{
	setUpNoise();
}
void TerrainGeneration::generateTerrainFor(Chunk& chunk) {
	m_pChunk = &chunk;
	sf::Vector2i location = chunk.getChunkLocation();
	m_random.setSeed((location.x + location.y) << 2);
	getHeightMap();
	getBiomeMap();
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
				const Biome& biome = getBiomeAt(x, z);
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
				else if (y > height - 3) {
					m_pChunk->setBlock(x, y, z, BlockId::DIRT);
				}
				else {
					m_pChunk->setBlock(x, y, z, BlockId::STONE);
				}
			}
		}
	}

	for (auto& tree: trees) {
		getBiomeAt(tree.x, tree.z).makeTrees(*m_pChunk, m_random, tree.x, tree.y, tree.z);
	}
}

void TerrainGeneration::setTopBlock(int x, int y, int z)
{
	m_pChunk->setBlock(x, y, z, getBiomeAt(x, z).getTopBlock(m_random));
}

void TerrainGeneration::getHeightMap()
{
	constexpr static int HALF_CHUNK = CHUNK_SIZE / 2;
	constexpr static int CHUNK = CHUNK_SIZE;

	getHeightln(0, 0, HALF_CHUNK, HALF_CHUNK);
	getHeightln(HALF_CHUNK, 0, CHUNK, HALF_CHUNK);
	getHeightln(0, HALF_CHUNK, HALF_CHUNK, CHUNK);
	getHeightln(HALF_CHUNK, HALF_CHUNK, CHUNK, CHUNK);
}

void TerrainGeneration::getBiomeMap()
{
	auto location = m_pChunk->getChunkLocation();
	for (int x = 0; x < CHUNK_SIZE + 1; x++) {
		for (int z = 0; z < CHUNK_SIZE + 1; z++) {
			m_biomeMap[x * (CHUNK_SIZE+1) + z] = m_biomeNoiseGen.getHeight(x, z, location.x + 10, location.y + 10);
		}
	}
}

void TerrainGeneration::getHeightln(int xMin, int zMin, int xMax, int zMax)
{
	auto getHeightAt = [&](int x, int z, const std::string& pos) {
		const Biome& biome = getBiomeAt(x, z);
		return biome.getHeight(x, z,m_pChunk->getChunkLocation().x, m_pChunk->getChunkLocation().y);
	};

	float bottomLeft = getHeightAt(xMin, zMin, "BottomLeft");
	float bottomRight = getHeightAt(xMax, zMin, "BottomRight");
	float topLeft = getHeightAt(xMin, zMax, "TopLeft");
	float topRight = getHeightAt(xMax, zMax, "TopRight");

	for (int x = xMin; x < xMax; ++x) {
		for (int z = zMin; z < zMax; ++z) {
			if (x == CHUNK_SIZE) 
				continue;
			if (z == CHUNK_SIZE) 
				continue;
			int h = bilinearInterpolation(
				bottomLeft,
				bottomRight,
				topLeft,
				topRight,
				xMax,
				xMin,
				zMax,
				zMin,
				x,
				z
			);
			m_heightMap[x * CHUNK_SIZE + z] = h;
		}
	}
}

const Biome& TerrainGeneration::getBiomeAt(int x, int z) const
{
	int biomeValue = m_biomeMap[x * (CHUNK_SIZE + 1) + z];
	if (biomeValue > 155) {
		return m_desertForestBiome;
	}
	else if (biomeValue > 135) {
		return m_lightForestBiome;
	}
	else {
		return m_grassLandBiome;
	}
}

void TerrainGeneration::setUpNoise()
{
	static bool noiseGen = false;
	if (!noiseGen) {
		noiseGen = true;

		NoiseParameters biomeParmams;
		biomeParmams.octaves = 5;
		biomeParmams.amplitude = 125;
		biomeParmams.smoothness = 735;
		biomeParmams.heightOffset = -5;
		biomeParmams.roughNess = 0.6;

		m_biomeNoiseGen.setNoiseParameter(biomeParmams);
	}
}
