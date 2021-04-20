#include "mainRenderer.h"
#include <GL/glew.h>
#include "../world/chunk/chunkMesh/chunkMesh.h"

void MainRenderer::drawQuads(glm::vec3 pos) {
	m_quadRenderer.addAt({ 0,0,0 });
}
void MainRenderer::drawCubes(const Entity& entity) {
	m_cubeRenderer.addAt(entity);
}
void MainRenderer::drawChunk(const ChunkMesh& mesh) {
	if (mesh.getFaceCount() > 0) {
		m_chunkRenderer.add(mesh);
	}
}
void MainRenderer::drawSky() {
	m_drawbox = true;
}
void MainRenderer::drawSFMLObj(const sf::Drawable& drawable) {
	m_sfmlRenderer.add(drawable);
}
void MainRenderer::finishRenderer(sf::RenderWindow& window, const Camera& camera) {
	glClearColor(
		0.1,
		0.5,
		1.0,
		1.0
	);
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT
	);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//m_quadRenderer.renderQuads(camera);
	//m_cubeRenderer.renderCubes(camera);
	m_chunkRenderer.render(camera);

	if (m_drawbox) {
		glDisable(GL_CULL_FACE);
		m_skyboxRenderer.renderSkyBox(camera);
		m_drawbox = false;
	}

	m_sfmlRenderer.render(window);

	window.display();
}