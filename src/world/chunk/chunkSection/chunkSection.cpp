#include "chunkSection.h"
#include "../../world.h"
#include "../chunkMeshBuilder/chunkMeshBuillder.h"
#include <iostream>

ChunkSection::ChunkSection(const sf::Vector3i location, World& world)
	:m_location(location), m_pWorld(&world)
{
}
void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block) {
	//m_hasMesh = false;
	if (outOfIndex(x) ||
		outOfIndex(y) ||
		outOfIndex(z)) { //-- check if the coords are out of the section if 'yes' then set the block in the m_world
		auto location = toWorldPosition(x, y, z);
		m_pWorld->setBlock(location.x, location.y, location.z, block);
		return;
	}
	//-- if above condition fails that means the coords are in between the current bounds
	m_layers[y].update(block);
	m_chunkBlocks[getBlockIndex(x, y, z)] = block;
}

void ChunkSection::makeMesh() {
	//-- build the mesh based on the m_chunkBlocks and load that to m_chunkMesh.
	ChunkMeshBuillder(*this, m_chunkMesh).buildMesh();
	m_hasMesh = true;
	m_hasMeshBuffered = false;
}

void ChunkSection::bufferMesh() {
	//m_layers;
	m_chunkMesh.bufferMesh();
	m_hasMeshBuffered = true;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z) const {
	if (outOfIndex(x) ||
		outOfIndex(y) ||
		outOfIndex(z)) {//-- check if the coords are out of the section if 'yes' then extract from m_world
		auto location = toWorldPosition(x, y, z);
		return m_pWorld->getBlock(location.x, location.y, location.z);
	}
	//-- if above condition fails that means the coords are in between the current bounds
	return m_chunkBlocks[getBlockIndex(x, y, z)];
}
bool ChunkSection::outOfIndex(int value) {
	return value >= CHUNK_SIZE || value < 0;
}
int ChunkSection::getBlockIndex(int x, int y, int z) {
	return  y *
		CHUNK_AREA + z *
		CHUNK_SIZE + x;	
}
const sf::Vector3i ChunkSection::getLocation() const {
	return m_location;
}
sf::Vector3i ChunkSection::toWorldPosition(int x, int y, int z) const noexcept {
	return {
		m_location.x * CHUNK_SIZE + x,
		m_location.y * CHUNK_SIZE + y,
		m_location.z * CHUNK_SIZE + z
	};
}
bool ChunkSection::hasMesh() const {
	return m_hasMesh;
}

bool ChunkSection::hasBuffered() const {
	return m_hasMeshBuffered;
}

const ChunkSection::Layer& ChunkSection::getLayer(int y) const {
	if (y == -1) {
		return m_pWorld->getChunkManager().getChunk(m_location.x, m_location.z).getSection(m_location.y - 1).getLayer(CHUNK_SIZE - 1);
	}
	else if(y == CHUNK_SIZE) {
		return m_pWorld->getChunkManager().getChunk(m_location.x, m_location.z).getSection(m_location.y + 1).getLayer(0);
	}
	else {
		return m_layers[y];
	}
}
ChunkSection& ChunkSection::getAdjacent(int dx, int dz) {
	return m_pWorld->getChunkManager().getChunk(m_location.x + dx, m_location.z + dz).getSection(m_location.y);
}