#pragma once

/*
Following header is used the specifying or adding id of each type of block
Every block will have unqiue id(can be used for extracing the data: texture data from the DB)
*/

#include <cstdint>

using block_t = uint8_t;

enum class BlockId : block_t {
	AIR,
	GRASS,
	DIRT,
	STONE,
	OAKBARK,
	OAKLEAF,

	NUM_TYPES
};