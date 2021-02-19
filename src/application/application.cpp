#include "application.h"

Application::Application(const std::string& name) {
	sf::ContextSettings setting;
	setting.antialiasingLevel = 4;
	setting.majorVersion = 4;
	setting.minorVersion = 4;
	setting.depthBits = 24;
	setting.stencilBits = 8;
	m_window.create({ 1280, 768 }, "MineCraft", sf::Style::Close, setting);
	glViewport(0, 0, 1280, 768);
	m_window.setFramerateLimit(90);
}
void Application::runApp() {
	sf::Clock dtTimer;
	while (m_window.isOpen())
	{
		glClearColor(0.1, 0.5, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		m_window.display();
		handleEvents();
	}
}
void Application::pushState() {

}
void Application::popState() {

}
Camera& Application::getCamera() {
	return m_camera;
}
const sf::RenderWindow& Application::getWindow() const{
	return m_window;
}
void Application::handleEvents() {
	sf::Event e;
	while (m_window.pollEvent(e)) {
		switch (e.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_window.close();
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
}
