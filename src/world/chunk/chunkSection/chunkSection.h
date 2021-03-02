#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "../../worldConstant.h"
#include "../chunkMesh/chunkMesh.h"
#include "../../Block/chunkBlock/chunkBlock.h"
#include "../iChunk/iChunk.h"

class World;

class ChunkSection: public IChunk
{
	friend class Chunk;
public:
	ChunkSection(const sf::Vector3i location, World& world);
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	const sf::Vector3i getLocation() const;
private:
	sf::Vector3i toWorldPosition(int x, int y, int z) const noexcept;
	static bool outOfIndex(int value);
	static int getBlockIndex(int x, int y, int z);
	bool hasMesh() const;

	std::array<
		ChunkBlock,
		CHUNK_VOLUME
	> m_chunkBlocks;
	ChunkMesh m_chunkMesh;
	sf::Vector3i m_location;
	World* m_pWorld;
	bool m_hasMesh = false;
};

