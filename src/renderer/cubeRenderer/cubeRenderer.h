#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../../model/model.h"
#include "../../texture/textureHandler.h"
#include "../../shaders/basicShader/basicShader.h"

class Camera;

class CubeRenderer
{
public:
	CubeRenderer();
	void addAt(const glm::vec3& pos);
	void renderCubes(const Camera& cam);
private:
	std::vector<glm::vec3> m_cubes;
	Model m_model;
	BasicShader m_basicShader;
	TextureHandler m_textureHandler;
};

