#pragma once

#include "chunk/iChunk/iChunk.h"
#include "chunk/chunk.h"
#include <vector>
#include "./chunk/chunkManager/chunkManager.h"
#include <unordered_set>
#include "./event/IWorldEvent.h"

class MainRenderer;
class Camera;

class World
{
public:
	World();
	void renderWorld(MainRenderer& renderer);
	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);
	void update(const Camera& cam);

	const ChunkManager& getChunkManager() const;
	static VectorXZ getBlock(int x, int z);
	static VectorXZ getChunk(int x, int z);

	template<typename T, typename ...Args>
	void addEvent(Args&&... args) {
		m_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}
private:
	void renderedUpdatedSections();
	std::vector<std::unique_ptr<IWorldEvent>> m_events;
	ChunkManager m_chunkManager;
	std::unordered_set<sf::Vector3i> m_rebuildChunks;
};

