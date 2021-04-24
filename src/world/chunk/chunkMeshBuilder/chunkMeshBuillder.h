#pragma once

#include <SFML/Graphics.hpp>
#include "../chunkMesh/chunkMesh.h"
#include "../chunkSection/chunkSection.h"
#include "../../Block/blockData/blockData.h"

/*
* Following class work is to build the chunkmesh data based on chunksection chunkblocks
*/
class ChunkMeshBuillder
{
public:
	ChunkMeshBuillder()  = default;
	~ChunkMeshBuillder();

	/*
	* Following constructor loads the chunksection and chunkmesh with the reference provided as arguments(chunksection and chunkmesh)
	* based on blockdata in [M][M][M] chunkBlocks chunkmesh is updated and it reflect the chunkmesh in chunksection class
	*/
	ChunkMeshBuillder(ChunkSection& chunkSection, ChunkMesh& chunkMesh);
	/*
	* Method(ChunkMeshBuillder): build the chunkmesh based chunksection chunkblock info
 	*/
	void buildMesh();
private:
	/*
	* Method(ChunkMeshBuillder): add the face with 
	*	1) face coords val
	*	2) texture coords for the face
	*	3) chunk Position in world space
	*	4) block pos in world space to check for the adjacent blocks
	*/
	void tryAddFaceToMesh(
		const std::vector<float>& blockFace,
		const sf::Vector2i&       texCoords,
		const sf::Vector3i&       chunkPosition,
		const sf::Vector3i&       blockPosition,
		const char* faceType
	);
	/*
	* Method(ChunkMeshBuillder): Check for conditional requirements to render some part of the face for a block
	*/
	bool shouldMakeFace(
		const sf::Vector3i&    adjPositions,
		const BlockDataHolder& blockdata,
		const char* faceType
	);

	bool shouldMakeLayer(int y);

	ChunkMesh*    m_pChunkMesh                = nullptr;// will hold the chunkmesh reference of chunkSection
	ChunkSection* m_pChunkSection       = nullptr; //will have the chunksection reference for doing work FYI: it will add info in chunkMesh based on chunkSection blockdata info 
	const BlockDataHolder* m_pBlockDataHolder = nullptr; // will hold each block blockType info
};

