#include "chunkShader.h"

ChunkShader::ChunkShader()
	:BasicShader("chunkShader", "chunkShader")
{
	getUniform();
}

void ChunkShader::getUniform() {
	BasicShader::getUniform();
}