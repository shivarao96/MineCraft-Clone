#include "glFunctions.h"
#include <iostream>

void GlFunctions::drawElements(unsigned int indicesCount) {
	glDrawElements(
		GL_TRIANGLES,
		indicesCount,
		GL_UNSIGNED_INT,
		nullptr
	);
}