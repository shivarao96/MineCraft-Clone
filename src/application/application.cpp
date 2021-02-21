#include "application.h"
#include "../states/playerState/playState.h"
#include "../shaders/basicShader/basicShader.h"

Application::Application(const std::string& name) {
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
	m_window.setFramerateLimit(90);
	pushState<PlayState>(*this);
	BasicShader basicShader;
}
void Application::runApp() {
	sf::Clock dtTimer;
	while (m_window.isOpen() && !m_states.empty())
	{
		auto deltaTime = dtTimer.restart();
		auto& state = *m_states.back();
		state.handleInputs();
		state.update(deltaTime.asSeconds());
		state.render(m_mainRenderer);
		m_camera.update();
		m_mainRenderer.finishRenderer(m_window);

		handleEvents();
		if (m_shouldPopState) {
			m_states.pop_back();
			m_shouldPopState = false;
		}
	}
}
template<typename T, typename... Args>
void Application::pushState(Args&&... args) {
	m_states.push_back(
		std::make_unique<T>(std::forward<Args>(args)...)
	);
}
void Application::popState() {
	m_shouldPopState = true;
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
