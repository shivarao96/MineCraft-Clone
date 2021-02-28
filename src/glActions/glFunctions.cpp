#include "glFunctions.h"
#include <GL/glew.h>
#include <iostream>

void GlFunctions::drawElements(unsigned int indicesCount) {
	glDrawElements(
		GL_TRIANGLES,
		indicesCount,
		GL_UNSIGNED_INT,
		nullptr
	);
}