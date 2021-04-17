#pragma once

#include <vector>
#include "../mesh/mesh.h"


/*
* Work of this class is to create the model for the opengl render pipeline
* it take the Mesh info and setup the vertex infos
*/
class Model
{
public:
	Model() = default;

	/*
	* Model data take mesh info
	* Mesh class
	* {
	*	vertexPos: glm::vec3
	*	textureCoords: glm::vec3
	*	indices: vector<unsigned int>
	* }
	*/
	Model(const Mesh& mesh);
	~Model();
	/*
	* Method(Model): Setting up Vertex array, buffer(positions and texture) and indices
	* Following method call other methods in the Model class(genVAo, addVBO, and addEBO)
	*/
	void addData(const Mesh& mesh);
	/*
	* Method(Model): Deleting data after usage
	*/
	void deleteData();
	/*
	* Method(Model): Adding the vertex array object 
	*/
	void genVAO();
	/*
	* Method(Model): Adding the vertex buffer object in to the pipeline
	* 1. setting up the buffer object
	* 2. setting up the attrib pointer for shader operations
	* arg1(dimension): size of type of data size we want the attrib pointer to pass to shader
	* example: vec3: dimesion will be 3
	* arg2(data): data that need to put into pipeline of vertex buffer object
	*/
	void addVBO(
		int dimension,
		const std::vector<float>& data
	);
	/*
	* Method(Model): Adding the element buffer object data in to the pipeline
	*/
	void addEBO(const std::vector<unsigned int>& data);
	/*
	* Method(Model): bind vertex Array object
	*/
	void bindVAO() const;
	/*
	* Method(Model): return total indices count of the model
	*/
	int getIndicesCount() const;

	// Model class Copy action
	Model(Model&& other);
	// Model class Assignment action
	Model& operator=(Model&& other);
private:
	unsigned int m_vao = 0; //--vertex array object id
	int m_vboCount     = 0; //--vertex buffer count(total number buffer object present) 
	int m_indicesCount = 0; //--indices count(total number of indices present)
	std::vector<unsigned int> m_vboBuffers; //--array that stores all the vetex buffer object id's
};

