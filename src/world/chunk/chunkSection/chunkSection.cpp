#include "chunkSection.h"


ChunkSection::ChunkSection() {
	m_location = { 0,0,0 };
	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				if (y == CHUNK_SIZE - 1) {
					m_chunks[getBlockIndex(x, y, z)].m_id = 1;
				}
				else if (y < 10) {
					m_chunks[getBlockIndex(x, y, z)].m_id = 3;
				}
				else {
					m_chunks[getBlockIndex(x, y, z)].m_id = 2;
				}
			}
		}
	}
}
void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block) {
	if (outOfIndex(x)) return;
	if (outOfIndex(y)) return;
	if (outOfIndex(z)) return;

	m_chunks[getBlockIndex(x, y, z)] = block;

}
ChunkBlock ChunkSection::getBlock(int x, int y, int z) {
	
	if (outOfIndex(x)) return BlockId::AIR;
	if (outOfIndex(y)) return BlockId::AIR;
	if (outOfIndex(z)) return BlockId::AIR;
	return m_chunks[getBlockIndex(x, y, z)];
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