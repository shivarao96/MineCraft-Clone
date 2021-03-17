#pragma once

#include "../chunk.h"
#include <unordered_map>
#include "../../../math/vector2XZ/vector2XZ.h"

class World;

using ChunkMap = std::unordered_map<VectorXZ, Chunk>;

class ChunkManager
{
public:
	ChunkManager(World& world);
	Chunk& getChunk(int x, int z);
	
	ChunkMap& getChunks();
	
	bool makeMesh(int x, int z);

	bool chunkLoadedAt(int x, int z) const;
	bool chunkExistAt(int x, int z) const;

	void loadChunk(int x, int z);
	void unLoadChunk(int x, int z);
private:
	World* m_world;

	ChunkMap m_chunkMap; // new
};	

