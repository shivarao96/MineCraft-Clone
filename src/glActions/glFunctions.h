#pragma once
#include <GL/glew.h>

namespace GlFunctions
{
	void drawElements(unsigned int indicesCount);
	namespace Enum {
		enum Texture {
			Tex2D = GL_TEXTURE_2D,
			TexCubeMap = GL_TEXTURE_CUBE_MAP
		};
	}
};

