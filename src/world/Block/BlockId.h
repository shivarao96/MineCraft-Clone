#pragma once

/*
Following header is used the specifying or adding id of each type of block
Every block will have unqiue id(can be used for extracing the data: texture data from the DB)
*/

#include <cstdint>

using block_t = uint8_t;

enum class BlockId : block_t {
	AIR = 0,
	GRASS = 1,
	DIRT = 2,
	STONE = 3,
	OAKBARK = 4,
	OAKLEAF = 5,
	SAND = 6,
	WATER = 7,

	NUM_TYPES
};