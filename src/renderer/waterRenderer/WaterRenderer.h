#pragma once

#include <vector>
#include "../../shaders/chunkShader/chunkShader.h"

class ChunkMesh;
class Camera;

class WaterRenderer
{
public:
	void add(const ChunkMesh& mesh);
	void render(const Camera& camera);
private:
	std::vector<const ChunkMesh*> m_chunkMeshes;
	ChunkShader m_chunkShader;
};


