#include "player.h"
#include <GL/glew.h>

Player::Player() {
	m_position = glm::vec3(1, 0, -15);
}
void Player::handleInput(const sf::RenderWindow& window) {
	keyboardInput();
	mouseInput(window);
}
void Player::update(float deltaTime) {
	m_position += m_velocity * deltaTime;
	m_velocity *= 0.95;
}
void Player::keyboardInput() {
	glm::vec3 change = glm::vec3(0);
	static bool fillModeLine = false;
	float speed = 0.5;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		change.x += glm::cos(glm::radians(m_rotation.y + 90)) * speed;
		change.z += glm::sin(glm::radians(m_rotation.y + 90)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		change.x += -glm::cos(glm::radians(m_rotation.y + 90)) * speed;
		change.z += -glm::sin(glm::radians(m_rotation.y + 90)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		change.x += glm::cos(glm::radians(m_rotation.y)) * speed;
		change.z += glm::sin(glm::radians(m_rotation.y)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		change.x += -glm::cos(glm::radians(m_rotation.y)) * speed;
		change.z += -glm::sin(glm::radians(m_rotation.y)) * speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		change.y -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		change.y += speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
		glPolygonMode(GL_FRONT_AND_BACK, fillModeLine ? GL_FILL : GL_LINE);
		fillModeLine = !fillModeLine;
	}
	
	m_velocity   += change;
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

	auto cx = static_cast<int>(window.getSize().x / 4);
	auto cy = static_cast<int>(window.getSize().y / 4);
	sf::Mouse::setPosition({ cx, cy }, window);
	lastMousePos = sf::Mouse::getPosition();

}