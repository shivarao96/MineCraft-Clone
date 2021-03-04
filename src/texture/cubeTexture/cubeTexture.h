#pragma once

#include "../../utility/nonCopyable.h"
#include <array>
#include <string>

class CubeTexture: public NonCopyable
{
public:
	CubeTexture() = default;
	CubeTexture(const std::array<std::string, 6>& files);
    /*
       MUST BE IN THIS ORDER:
        -right
        -left
        -top
        -bottom
        -back
        -front
    */
	void loadFromFile(const std::array<std::string, 6>& files);
	~CubeTexture();
	void bindTexture() const;
private:
	unsigned int m_texId;
};

