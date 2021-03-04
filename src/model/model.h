#pragma once

#include <vector>
#include "../mesh/mesh.h"

class Model
{
public:
	Model() = default;
	Model(const Mesh& mesh);
	~Model();
	void addData(const Mesh& mesh);
	void deleteData();
	void genVAO();
	void addVBO(
		int dimension,
		const std::vector<float>& data
	);
	void addEBO(const std::vector<unsigned int>& data);
	void bindVAO() const;
	int getIndicesCount() const;
	Model(Model&& other);
	Model& operator=(Model&& other);
private:
	unsigned int m_vao = 0;
	int m_vboCount     = 0;
	int m_indicesCount = 0;
	std::vector<unsigned int> m_vboBuffers;
};

