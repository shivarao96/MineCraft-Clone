#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "./quadRenderer/quadRenderer.h"

class Camera;

class MainRenderer
{
public:
	void drawQuads(glm::vec3 pos);
	void finishRenderer(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
};

