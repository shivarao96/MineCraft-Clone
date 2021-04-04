#pragma once

#include <SFML/Graphics.hpp>
#include "../entity.h"

class World;

class Player : public Entity {
public:
	Player();
	void handleInput(const sf::RenderWindow& window);
	void update(float deltaTime, World& world);
	void collide(World& world, const glm::vec3& vel, float dt);
private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	//glm::vec3 m_velocity = glm::vec3(0);

	bool m_isOnGround = false; // @TODO need to make it as false while init
};