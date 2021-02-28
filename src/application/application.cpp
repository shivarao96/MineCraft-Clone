#include "application.h"
#include "../states/playerState/playState.h"
#include <iostream>

Application::Application(const std::string& name) {
	pushState<PlayState>(*this);
}
void Application::runApp() {
	sf::Clock dtTimer;
	while (m_context.m_window.isOpen() && !m_states.empty())
	{
		auto deltaTime = dtTimer.restart();
		auto& state = *m_states.back();
		state.handleInputs();
		state.update(deltaTime.asSeconds());
		m_camera.update();

		if (state.isStateInitialized()) {
			state.render(m_mainRenderer);
		}
		m_mainRenderer.finishRenderer(m_context.m_window, m_camera);

		handleEvents();
		if (m_shouldPopState) {
			m_states.pop_back();
			m_shouldPopState = false;
		}
	}
}
//template<typename T, typename... Args>
//void Application::pushState(Args&&... args) 
void Application::popState() {
	m_shouldPopState = true;
}
Camera& Application::getCamera() {
	return m_camera;
}
const sf::RenderWindow& Application::getWindow() const{
	return m_context.m_window;
}
void Application::handleEvents() {
	sf::Event e;
	while (m_context.m_window.pollEvent(e)) {
		switch (e.type)
		{
		case sf::Event::Closed:
			m_context.m_window.close();
			break;
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				m_context.m_window.close();
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
