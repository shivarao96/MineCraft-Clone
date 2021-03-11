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

	static Random<std::minstd_rand> rand(500);
	NoiseGenerator temp_noise(6543);
	std::array<int, CHUNK_AREA> heightMap;
	std::vector<sf::Vector3i> treeLocations;

	int maxValue = 0;
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			int h = temp_noise.getHeight(x, z, m_location.x, m_location.y);
			heightMap[x * CHUNK_SIZE + z] = h;
			maxValue = std::max(maxValue, h);
		}
	}

	for (int y = 0; y < maxValue / CHUNK_SIZE + 1; y++) {
		m_chunksSections.emplace_back(sf::Vector3i(m_location.x, y, m_location.y), *m_pWorld);
	}
	//int height = m_chunksSections.size() * CHUNK_SIZE;
	for (int y = 0; y < maxValue + 1; y++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {

				int h = heightMap[x * CHUNK_SIZE + z];
				if (y > h) {
					setBlock(x, y, z, BlockId::AIR);
				}
				else if (y == h) {
					setBlock(x, y, z, BlockId::GRASS);
					if (rand.intInRange(0, 100) == 10) {
						treeLocations.emplace_back(x, y, z);
					}
				}
				else if (y > h / 3) {
					setBlock(x, y, z, BlockId::DIRT);
				}
				else {
					setBlock(x, y, z, BlockId::STONE);
				}
			}
		}

	}
	m_chunkLoaded = true;
}

bool Chunk::hasLoaded() {
	return m_chunkLoaded;
}

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
void Chunk::drawChunks(MainRenderer& renderer) const {
	for (const auto& chunkSection : m_chunksSections) {
		if (chunkSection.hasMesh()) {
			renderer.drawChunk(chunkSection.m_chunkMesh);
		}
	}
}
bool Chunk::outOfBound(int x, int y, int z) const {
	if (x >= CHUNK_SIZE) {
		std::cout << "x size greater than chunk_size" << std::endl;
		return true;
	} 
	if (z >= CHUNK_SIZE) {
		std::cout << "z size greater than chunk_size" << std::endl;
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
	while (index >= m_chunksSections.size()) {
		// create new section
		m_chunksSections.emplace_back(sf::Vector3i(m_location.x, m_chunksSections.size(), m_location.y), *m_pWorld);
	}
	return m_chunksSections.at(index);
}