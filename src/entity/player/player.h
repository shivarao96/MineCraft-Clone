#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "../../renderer/mainRenderer.h"
#include "../entity.h"
#include "../../item/itemStack/ItemStack.h"
#include "../../InputHandler/ToggleKey.h"


class World;

class Player : public Entity {
public:
	Player();
	void handleInput(const sf::RenderWindow& window);
	void update(float deltaTime, World& world);
	void collide(World& world, const glm::vec3& vel, float dt);
	void draw(MainRenderer& mainRenderer);
	void addItem(const Material& material);
	ItemStack& getHeldItems();

private:
	void keyboardInput();
	void mouseInput(const sf::RenderWindow& window);
	//glm::vec3 m_velocity = glm::vec3(0);

	bool m_isOnGround = false; // @TODO need to make it as false while init
	bool m_debugMode = false;

	sf::Text m_playModetext;
	sf::Font m_font;

	std::vector<ItemStack> m_items;
	std::vector<sf::Text> m_itemText;
	int m_heldItem = 0;

	ToggleKey m_keyUp;
	ToggleKey m_keyDown;
};