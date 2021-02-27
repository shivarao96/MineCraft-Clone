#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../../model/model.h"

class ChunkMesh
{
public:
	ChunkMesh();
	void addFace(
		const std::vector<float>& blockFace,
		const std::vector<float>& texCoords,
		const sf::Vector3i&       chunkPosition,
		const sf::Vector3i&       blockPosition
	);
	void bufferMesh();
	const Model& getModel() const;
private:
	Model m_model;
	Mesh  m_mesh;
	unsigned int m_index = 0;
};

