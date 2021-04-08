#include "player.h"
#include <GL/glew.h>
#include "../../world/worldConstant.h"
#include "../../world/world.h"

Player::Player() : Entity({ 25,125,25 }, { 0,0,0 }, {0.5, 1, 0.5}) {
}
void Player::handleInput(const sf::RenderWindow& window) {
	keyboardInput();
	mouseInput(window);
}
void Player::update(float deltaTime, World& world) {
	
	if (!m_isOnGround) { // if not on ground 
		m_velocity.y -= 45 * deltaTime;
	}
	m_isOnGround = false;
	
	m_velocity.x *= 0.95;
	m_velocity.z *= 0.95;
	
	m_position.x += m_velocity.x * deltaTime;
	collide(world, { m_velocity.x, 0, 0 }, deltaTime);
	m_position.y += m_velocity.y * deltaTime;
	collide(world, { 0, m_velocity.y, 0 }, deltaTime);
	m_position.z += m_velocity.z * deltaTime;
	collide(world, { 0, 0, m_velocity.z }, deltaTime);
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
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		change.y -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		glPolygonMode(GL_FRONT_AND_BACK, fillModeLine ? GL_FILL : GL_LINE);
		fillModeLine = !fillModeLine;
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

	auto& dimension = m_aabb.m_dimension;
	auto& position  = m_position;
	auto& velocity  = vel;

	for (int x = position.x - dimension.x; x < position.x + dimension.x; x++) {
		for (int y = position.y - dimension.y; y < position.y + 0.7; y++) {
			for (int z = position.z - dimension.z; z < position.z + dimension.z; z++) {
				auto block = world.getBlock(x, y, z);
				if (block != BlockId::AIR) {
					// @case for x
					if (velocity.x > 0) {
						position.x = x - dimension.x;
					}
					else if(velocity.x < 0) {
						position.x = x + dimension.x + 1;
					}
					// @case for z
					if (velocity.z > 0) {
						position.z = z - dimension.z;
					}
					else if (velocity.z < 0) {
						position.z = z + dimension.z + 1;
					}
					//@case for y
					if (velocity.y > 0) {
						position.y = y - dimension.y;
						m_velocity.y = 0; // ???
					}
					else if (velocity.y < 0) {
						position.y = y + dimension.y + 1;
						m_velocity.y = 0;
						m_isOnGround = true;
					}
				}
			}
		}
	}
}