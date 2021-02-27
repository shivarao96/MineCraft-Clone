#pragma once

#include <SFML/Graphics.hpp>
#include "../chunkMesh/chunkMesh.h"
#include "../chunkSection/chunkSection.h"
#include "../../Block/blockData/blockData.h"

class ChunkMeshBuillder
{
public:
	ChunkMeshBuillder()  = default;
	~ChunkMeshBuillder();

	ChunkMeshBuillder(ChunkSection& chunkSection);
	void buildMesh(ChunkMesh& chunkMesh);
private:
	void tryAddFaceToMesh(
		const std::vector<float>& blockFace,
		const sf::Vector2i&       texCoords,
		const sf::Vector3i&       chunkPosition,
		const sf::Vector3i&       blockPosition,
		const char* faceType
	);
	bool shouldMakeFace(
		const sf::Vector3i&    adjPositions,
		const BlockDataHolder& blockdata,
		const char* faceType
	);

	ChunkMesh*    m_pChunkMesh                = nullptr;
	ChunkSection* m_pChunkSection             = nullptr;
	const BlockDataHolder* m_pBlockDataHolder = nullptr;
};

