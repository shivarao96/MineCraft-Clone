#pragma once

#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include "./quadRenderer/quadRenderer.h"
#include "./cubeRenderer/cubeRenderer.h"
#include "./chunkRenderer/chunkRenderer.h"
#include "./skyboxRenderer/skyboxRenderer.h"
#include "./sfmlRenderer/sfmlRenderer.h"
#include "./waterRenderer/WaterRenderer.h"

class ChunkMesh;
class Camera;
class ChunkSection;

class MainRenderer
{
public:
	void drawQuads(glm::vec3 pos);
	void drawCubes(const Entity& entity);
	void drawChunk(const ChunkSection& mesh);
	void drawSky();
	void drawSFMLObj(const sf::Drawable& drawable);
	void finishRenderer(sf::RenderWindow& window, const Camera& camera);
private:
	QuadRenderer   m_quadRenderer;
	CubeRenderer   m_cubeRenderer;
	ChunkRenderer  m_chunkRenderer;
	SkyboxRenderer m_skyboxRenderer;
	SFMLRenderer   m_sfmlRenderer;
	WaterRenderer m_waterRenderer;
	bool m_drawbox = false;
};

