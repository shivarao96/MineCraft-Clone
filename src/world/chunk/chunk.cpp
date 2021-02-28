#include "chunk.h"
#include "../world.h"
#include "../Block/chunkBlock/chunkBlock.h"
#include "../../renderer/mainRenderer.h"
#include "chunkMeshBuilder/chunkMeshBuillder.h"
#include <iostream>

Chunk::Chunk(World& world, sf::Vector2i location):m_location(location),m_pWorld(&world) {
	for (int y = 0; y < 3; y++) {
		m_chunksSections.emplace_back(sf::Vector3i(location.x,y,location.y), world);
	}
}

void Chunk::makeAllMesh() {
	for (auto& chunkSection: m_chunksSections) {
		ChunkMeshBuillder builder(chunkSection);
		builder.buildMesh(chunkSection.m_chunkMesh);
		chunkSection.m_chunkMesh.bufferMesh();
	}
}
void Chunk::setBlock(int x, int y, int z, ChunkBlock block) {
	if (outOfBound(x, y, z)) return;
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
		renderer.drawChunk(chunkSection.m_chunkMesh);
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