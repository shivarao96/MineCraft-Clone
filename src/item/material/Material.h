#pragma once

#include <string>
#include "../../utility/nonCopyable.h"
#include "../../world/Block/BlockId.h"

struct Material : public NonCopyable
{
	enum  ID
	{
		Nothing,
		Grass,
		Dirt,
		Stone,
		Bark,
		Leaf
	};

	const static Material NOTHING,
		GRASS_BLOCK,
		DIRT_BLOCK,
		STONE_BLOCK,
		BARK_BLOCK,
		LEAF_BLOCK;	

	static const Material& toMaterial(BlockId block);

	Material(
		Material::ID materialId,
		int maxStack,
		bool isBlock,
		std::string&& name
	);

	BlockId toBlockId() const;

	const Material::ID materialId;
	const int maxStack;
	const bool isBlock;
	const std::string name;
};
