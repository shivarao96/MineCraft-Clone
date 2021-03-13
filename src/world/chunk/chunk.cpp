#include "chunk.h"
#include "../world.h"
#include "../Block/chunkBlock/chunkBlock.h"
#include "../../renderer/mainRenderer.h"
#include "chunkMeshBuilder/chunkMeshBuillder.h"
#include "../../utility/randomGenerator/random.h"
#include "../../utility/noiseGenerator/noiseGenerator.h"
#include <iostream>
#include <vector>

Chunk::Chunk(World& world, sf::Vector2i location)
	:m_location(location)
	,m_pWorld(&world) {}

void Chunk::load() {
	static int seed = RandomSingleton::get().intInRange(444, 444444);
	if (hasLoaded()) return;
	static Random<std::minstd_rand> rand((m_location.x ^ m_location.y) << 2);
	NoiseGenerator temp_noise(seed);
	std::array<int, CHUNK_AREA> heightMap;
	std::vector<sf::Vector3i> treeLocations;

	int maxValue = 0;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			int h = temp_noise.getHeight(x, z, m_location.x + 10, m_location.y + 10);
			heightMap[x * CHUNK_SIZE + z] = h;
			maxValue = std::max(maxValue, h);
		}
	}

	//for (int y = 0; y < maxValue / CHUNK_SIZE + 1; y++) {
	//	m_chunksSections.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
	//}

	for (int y = 0; y < maxValue + 1; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				int h = heightMap[x * CHUNK_SIZE + z];
				if (y > h) {
					continue;
				}
				else if (y == h) {
					if (y > WATER_LEVEL) {
						setBlock(x, y, z, BlockId::GRASS);
						if (rand.intInRange(0, 100) == 10) {
							treeLocations.emplace_back(x, y, z);
						}
					}
					else {
						setBlock(x, y, z, BlockId::SAND);
					}
				}
				else if (y > h / 3 + 4) {
					setBlock(x, y, z, BlockId::DIRT);
				}
				else {
					setBlock(x, y, z, BlockId::STONE);
				}
			}
		}

	}

	for (auto& treeLoc : treeLocations) {
		int h = rand.intInRange(5, 9);

		for (int y = 0; y < h; y++) {
			setBlock(treeLoc.x, treeLoc.y + y, treeLoc.z, BlockId::OAKBARK);
		} // place the bark

		for (int x = -4; x < 4; x++) {
			for (int z = -4; z < 4; z++) {
				for (int y = 0; y < 3; y++) {
					setBlock(treeLoc.x + x, treeLoc.y + h + y, treeLoc.z + z, BlockId::OAKLEAF);
				}
			}
		}
	}

	m_chunkLoaded = true;

}

bool Chunk::hasLoaded() const {
	return m_chunkLoaded;
}

/*
	This class is called only once.
*/
bool Chunk::makeMesh() {
	for (auto& chunkSection: m_chunksSections) {
		if (!chunkSection.hasMesh()) { //if mesh don't exist then make the mesh
			chunkSection.makeMesh();
			return true;
		}
	}
	return false;
}
void Chunk::setBlock(int x, int y, int z, ChunkBlock block) {
	addSectionsBlockTarget(y);
	if (outOfBound(x, y, z)) return;
	int bY = y % CHUNK_SIZE;
	m_chunksSections.at(y / CHUNK_SIZE).setBlock(x, bY, z, block);
}
ChunkBlock Chunk::getBlock(int x, int y, int z) const {
	if (outOfBound(x, y, z)) { 
		return BlockId::AIR; 
	}
	int bY = y % CHUNK_SIZE;
	return m_chunksSections.at(y / CHUNK_SIZE).getBlock(x, bY, z);
}
void Chunk::drawChunks(MainRenderer& renderer) {
	for (auto& chunkSection : m_chunksSections) {
		if (chunkSection.hasMesh()) {
			if (!chunkSection.hasBuffered()) {
				chunkSection.bufferMesh();
			}
			renderer.drawChunk(chunkSection.m_chunkMesh);
		}
	}
}
bool Chunk::outOfBound(int x, int y, int z) const {
	if (x >= CHUNK_SIZE) {
		return true;
	} 
	if (z >= CHUNK_SIZE) {
		return true;
	}

	if (x < 0) return true;
	if (y < 0) return true;
	if (z < 0) return true;

	if (y >= (int)m_chunksSections.size() * CHUNK_SIZE) {
		return true;
	}
	
	return false;
}
ChunkSection& Chunk::getSection(int index) {
	return m_chunksSections.at(index);
}

void Chunk::addSection() {
	int y = m_chunksSections.size();
	m_chunksSections.emplace_back(sf::Vector3i( m_location.x, y , m_location.y ), *m_pWorld);
}
void Chunk::addSectionsBlockTarget(int blockY) {
	int index = blockY / CHUNK_SIZE;
	addSectionsIndexTarget(index);
}
void Chunk::addSectionsIndexTarget(int index) {
	while (m_chunksSections.size() < index + 1) {
		addSection();
	}
}