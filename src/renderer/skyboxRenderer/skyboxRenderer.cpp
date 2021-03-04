#include "skyboxRenderer.h"
#include <vector>
#include "../../entity/camera/camera.h"
#include "../../glActions/glFunctions.h"

SkyboxRenderer::SkyboxRenderer() {
	constexpr int CUBE_SIZE = 500;
	std::vector<float> cubeVertices = {
		 //Back
		  CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		 -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		 -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,
		  CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,

		 //Front
		 -CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
		  CUBE_SIZE, -CUBE_SIZE, CUBE_SIZE,
		  CUBE_SIZE,  CUBE_SIZE, CUBE_SIZE,
		 -CUBE_SIZE,  CUBE_SIZE, CUBE_SIZE,

		 //Right
		 CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,
		 CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		 CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,
		 CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,

		 //Left
		 -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		 -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,
		 -CUBE_SIZE,  CUBE_SIZE,  CUBE_SIZE,
		 -CUBE_SIZE,  CUBE_SIZE, -CUBE_SIZE,

		 //Top
		 -CUBE_SIZE, CUBE_SIZE,  CUBE_SIZE,
		  CUBE_SIZE, CUBE_SIZE,  CUBE_SIZE,
		  CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,
		 -CUBE_SIZE, CUBE_SIZE, -CUBE_SIZE,

		 //Bottom
		 -CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		  CUBE_SIZE, -CUBE_SIZE, -CUBE_SIZE,
		  CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE,
		 -CUBE_SIZE, -CUBE_SIZE,  CUBE_SIZE
	};
	std::vector<unsigned int> cubeIndices = {
		0,  1, 2,
		2,  3, 0,
		
		4,  5, 6,
		6,  7, 4,

		8,  9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	m_skyboxModel.genVAO();
	m_skyboxModel.addVBO(3, cubeVertices);
	m_skyboxModel.addEBO(cubeIndices);

	m_skyboxTexture.loadFromFile({
		"middlesb",
		"middlesb",
		"topsb",
		"bottomsb",
		"middlesb",
		"middlesb",
	});
}
void SkyboxRenderer::renderSkyBox(const Camera& camera) {
	m_skyboxShader.useShader();
	m_skyboxModel.bindVAO();
	m_skyboxTexture.bindTexture();

	m_skyboxShader.loadProjectionMatrix(camera.getProjectionMatrix());
	auto camViewMat = camera.getViewMatrix();
	m_skyboxShader.loadViewMatrix(camViewMat);

	GlFunctions::drawElements(m_skyboxModel.getIndicesCount());
}