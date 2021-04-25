#include "player.h"
#include <GL/glew.h>
#include "../../world/worldConstant.h"
#include "../../world/world.h"
#include <iostream>

Player::Player()
	: Entity({ 25,125,25 }, { 0,0,0 }, { 0.5, 1, 0.5 })
	, m_keyDown(sf::Keyboard::Down)
	,m_keyUp(sf::Keyboard::Up)
{
	m_font.loadFromFile("assets/fonts/Minecrafter.Reg.ttf");
	
	for (int i = 0; i < 5; i++) {
		m_items.emplace_back(Material::NOTHING, 0);
	}

	for (int i = 0; i < 5; i++) {
		//sfml text
		sf::Text t;
		t.setOutlineColor(sf::Color::Black);
		t.setOutlineThickness(2);
		t.setFont(m_font);
		t.setCharacterSize(25);
		t.setPosition({10, (float)(30 * i + 100)});
		m_itemText.push_back(t);
	}

	m_playModetext.setOutlineColor(sf::Color::Black);
	m_playModetext.setOutlineThickness(2);
	m_playModetext.setFont(m_font);
	m_playModetext.setCharacterSize(24);
	m_playModetext.move(10, 40);

}
void Player::handleInput(const sf::RenderWindow& window) {

	if (m_keyDown.isKeyPressed()) {
		m_heldItem++;
		if (m_heldItem == m_items.size()) {
			m_heldItem = 0;
		}
	}
	else if (m_keyUp.isKeyPressed()) {
		m_heldItem--;
		if (m_heldItem == -1) {
			m_heldItem = m_items.size() - 1;
		}
	}

	keyboardInput();
	mouseInput(window);
}
void Player::update(float deltaTime, World& world) {
	
	if (!m_isOnGround && !m_debugMode) { // if not on ground 
		m_velocity.y -= 100 * deltaTime;
	}
	m_isOnGround = false;
	
	m_velocity.x *= 0.95;
	m_velocity.z *= 0.95;
	m_velocity.y *= 0.95;
	
	m_position.x += m_velocity.x * deltaTime;
	if(!m_debugMode) { collide(world, { m_velocity.x, 0, 0 }, deltaTime); }
	m_position.y += m_velocity.y * deltaTime;
	if (!m_debugMode) { collide(world, { 0, m_velocity.y, 0 }, deltaTime); }
	m_position.z += m_velocity.z * deltaTime;
	if (!m_debugMode) { collide(world, { 0, 0, m_velocity.z }, deltaTime); }

	std::string mode = m_debugMode ? "TRUE" : "FALSE";
	m_playModetext.setString("Flying Mode:: " + mode);
}

void Player::draw(MainRenderer& mainRenderer) {
	for (int i = 0; i < m_items.size(); i++) {
		sf::Text& t = m_itemText[i];
		if (i == m_heldItem) {
			t.setFillColor(sf::Color::Red);
		}
		else {
			t.setFillColor(sf::Color::White);
		}
		t.setString(m_items[i].getMaterial().name + "::" + std::to_string(m_items[i].getNumInStack()));
		mainRenderer.drawSFMLObj(t);
	}

	mainRenderer.drawSFMLObj(m_playModetext);
}

void Player::keyboardInput() {
	glm::vec3 change = glm::vec3(0);
	static bool fillModeLine = false;
	float speed = 0.5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		speed *= 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		change.x += -glm::cos(glm::radians(m_rotation.y + 90)) * speed;
		change.z += -glm::sin(glm::radians(m_rotation.y + 90)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		change.x += glm::cos(glm::radians(m_rotation.y + 90)) * speed;
		change.z += glm::sin(glm::radians(m_rotation.y + 90)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		change.x += -glm::cos(glm::radians(m_rotation.y)) * speed;
		change.z += -glm::sin(glm::radians(m_rotation.y)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		change.x += glm::cos(glm::radians(m_rotation.y)) * speed;
		change.z += glm::sin(glm::radians(m_rotation.y)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_isOnGround) {
		change.y += speed * 50;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_debugMode) {
		change.y += speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		change.y -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		glPolygonMode(GL_FRONT_AND_BACK, fillModeLine ? GL_FILL : GL_LINE);
		fillModeLine = !fillModeLine;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G) && m_debugMode) {
		m_debugMode = false;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !m_debugMode) {
		m_debugMode = true;
		m_isOnGround = false;
		change.y += speed * 50;
	}

	
	m_velocity += change;
}
void Player::mouseInput(const sf::RenderWindow& window) {
	const int xViewBound     = 80;
	static auto lastMousePos = sf::Mouse::getPosition(window);
	auto change              = sf::Mouse::getPosition() - lastMousePos;

	m_rotation.y += change.x * 0.05;
	m_rotation.x += change.y * 0.05;

	if (m_rotation.x > xViewBound) {
		m_rotation.x = xViewBound;
	}
	else if (m_rotation.x < -xViewBound) {
		m_rotation.x = -xViewBound;
	}

	if (m_rotation.y > 360) {
		m_rotation.y = 0;
	}
	else if (m_rotation.y < 0) {
		m_rotation.y = 360;
	}

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);
	sf::Mouse::setPosition({ cx, cy }, window);
	lastMousePos = sf::Mouse::getPosition();

}

void Player::collide(World& world, const glm::vec3& vel, float dt) {

	for (int x = m_position.x - m_aabb.m_dimension.x; x < m_position.x + m_aabb.m_dimension.x; x++) {
		for (int y = m_position.y - m_aabb.m_dimension.y; y < m_position.y + 0.7; y++) {
			for (int z = m_position.z - m_aabb.m_dimension.z; z < m_position.z + m_aabb.m_dimension.z; z++) {
				auto block = world.getBlock(x, y, z);
				if (block != BlockId::AIR && block != BlockId::WATER) {
					// @case for x
					if (vel.x > 0) {
						m_position.x = x - m_aabb.m_dimension.x;
					}
					else if(vel.x < 0) {
						m_position.x = x + m_aabb.m_dimension.x + 1;
					}
					// @case for z
					if (vel.z > 0) {
						m_position.z = z - m_aabb.m_dimension.z;
					}
					else if (vel.z < 0) {
						m_position.z = z + m_aabb.m_dimension.z + 1;
					}
					//@case for y
					if (vel.y > 0) {
						m_position.y = y - m_aabb.m_dimension.y;
						m_velocity.y = 0; // ???
					}
					else if (vel.y < 0) {
						m_position.y = y + m_aabb.m_dimension.y + 1;
						m_velocity.y = 0;
						m_isOnGround = true;
					}
				}
			}
		}
	}
}

void Player::addItem(const Material& material) {
	Material::ID id = material.materialId;
	for (int i = 0; i < m_items.size(); i++) {
		if (m_items[i].getMaterial().materialId == id) {
			const int leftOver = m_items[i].add(1);
			return;
		}
		else if(m_items[i].getMaterial().materialId == Material::ID::Nothing) {
			m_items[i] = { material, 1 };
			return;
		}
	}
}

ItemStack& Player::getHeldItems() {
	return m_items[m_heldItem];
}