#include "mainRenderer.h"
#include <GL/glew.h>

void MainRenderer::drawQuads(glm::vec3 pos) {
	m_quadRenderer.addAt({ 0,0,0 });
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

	m_quadRenderer.renderQuads(camera);

	window.display();
}