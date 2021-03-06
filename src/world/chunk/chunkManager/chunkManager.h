#pragma once

#include "../chunk.h"
#include <unordered_map>
#include "../../../math/vector2XZ/vector2XZ.h"

class World;
class ChunkManager
{
public:
	ChunkManager(World& world);
	Chunk& getChunk(int x, int z);
	const std::unordered_map<VectorXZ, Chunk>& getChunks() const;
	bool makeMesh(int x, int z);
	void queueChunk(int x, int z);
	void update();
private:
	std::unordered_map<VectorXZ, Chunk> m_chunks;
	World* m_world;
};	

