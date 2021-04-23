#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include "../../worldConstant.h"
#include "../chunkMesh/chunkMesh.h"
#include "../../Block/chunkBlock/chunkBlock.h"
#include "../iChunk/iChunk.h"
#include "../../../physics/AABB/AABB.h"

class World;

class ChunkSection: public IChunk
{
	friend class Chunk; //allowing the access to Chunk class
public:

	class Layer {
	public:
		void update(ChunkBlock block) {
			if (block == 0) {
				m_solidBlockCount--;
			}
			else {
				m_solidBlockCount++;
			}
		}

		bool isLayerSolid() const {
			return m_solidBlockCount == CHUNK_AREA;
		}

	private:
		int m_solidBlockCount = 0;
	};

	ChunkSection(const sf::Vector3i location, World& world);
	/*
	* Method-Override(ChunkSection): Following method set the chunkblock at pos x,y,z
	*	(based on world on the chunkblock array in chunksection)
	*/
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	/*
	* Method-Override(ChunkSection): Following method returns the chunkblock at pos x,y,z
	*	(based on world on the chunkblock array in chunksection)
	*/
	ChunkBlock getBlock(int x, int y, int z) const override;
	/*
	* Method(ChunkSection): get the current location of the chunksection in world.
	*/
	const sf::Vector3i getLocation() const;
	/*
	* Method(ChunkSection): build the mesh based on the m_chunkBlocks and load that to m_chunkMesh.
	*/
	void makeMesh();
	bool hasMesh() const;
	bool hasBuffered() const;
	/*
	* Method(ChunkSection): bufferMesh adds the m_mesh data into the mesh model later which can be called for rendering
	*/
	void bufferMesh();

	const Layer& getLayer(int y) const;
	ChunkSection& getAdjacent(int dx, int dz);

private:
	/*
	* Method(ChunkSection): convert the x,y,z to world position.
	*/
	sf::Vector3i toWorldPosition(int x, int y, int z) const noexcept;
	/*
	* Method(ChunkSection): Check the value is coming under the 0 to ChunkSize
	*/
	static bool outOfIndex(int value);
	/*
	* Method(ChunkSection): convert the x,y,z: 3D to 1D index value
	*/
	static int getBlockIndex(int x, int y, int z);

	std::array<
		ChunkBlock,
		CHUNK_VOLUME
	> m_chunkBlocks; // array of chunkblock represented in array(basically hold the info in M x N x L dimensions)
	ChunkMesh m_chunkMesh; // chunkmesh
	sf::Vector3i m_location; // current chunksection location
	World* m_pWorld; // chunk world var for recieving the world reference.
	bool m_hasMesh = false; // flag to check whether we intitiated the mesh building or not.
	bool m_hasMeshBuffered = false; // flag to check whether we buffered the mesh or not
	std::array<Layer, CHUNK_SIZE> m_layers;
	AABB m_aabb;
};

