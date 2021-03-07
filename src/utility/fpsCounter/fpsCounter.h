#pragma once

#include <SFML/Graphics.hpp>
#include "../../renderer/mainRenderer.h"

class FPSCounter
{
public:
	FPSCounter();
	void update();
	int getFPS() const;
	void renderFps(MainRenderer& mainRenderer);
private:
	sf::Text m_text;
	sf::Font m_font;

	sf::Clock m_delayTimer;
	sf::Clock m_fpsTimer;

	int m_fps;
	int m_frameCount;
};

