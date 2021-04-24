#include "chunkMeshBuillder.h"
#include <vector>
#include "../../Block/blockDataBase/blockDataBase.h"
#include <SFML/Graphics.hpp>
#include <iostream>

// Data for the cube face coords
namespace FaceVal {
	
	std::vector<float> frontFace{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

	std::vector<float> backFace{
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,
	};

	std::vector<float> leftFace{
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,
	};

	std::vector<float> rightFace{
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,
	};

	std::vector<float> topFace{
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,
	};

	std::vector<float> bottomFace{
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

}

// direction class for updating there x,y, and z position.
struct Direction
{
	void update(int x, int y, int z) {
		up    = { x    , y + 1, z     };
		down  = { x    , y - 1, z     };
		left  = { x - 1, y    , z     };
		right = { x + 1, y    , z     };
		front = { x    , y    , z + 1 };
		back  = { x    , y    , z - 1 };
	}

	sf::Vector3i up;
	sf::Vector3i down;
	sf::Vector3i left;
	sf::Vector3i right;
	sf::Vector3i front;	
	sf::Vector3i back;
};

ChunkMeshBuillder::ChunkMeshBuillder(ChunkSection& chunkSection, ChunkMesh& chunkMesh)
	:m_pChunkSection(&chunkSection)
	,m_pChunkMesh(&chunkMesh)
{}

void ChunkMeshBuillder::buildMesh() {
	sf::Clock c;
	Direction direction;

	for (int8_t y = 0; y < CHUNK_SIZE; ++y) { // go through the y-axis
		if (!shouldMakeLayer(y)) continue;
		for (int8_t x = 0; x < CHUNK_SIZE; ++x) { // go through the x-axis
			for (int8_t z = 0; z < CHUNK_SIZE; ++z) { // go through the z-axis
				sf::Vector3i positions(x,y,z);
				ChunkBlock block = m_pChunkSection->getBlock(x, y, z); // get the what kind of block is to be rendered at (x,y,z) position.
				if (block == BlockId::AIR) { // if it is air then no need to render any face
					continue;
				}

				m_pBlockDataHolder = &block.getBlockData();
				auto& texData = *m_pBlockDataHolder;
				direction.update(x, y, z);

				// now try adding all the faces with there texture coordinates
				
				tryAddFaceToMesh(
					FaceVal::topFace,
					texData.texTopCoords,
					positions,
					direction.up,
					"up"
				);
				tryAddFaceToMesh(
					FaceVal::bottomFace,
					texData.texBottomCoords,
					positions,
					direction.down,
					"down"
				);
				tryAddFaceToMesh(
					FaceVal::leftFace,
					texData.texSideCoords,
					positions,
					direction.left,
					"left"
				);
				tryAddFaceToMesh(
					FaceVal::rightFace,
					texData.texSideCoords,
					positions,
					direction.right,
					"right"
				);
				tryAddFaceToMesh(
					FaceVal::frontFace,
					texData.texSideCoords,
					positions,
					direction.front,
					"front"
				);
				tryAddFaceToMesh(
					FaceVal::backFace,
					texData.texSideCoords,
					positions,
					direction.back,
					"back"
				);
			}
		}
	}
}

void ChunkMeshBuillder::tryAddFaceToMesh(
	const std::vector<float>& blockFace,
	const sf::Vector2i& texCoords,
	const sf::Vector3i& chunkPosition,
	const sf::Vector3i& blockPosition,
	const char* faceType
) {
	if (shouldMakeFace(blockPosition, *m_pBlockDataHolder, faceType)) {
		auto texCoordInfo = BlockDataBase::get().m_textureAtlas.getTextureCoords(texCoords);
		m_pChunkMesh->addFace(
			blockFace,
			texCoordInfo,
			m_pChunkSection->getLocation(), // this is chunklocation
			chunkPosition
		);
	}
}

bool ChunkMeshBuillder::shouldMakeFace(
	const sf::Vector3i& adjPositions,
	const BlockDataHolder& blockdata,
	const char* faceType
) {
	auto block = m_pChunkSection->getBlock(
		adjPositions.x,
		adjPositions.y,
		adjPositions.z
	);
	auto& data = block.getBlockData();
	// if the adjacent block is AIR then create the block
	if (block == BlockId::AIR) {
		return true;
	}
	// guessing it checks for opaque object and also checks for id if both are same then no need to do anything(but still i find this condition of no use)
	else if (!(data.isOpaque) && (m_pBlockDataHolder->id != data.id)) { // still need to understand how does this thing works
		return true;
	}
	else {
		return false;
	}
}

bool ChunkMeshBuillder::shouldMakeLayer(int y)
{
	auto isAdjSolid = [&](int x, int z) {
		const ChunkSection& cs = m_pChunkSection->getAdjacent(x, z);
		return cs.getLayer(y).isLayerSolid();
	};

	return	(!m_pChunkSection->getLayer(y).isLayerSolid()) ||
		(!m_pChunkSection->getLayer(y + 1).isLayerSolid()) ||
		(!m_pChunkSection->getLayer(y - 1).isLayerSolid()) ||
		(!isAdjSolid(1, 0)) ||
		(!isAdjSolid(0, 1)) ||
		(!isAdjSolid(-1, 0)) ||
		(!isAdjSolid(0, -1));
	//return (!m_pChunkSection->getLayer(y).isLayerSolid()) || (!m_pChunkSection->getLayer(y + 1).isLayerSolid()) || (!m_pChunkSection->getLayer(y - 1).isLayerSolid());
}

ChunkMeshBuillder::~ChunkMeshBuillder() {
	//delete m_pChunkMesh;
	//delete m_pChunkSection;
	//delete m_pBlockDataHolder;
}