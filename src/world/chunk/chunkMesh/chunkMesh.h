#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../../model/model.h"

/*
* ChunkMesh which contains mesh data
*/
class ChunkMesh
{
public:
	ChunkMesh();
	/*
	* Method(ChunkMesh): add face data
	* @blockFace: (front, back, top, bottom, left, right)
	* @texCoords: correct texture coordinate for face
	* @chunkPosition: current chunk(collection of blocks) position in world space
	* @blockPosition: current block position in world space
	*/
	void addFace(
		const std::vector<float>& blockFace,
		const std::vector<float>& texCoords,
		const sf::Vector3i&       chunkPosition,
		const sf::Vector3i&       blockPosition
	);
	/*
	* Method(ChunkMesh): add mesh data into a model
	*/
	void bufferMesh();
	/*
	* Method(ChunkMesh): get the model data that is holding all the chunkMesh info
	*/
	const Model& getModel() const;
	/*
	* Method(ChunkMesh): get the total number of face in chunkmesh
 	*/
	int getFaceCount() const;
private:
	int m_faceCount = 0;
	Model m_model;
	Mesh  m_mesh;
	unsigned int m_index = 0;
};

