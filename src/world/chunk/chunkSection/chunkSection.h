#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "../../worldConstant.h"
#include "../chunkMesh/chunkMesh.h"
#include "../../Block/chunkBlock/chunkBlock.h"

class ChunkSection
{
public:
	ChunkSection();

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);
	const sf::Vector3i getLocation() const;
	ChunkMesh m_chunkMesh;
private:
	bool outOfIndex(int value);
	int getBlockIndex(int x, int y, int z);

	std::array<
		ChunkBlock,
		CHUNK_VOLUME
	> m_chunks;
	sf::Vector3i m_location;
};

