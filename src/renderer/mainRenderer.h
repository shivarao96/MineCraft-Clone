#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "./quadRenderer/quadRenderer.h"
#include "./cubeRenderer/cubeRenderer.h"
#include "./chunkRenderer/chunkRenderer.h"
#include "./skyboxRenderer/skyboxRenderer.h"
#include "./sfmlRenderer/sfmlRenderer.h"

class ChunkMesh;
class Camera;

class MainRenderer
{
public:
	void drawQuads(glm::vec3 pos);
	void drawCubes(const Entity& entity);
	void drawChunk(const ChunkMesh& mesh);
	void drawSky();
	void drawSFMLObj(const sf::Drawable& drawable);
	void finishRenderer(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer   m_quadRenderer;
	CubeRenderer   m_cubeRenderer;
	ChunkRenderer  m_chunkRenderer;
	SkyboxRenderer m_skyboxRenderer;
	SFMLRenderer   m_sfmlRenderer;
	bool m_drawbox = false;
};

