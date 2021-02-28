#include "cubeRenderer.h"
#include "../../entity/camera/camera.h"
#include <iostream>
#include "../../math/Matrix.h"
#include "../../glActions/glFunctions.h"

CubeRenderer::CubeRenderer():m_texAtlas("DefaultPack"){
	m_textureHandler.loadFromFile("test");
	std::vector<float> vertices = {
		//Back
		 1, 0, 0,
		 0, 0, 0,
		 0, 1, 0,
		 1, 1, 0,

		 //Front
		 0, 0, 1,
		 1, 0, 1,
		 1, 1, 1,
		 0, 1, 1,

		 //Right
		 1, 0, 1,
		 1, 0, 0,
		 1, 1, 0,
		 1, 1, 1,

		 //Left
		 0, 0, 0,
		 0, 0, 1,
		 0, 1, 1,
		 0, 1, 0,

		 //Top
		 0, 1, 1,
		 1, 1, 1,
		 1, 1, 0,
		 0, 1, 0,

		 //Bottom
		 0, 0, 0,
		 1, 0, 0,
		 1, 0, 1,
		 0, 0, 1
	};
	std::vector<float> texTopCoords = m_texAtlas.getTextureCoords({ 0,0 }); // air
	std::vector<float> texSideCoords = m_texAtlas.getTextureCoords({ 1,0 }); // grass
	std::vector<float> texBottomCoords = m_texAtlas.getTextureCoords({ 2,0 }); // dirt
	std::vector<float> texCoords;
	texCoords.insert(texCoords.end(), texSideCoords.begin(), texSideCoords.end());
	texCoords.insert(texCoords.end(), texSideCoords.begin(), texSideCoords.end());
	texCoords.insert(texCoords.end(), texSideCoords.begin(), texSideCoords.end());
	texCoords.insert(texCoords.end(), texSideCoords.begin(), texSideCoords.end());
	texCoords.insert(texCoords.end(), texTopCoords.begin(), texTopCoords.end());
	texCoords.insert(texCoords.end(), texBottomCoords.begin(), texBottomCoords.end());
	/*{
		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0
	};*/
	std::vector<unsigned int> indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};
	m_model.addData({
		vertices,
		texCoords,
		indices
	});
}
void CubeRenderer::addAt(const glm::vec3& pos) {
	m_cubes.push_back(pos);
}
void CubeRenderer::renderCubes(const Camera& cam) {
	m_basicShader.useShader();
	m_texAtlas.bindTexture();
	//m_textureHandler.bindTexture();
	m_model.bindVAO();
	//m_basicShader.setInt("texSampler", 0);
	//glActiveTexture(GL_TEXTURE0);
	m_basicShader.loadProjectionMatrix(cam.getProjectionMatrix());
	m_basicShader.loadViewMatrix(cam.getViewMatrix());

	for (auto& cube : m_cubes) {
		m_basicShader.loadModelMatrix(
			makeModelMatrix({ cube, glm::vec3(0,0,0) })
		);
		GlFunctions::drawElements(m_model.getIndicesCount());
	}
	m_cubes.clear();
}