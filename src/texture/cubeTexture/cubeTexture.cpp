#include "cubeTexture.h"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

CubeTexture::CubeTexture(const std::array<std::string, 6>& files) {
	loadFromFile(files);
}
void CubeTexture::loadFromFile(const std::array<std::string, 6>& files) {
	glGenTextures(1, &m_texId);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texId);

	for (unsigned int i = 0; i < 6; i++) {
		std::string file = "assets/textures/" + files[i] + ".png" ;
		sf::Image image;
		if (!image.loadFromFile(file)) {
			throw std::runtime_error("failed to load the file::" + file);
		}
		GLenum param = GL_TEXTURE_CUBE_MAP_POSITIVE_X + i;
		int width    = image.getSize().x;
		int height   = image.getSize().y;
		glTexImage2D(
			param,
			0,
			GL_RGBA,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			image.getPixelsPtr()
		);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}
CubeTexture::~CubeTexture() {
	glDeleteTextures(1, &m_texId);
}
void CubeTexture::bindTexture() const {
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texId);
}