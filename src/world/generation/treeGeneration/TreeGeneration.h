#pragma once
#ifndef __TREE_GENERATION__
#define __TREE_GENERATION__

#include "../../../utility/randomGenerator/random.h"
class Chunk;
void makeOakTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);
void makePamTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);
void makeCactusTree(Chunk& chunk, Random<std::minstd_rand>& rand, int x, int y, int z);

#endif // !__TREE_GENERATION__


