#include "basicShader.h"

BasicShader::BasicShader(
	const std::string& vertexShaderFile,
	const std::string& fragmentShaderFile
):Shader(
	vertexShaderFile, 
	fragmentShaderFile
)
{
	getUniform();
}
void BasicShader::loadProjectionMatrix(const glm::mat4& projectionMatrix) {
	setMat4("projection", projectionMatrix);
}
void BasicShader::loadViewMatrix(const glm::mat4& viewMatrix) {
	setMat4("view", viewMatrix);
}
void BasicShader::loadModelMatrix(const glm::mat4& modelMatrix) {
	setMat4("model", modelMatrix);
}
void BasicShader::getUniform() {
	useShader();
}