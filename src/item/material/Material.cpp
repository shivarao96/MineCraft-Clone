#include "Material.h"

const Material Material::NOTHING		(ID::Nothing, 0, false, "None");
const Material Material::GRASS_BLOCK	(ID::Grass, 99, true, "Grass Block");
const Material Material::DIRT_BLOCK		(ID::Dirt, 99, true, "Dirt Block");
const Material Material::STONE_BLOCK	(ID::Stone, 99, true, "Stone Block");
const Material Material::BARK_BLOCK		(ID::Bark, 99, true, "Bark");
const Material Material::LEAF_BLOCK		(ID::Leaf, 99, true, "Leaf");
const Material Material::SAND_BLOCK     (ID::Sand, 99, true, "Sand");
const Material Material::CACTUS_BLOCK   (ID::Cactus, 99, true, "Cactus");
const Material Material::ROSE			(ID::Rose, 99, true, "Rose");
const Material Material::TALL_GRASS     (ID::TallGrass, 99, true, "Tall Grass");
const Material Material::DEAD_PLANT     (ID::DeadPlant, 99, true, "Dead Plant");

Material::Material(
	Material::ID materialId,
	int maxStack,
	bool isBlock,
	std::string&& name
) 
	:materialId(materialId)
	, maxStack(maxStack)
	, isBlock(isBlock)
	, name(name)
{}

BlockId Material::toBlockId() const {
	switch (materialId)
	{
		case Nothing:
			return BlockId::AIR;
		case Grass:
			return BlockId::GRASS;
		case Dirt:
			return BlockId::DIRT;
		case Stone:
			return BlockId::STONE;
		case Bark:
			return BlockId::OAKBARK;
		case Leaf:
			return BlockId::OAKLEAF;
		case Sand:
			return BlockId::SAND;
		case Cactus:
			return BlockId::CACTUS;
		case TallGrass:
			return BlockId::TALLGRASS;
		case Rose:
			return BlockId::ROSE;
		case DeadPlant:
			return BlockId::DEADPLANT;
	}
}

const Material& Material::toMaterial(BlockId block) {
	switch (block)
	{
		case BlockId::AIR:
			return NOTHING;
		case BlockId::GRASS:
			return GRASS_BLOCK;
		case BlockId::DIRT:
			return DIRT_BLOCK;
		case BlockId::STONE:
			return STONE_BLOCK;
		case BlockId::OAKBARK:
			return BARK_BLOCK;
		case BlockId::OAKLEAF:
			return LEAF_BLOCK;
		case BlockId::SAND:
			return SAND_BLOCK;
		case BlockId::CACTUS:
			return CACTUS_BLOCK;
		case BlockId::ROSE:
			return ROSE;
		case BlockId::DEADPLANT:
			return DEAD_PLANT;
		case BlockId::TALLGRASS:
			return TALL_GRASS;
		default:
			return NOTHING;
	}
}