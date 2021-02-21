#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>

class MainRenderer
{
public:
	void drawQuads(glm::vec3 pos);
	void finishRenderer(sf::RenderWindow& window);
};

