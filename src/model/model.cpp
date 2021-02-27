#include "model.h"
#include <GL/glew.h>

Model::Model(const Mesh& mesh) {
	addData(
		mesh
	);
}	
Model::~Model() {
	deleteData();
}
void Model::addData(const Mesh& mesh) {
	if (m_vao != 0)
		deleteData();
	m_indicesCount = mesh.indices.size();
	glGenVertexArrays(
		1, 
		&m_vao
	);
	glBindVertexArray(m_vao);
	
	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoordinates);
	addEBO(mesh.indices);
}
void Model::addVBO(
	int dimension, 
	const std::vector<float>& data
) {
	unsigned int vbo;
	glGenBuffers(
		1, 
		&vbo
	);
	glBindBuffer(
		GL_ARRAY_BUFFER,
		vbo
	);
	glBufferData(
		GL_ARRAY_BUFFER,
		data.size() * sizeof(float),
		data.data(),
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(
		m_vboCount,
		dimension,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
	);
	glEnableVertexAttribArray(m_vboCount++);
	m_vboBuffers.push_back(vbo);
}
void Model::addEBO(const std::vector<unsigned int>& data) {
	unsigned int ebo;
	glGenBuffers(
		1, 
		&ebo
	);
	glBindBuffer(
		GL_ELEMENT_ARRAY_BUFFER,
		ebo
	);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		data.size() * sizeof(unsigned int),
		data.data()	,
		GL_STATIC_DRAW
	);
}
void Model::deleteData() {
	glDeleteVertexArrays(
		1, 
		&m_vao
	);
	glDeleteBuffers(
		m_vboBuffers.size(),
		m_vboBuffers.data()
	);

	m_vao = 0;
	m_vboCount = 0;
	m_indicesCount = 0;
	m_vboBuffers.clear();
}
void Model::bindVAO() const{
	glBindVertexArray(m_vao);
}
int Model::getIndicesCount() const {
	return m_indicesCount;
}