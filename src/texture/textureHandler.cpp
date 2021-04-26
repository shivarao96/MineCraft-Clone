#include "textureHandler.h"
#include <GL/glew.h>
#include <stdexcept>
#include <iostream>

TextureHandler::TextureHandler(const std::string& fileName) {
	loadFromFile(fileName);
}
TextureHandler::~TextureHandler() {
	glDeleteTextures(1, &m_textureId);
}
void TextureHandler::loadFromImage(const sf::Image& img) {
	glGenTextures(
		1,
		&m_textureId
	);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(
		GL_TEXTURE_2D,
		m_textureId
	);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		img.getSize().x,
		img.getSize().y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		img.getPixelsPtr()
	);

	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S,
		GL_CLAMP_TO_EDGE
	);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T,
		GL_CLAMP_TO_EDGE
	);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MIN_FILTER,
		GL_NEAREST
	);
	glTexParameteri(
		GL_TEXTURE_2D,
		GL_TEXTURE_MAG_FILTER,
		GL_NEAREST
	);
	//glGenerateMipmap(GL_TEXTURE_2D);
}
void TextureHandler::loadFromFile(const std::string& fileName) {
	sf::Image imgLoader;
	const std::string& filePath = "assets/textures/" + fileName + ".png";
	if (!imgLoader.loadFromFile(filePath)) {
		std::cout << "failed to open texture file::" + filePath << std::endl;
		throw std::runtime_error("failed to open texture file::" + filePath);
	}
	loadFromImage(imgLoader);
}
void TextureHandler::bindTexture(){
	
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}