#include "fpsCounter.h"

FPSCounter::FPSCounter() {
	m_text.move(10, 10);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(2);

	m_font.loadFromFile("assets/fonts/Minecrafter.Reg.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(24);
}
void FPSCounter::update() {
	m_frameCount++;
	if (m_delayTimer.getElapsedTime().asSeconds() > 0.5) {
		m_fps = (int)(m_frameCount / m_fpsTimer.restart().asSeconds());
		m_frameCount = 0;
		m_delayTimer.restart();
	}
}
int FPSCounter::getFPS() const {
	return m_fps;
}

void FPSCounter::renderFps(MainRenderer& mainRenderer) {
	m_text.setString("FPS: " + std::to_string(m_fps));
	mainRenderer.drawFps(m_text);
}