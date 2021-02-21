#pragma once

#include <string>

class TextureHandler
{
public:
	TextureHandler() = default;
	TextureHandler(const std::string& fileName);
	~TextureHandler();
	void loadFromFile(const std::string& fileName);
	void bindTexture();
private:
	unsigned int m_textureId;
};

