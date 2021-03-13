#pragma once

#include <vector>
#include "iChunk/iChunk.h"
#include "chunkSection/chunkSection.h"
#include <SFML/Graphics.hpp>

class World;
class MainRenderer;

class Chunk:public IChunk
{
public:
	Chunk(World& world, sf::Vector2i location);
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	ChunkBlock getBlock(int x, int y, int z) const override;
	void drawChunks(MainRenderer& renderer);
	bool makeMesh();
	void load();
	bool hasLoaded() const;
	ChunkSection& getSection(int index);
private:
	void addSection();
	void addSectionsBlockTarget(int blockY);
	void addSectionsIndexTarget(int index);

	bool outOfBound(int x, int y, int z) const;
	std::vector<ChunkSection> m_chunksSections;
	World* m_pWorld;
	sf::Vector2i m_location;
	bool m_chunkLoaded;
};

