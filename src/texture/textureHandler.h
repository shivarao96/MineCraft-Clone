#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "../utility/nonCopyable.h"

class TextureHandler: public NonCopyable
{
public:
	TextureHandler() = default;
	TextureHandler(const std::string& fileName);
	~TextureHandler();
	void loadFromFile(const std::string& fileName);
	void loadFromImage(const sf::Image& img);
	void bindTexture();
private:
	unsigned int m_textureId;
};

