#pragma once

#include "../basicShader/basicShader.h"

class ChunkShader: public BasicShader
{
public:
	ChunkShader();
private:
	void getUniform() override;
};

