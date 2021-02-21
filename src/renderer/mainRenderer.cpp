#include "mainRenderer.h"
#include <GL/glew.h>

void MainRenderer::drawQuads(glm::vec3 pos) {

}
void MainRenderer::finishRenderer(sf::RenderWindow& window) {
	glClearColor(
		0.1,
		0.5,
		1.0,
		1.0
	);
	glClear(
		GL_COLOR_BUFFER_BIT |
		GL_DEPTH_BUFFER_BIT |
		GL_STENCIL_BUFFER_BIT
	);

	// do drawing stuff

	window.display();
}