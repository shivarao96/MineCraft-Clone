#include "skyboxShader.h"

SkyboxShader::SkyboxShader( 
): Shader("skyboxShader", "skyboxShader") {
	getUniform();
}
void SkyboxShader::loadProjectionMatrix(const glm::mat4& projectionMatrix) {
	setMat4("projection", projectionMatrix);
}
void SkyboxShader::loadViewMatrix(glm::mat4& viewMatrix) {
	viewMatrix[3][0] = 0;
	viewMatrix[3][1] = 0;
	viewMatrix[3][2] = 0;

	setMat4("view", viewMatrix);
}
void SkyboxShader::getUniform() {
	useShader();
}