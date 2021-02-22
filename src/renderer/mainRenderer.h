#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "./quadRenderer/quadRenderer.h"
#include "./cubeRenderer/cubeRenderer.h"

class Camera;

class MainRenderer
{
public:
	void drawQuads(glm::vec3 pos);
	void drawCubes(glm::vec3 pos);
	void finishRenderer(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer m_quadRenderer;
	CubeRenderer m_cubeRenderer;
};

