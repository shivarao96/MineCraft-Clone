#pragma once

/*
Following class returns the data regarding the texture coordinates based on block info
*/

#include <string>
#include <SFML/Graphics.hpp>
#include "../../../utility/nonCopyable.h"
#include "../BlockId.h"


class BlockDataHolder : public NonCopyable
{
public:
	sf::Vector2i texTopCoords;
	sf::Vector2i texSideCoords;
	sf::Vector2i texBottomCoords;
	BlockId id;
	bool isOpaque;
};

class BlockData : public NonCopyable {
public:
	BlockData(const std::string& blockName);
	const BlockDataHolder& getBlockData() const;
private:
	BlockDataHolder m_blockDataHolder;
};
