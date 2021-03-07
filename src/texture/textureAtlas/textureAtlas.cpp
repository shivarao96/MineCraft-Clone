#include "textureAtlas.h"
#include <iostream>


TextureAtlas::TextureAtlas(const std::string& atlasFileName) {
	sf::Image i;
	if (!i.loadFromFile("assets/textures/" + atlasFileName + ".png")) {
		std::cout << "Failed to load atlas file::" + atlasFileName << std::endl;
		throw std::runtime_error("Failed to load atlas file");
	}
	loadFromImage(i);
	m_imageSize         = 256;
	m_indivisualTexSize = 16;
}
std::vector<float> TextureAtlas::getTextureCoords(const sf::Vector2i& texCoord) {
	static const float texPerRow = (float)m_imageSize / (float)m_indivisualTexSize;
	static const float texSize   = 1.0f / texPerRow;
	static const float pixelSize = 1.0f / (float)m_imageSize;
	float offset = (0.5 * pixelSize);

	float xMin = (texCoord.x * texSize) + offset;
	float yMin = (texCoord.y * texSize) + offset;
	float xMax = (xMin + texSize) - offset;
	float yMax = (yMin + texSize) - offset;

	return {
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
}