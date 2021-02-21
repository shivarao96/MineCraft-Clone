#pragma once

#include <vector>

class Model
{
public:
	Model() = default;
	Model(
		const std::vector<float>&        vertexPositions,
		const std::vector<float>&        texCoords,
		const std::vector<unsigned int>& indices 
	);
	~Model();
	void addData(
		const std::vector<float>&        vertexPositions,
		const std::vector<float>&        texCoords,
		const std::vector<unsigned int>& indices
	);
	void deleteData();
	void addVBO(
		int dimension,
		const std::vector<float>& data
	);
	void addEBO(const std::vector<unsigned int>& data);
	void bindVAO();
	int getIndicesCount() const;
private:
	unsigned int m_vao = 0;
	int m_vboCount     = 0;
	int m_indicesCount = 0;
	std::vector<unsigned int> m_vboBuffers;
};

