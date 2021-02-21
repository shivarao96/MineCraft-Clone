#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


Camera::Camera() {
	m_projectionMatrix = glm::perspective(45.0f, (float)(1280 / 768), 0.1f, 1000.0f);
}
void Camera::hookEntity(const Entity& entity) {
	m_pEntity = &entity;
}
void Camera::update() {
	m_position = m_pEntity->m_position;
	m_rotation = m_pEntity->m_rotation;
	glm::mat4 matrix = glm::mat4(1.0f);
	matrix = glm::rotate(matrix, glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
	matrix = glm::rotate(matrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
	matrix = glm::rotate(matrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
	matrix = glm::translate(matrix, m_position);
	m_viewMatrix = matrix;
}
const glm::mat4& Camera::getViewMatrix() const {
	return m_viewMatrix;
}
const glm::mat4& Camera::getProjectionMatrix() const {
	return m_projectionMatrix;
}