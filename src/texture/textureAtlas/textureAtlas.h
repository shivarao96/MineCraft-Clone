#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../textureHandler.h"


class TextureAtlas:  public TextureHandler
{
public:
	TextureAtlas(const std::string& atlasFileName);
	std::vector<float> getTextureCoords(const sf::Vector2i& texCoord);

private:
	int m_imageSize;
	int m_indivisualTexSize;
};

