#pragma once

#include "chunk/iChunk/iChunk.h"
#include "chunk/chunk.h"
#include <vector>
#include "./chunk/chunkManager/chunkManager.h"
#include <unordered_set>
#include "./event/IWorldEvent.h"
#include "../entity/camera/camera.h"

#include <atomic>
#include <thread>

class MainRenderer;
class Camera;

class World
{
public:
	/*
	* Initialize the member var : chunkmanager
	*/
	World(const Camera& cam);
	~World();
	/*
	* Method(World): following function gets the chunks from chunkmanager
	* and loop through the chunks and draws them.
	* arg(renderer): Mainrender class for drawing all the chunks
	*/
	void renderWorld(MainRenderer& renderer, const Camera& cam);
	/*
	* Method(World): set the required blocktype at certain pos of the block
	*/
	void setBlock(int x, int y, int z, ChunkBlock block);
	/*
	* Method(World): get the chunk block at certain location
	*/
	ChunkBlock getBlock(int x, int y, int z);
	/*
	* Method(World): Update the chunks
	*/
	void update(const Camera& cam);

	/*
	* Method(World): fetch the chunk manager
	*/
	ChunkManager& getChunkManager();
	/*
	* Method(World): get the Chunkblock position
	*/
	static VectorXZ getBlock(int x, int z);
	/*
	* Method(World):get the chunk position
	*/
	static VectorXZ getChunk(int x, int z);

	/*
	* Method(World): template based method to register the user event (ex: editing the blocks )
	*/
	template<typename T, typename ...Args>
	void addEvent(Args&&... args) {
		m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
	/*
	* Method(World): update the chunkblock at certain pos
	*/
	void updateChunk(int blockX, int blockY, int blockZ);

private:
	void loadChunks(const Camera& cam);
	/*
	* Method(World): Update the edited chunksections
	*/
	void updateChunks();

	std::vector<std::unique_ptr<IWorldEvent>> m_events;
	ChunkManager m_chunkManager;
	std::unordered_set<sf::Vector3i> m_rebuildChunks;
	std::unordered_map<sf::Vector3i, ChunkSection*> m_chunkSectionUpdates; // these are the chunksection that got updated
	int m_loadDistance = 2;

	//std::atomic<bool> m_isRunning{ true };
	//std::thread m_thread;
};

