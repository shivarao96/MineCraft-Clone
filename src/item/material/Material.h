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
		Leaf,
		Sand,
		Cactus,
		Rose,
		TallGrass,
		DeadPlant
	};

	const static Material NOTHING,
		GRASS_BLOCK,
		DIRT_BLOCK,
		STONE_BLOCK,
		BARK_BLOCK,
		LEAF_BLOCK,
		SAND_BLOCK,
		CACTUS_BLOCK,
		ROSE,
		TALL_GRASS,
		DEAD_PLANT;

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
