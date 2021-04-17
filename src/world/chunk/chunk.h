#pragma once

#include <vector>
#include "iChunk/iChunk.h"
#include "chunkSection/chunkSection.h"
#include <SFML/Graphics.hpp>

class World;
class MainRenderer;

/*
* Basically following class is the collection of chunkSection
*/
class Chunk:public IChunk
{
public:
	/*
	*	initialization of chunk
	*/
	Chunk(World& world, sf::Vector2i location);
	/*
	* Method(Chunk): setblock at provided coords
	*/
	void setBlock(int x, int y, int z, ChunkBlock block) override;
	/*
	* Method(Chunk): get the chunk block
	*/
	ChunkBlock getBlock(int x, int y, int z) const override;
	/*
	* Method(Chunk): draw chunksection chunks
	*/
	void drawChunks(MainRenderer& renderer);
	/*
	* Method(Chunk): following function is responsible for creating the mesh based on chunksection data
	* ! : This function is called only once.
	*/
	bool makeMesh();
	/*
	* Method(Chunk): load the chunkblock in the chunksection and also create new instance
	* of chunksection.
	*/
	void load();
	/*
	* Method(Chunk): is the chunk loaded
	*/
	bool hasLoaded() const;
	/*
	* Method(Chunk): get the chunksection
	*/
	ChunkSection& getSection(int index);
private:
	/*
	* Method(Chunk): add the new chunksection
	*/
	void addSection();
	/*
	* Method(chunk): add new chunksection based on index checking
	*/
	void addSectionsBlockTarget(int blockY);
	/*
	* Method(Chunk): check whether we can add new chunksection based on it chunksection vector size and index provided as argument
	*/
	void addSectionsIndexTarget(int index);
	/*
	* Method(Chunk): chunk coord val based on conditions
	*/
	bool outOfBound(int x, int y, int z) const;
	std::vector<ChunkSection> m_chunksSections;
	World* m_pWorld; // world reference
	sf::Vector2i m_location; // chunk location
	bool m_chunkLoaded; // flag for to check whether chunk is loaded or not.
};

