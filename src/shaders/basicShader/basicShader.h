#pragma once

#include "../shader.h"

class BasicShader:public Shader
{
public:
	BasicShader(
		const std::string& vertexShaderFile = "basicShader",
		const std::string& fragmentShaderFile = "basicShader"
	);
	void loadProjectionMatrix (const glm::mat4& projectionMatrix);
	void loadViewMatrix       (const glm::mat4& viewMatrix);
	void loadModelMatrix      (const glm::mat4& modelMatrix);
private:
	virtual void getUniform() override;
};

