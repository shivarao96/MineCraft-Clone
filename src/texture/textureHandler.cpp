#include "textureHandler.h"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <stdexcept>
#include <iostream>

TextureHandler::TextureHandler(const std::string& fileName) {
	loadFromFile(fileName);
}
TextureHandler::~TextureHandler() {
	glDeleteTextures(1, &m_textureId);
}
void TextureHandler::loadFromFile(const std::string& fileName) {
	sf::Image imgLoader;
	const std::string& filePath = "assets/textures/" + fileName + ".png";
	if (!imgLoader.loadFromFile(filePath)) {
		std::cout << "failed to open texture file::" + filePath << std::endl;
		throw std::runtime_error("failed to open texture file::" + filePath);
	}
	glGenTextures(
		1, 
		&m_textureId
	);
	glBindTexture(
		GL_TEXTURE_2D, 
		m_textureId
	);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		imgLoader.getSize().x,
		imgLoader.getSize().y,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		imgLoader.getPixelsPtr()
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
}
void TextureHandler::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, m_textureId);
}