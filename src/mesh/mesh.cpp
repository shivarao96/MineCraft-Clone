#include "mesh.h"


void Mesh::clearData() {
	vertexPositions.clear();
	textureCoordinates.clear();
	indices.clear();

	vertexPositions.shrink_to_fit();
	textureCoordinates.shrink_to_fit();
	indices.shrink_to_fit();
}