#pragma once

#include <SFML/Graphics.hpp>
#include "../../renderer/mainRenderer.h"
#include "../entity.h"

class World;

class Player : public Entity {
public:
	Player();
	void handleInput(const sf::RenderWindow& window);
	void update(float deltaTime, World& world);
	void collide(World& world, const glm::vec3& vel, float dt);
	void renderPlayMode(MainRenderer& mainRenderer);
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	//glm::vec3 m_velocity = glm::vec3(0);

	bool m_isOnGround = false; // @TODO need to make it as false while init
	bool m_debugMode = false;

	sf::Text m_text;
	sf::Font m_font;
};