#include "context.h"
#include <GL/glew.h>

Context::Context() {
	sf::ContextSettings setting;
	setting.antialiasingLevel = 4;
	setting.majorVersion = 4;
	setting.minorVersion = 4;
	setting.depthBits = 24;
	setting.stencilBits = 8;
	m_window.create(
		{ 1280, 768 },
		"MineCraft",
		sf::Style::Close,
		setting
	);
	glewInit();
	glewExperimental = GL_TRUE;
	glViewport(
		0,
		0,
		1280,
		768
	);
	glCullFace(GL_BACK);
	m_window.setFramerateLimit(90);
}