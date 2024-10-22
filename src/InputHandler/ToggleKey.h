#pragma once

#include <SFML/Graphics.hpp>

class ToggleKey
{
public:
	ToggleKey(sf::Keyboard::Key key);
	bool isKeyPressed();
private:
	sf::Keyboard::Key m_key;
	sf::Clock m_delayTimer;
};

