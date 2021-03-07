#include "chunkMesh.h"
#include "../../worldConstant.h"

ChunkMesh::ChunkMesh() {

}
void ChunkMesh::addFace(
	const std::vector<float>& blockFace,
	const std::vector<float>& texCoords,
	const sf::Vector3i&       chunkPosition,
	const sf::Vector3i&       blockPosition
) {
	m_faceCount++;
	auto& vertices           = m_mesh.vertexPositions;
	auto& textureCoordinates = m_mesh.textureCoordinates;
	auto& indices            = m_mesh.indices;

	textureCoordinates.insert(
		textureCoordinates.end(),
		texCoords.begin(),
		texCoords.end()
	); // setting up the texture coords


	for (int i = 0, index = 0; i < 4; ++i) {
		vertices.push_back(
			blockFace[index++] + chunkPosition.x * CHUNK_SIZE + blockPosition.x
		);
		vertices.push_back(
			blockFace[index++] + chunkPosition.y * CHUNK_SIZE + blockPosition.y
		);
		vertices.push_back(
			blockFace[index++] + chunkPosition.z * CHUNK_SIZE + blockPosition.z
		);
	} // setting up the vertices

	indices.insert(indices.end(),
		{
			m_index,
			m_index + 1,
			m_index + 2,

			m_index + 2,
			m_index + 3,
			m_index
		}
	); // setting up the indices
	m_index += 4;
}
void ChunkMesh::bufferMesh() {
	m_model.addData(m_mesh);
	
	m_mesh.vertexPositions.clear();
	m_mesh.textureCoordinates.clear();
	m_mesh.indices.clear();

	m_mesh.vertexPositions.shrink_to_fit();
	m_mesh.textureCoordinates.shrink_to_fit();
	m_mesh.indices.shrink_to_fit();
	m_index = 0;
}
const Model& ChunkMesh::getModel() const {
	return m_model;
}

int ChunkMesh::getFaceCount() const {
	return m_faceCount;
}