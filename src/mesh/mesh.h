#pragma once

/*
* Mesh class representing the DS with following data:
* 1. vertexPositions: position in 3D world
* 2. textureCoordinates: texture for the vertex side.
* 3. indices: to represents the correct index without having duplicate vertices
*/

#include <vector>

class Mesh {
public:
	std::vector<float> vertexPositions;
	std::vector<float> textureCoordinates;
	std::vector<unsigned int> indices;
	
	// clearing the data
	void clearData();
};