#pragma once

#include "../shader.h"

class SkyboxShader: public Shader
{
public:
	SkyboxShader();
	void loadProjectionMatrix(const glm::mat4& projectionMatrix);
	void loadViewMatrix(glm::mat4& viewMatrix);
private:
	void getUniform() override;
};

