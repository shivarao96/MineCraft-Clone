#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../../model/model.h"
#include "../../entity/entity.h"
#include "../../texture/textureHandler.h"
#include "../../shaders/basicShader/basicShader.h"
#include "../../texture/textureAtlas/textureAtlas.h"

class Camera;

class CubeRenderer
{
public:
	CubeRenderer();
	void addAt(const Entity& entity);
	void renderCubes(const Camera& cam);
private:
	std::vector<const Entity*> m_cubes;
	Model m_model;
	BasicShader m_basicShader;
	TextureHandler m_textureHandler;
	TextureAtlas m_texAtlas;
};

