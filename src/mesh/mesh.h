#pragma once

#include <vector>

class Mesh {
public:
	std::vector<float> vertexPositions;
	std::vector<float> textureCoordinates;
	std::vector<unsigned int> indices;
	
	void clearData();
};