#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "../../model/model.h"
#include "../../texture/textureHandler.h"
#include "../../shaders/basicShader/basicShader.h"
#include "../../entity/entity.h"

class Camera;
class TextureHandler;

class QuadRenderer
{
public:
	QuadRenderer();
	void addAt(const glm::vec3& pos);
	void renderQuads(const Camera& cam);
private:
	glm::mat4 makeModelMatrix(const Entity& entity);
	std::vector<glm::vec3> m_quads;
	Model m_model;
	BasicShader m_basicShader;
	TextureHandler m_textureHandler;
};

