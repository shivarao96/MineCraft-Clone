#pragma once


#include <string>
#include <SFML/Graphics.hpp>
#include "../../../utility/nonCopyable.h"
#include "../BlockId.h"

enum class BlockMeshType {
	Cube = 0,
	X = 1
};

/*
* Inherited From: NonCopyable
* Following class holds the texture coords(top, side & bottom) of any blockid
*/

class BlockDataHolder : public NonCopyable
{
public:
	sf::Vector2i texTopCoords; // top coords
	sf::Vector2i texSideCoords; // side coords
	sf::Vector2i texBottomCoords;// bottom coords
	BlockId id;// id (BlockId)
	bool isOpaque; // opaque param
	BlockMeshType meshType;
};

/*
* Inherited From: NonCopyable
* Following class holds the texture coords info when a .block file is provided.
*/
class BlockData : public NonCopyable {
public:
	/*
	* following constructor takes .block file and extract the texture coordinates
	*/
	BlockData(const std::string& blockName);
	/*
	* Method(BlockData): returns the BlockDataHolder DS
	*/
	const BlockDataHolder& getBlockData() const;
private:
	BlockDataHolder m_blockDataHolder; // private var for storing the block info
};
