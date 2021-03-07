#include "sfmlRenderer.h"

#include <GL/glew.h>

void SFMLRenderer::add(const sf::Drawable& draw) {
	m_draws.push_back(&draw);
}
void SFMLRenderer::render(sf::RenderWindow& window) {
	if (m_draws.empty())
		return;


	reset();
	window.pushGLStates();
	window.resetGLStates();

	for (auto& drawer : m_draws) {
		window.draw(*drawer);
	}
	window.popGLStates();
	m_draws.clear();
}

void SFMLRenderer::reset() {
	glDisable(GL_DEPTH_TEST);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}