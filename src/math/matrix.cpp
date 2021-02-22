#include "Matrix.h"

glm::mat4 makeModelMatrix(const Entity& entity) {
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(
		model,
		glm::radians(entity.m_rotation.x),
		glm::vec3(1.0, 0.0, 0.0)
	);
	model = glm::rotate(
		model,
		glm::radians(entity.m_rotation.y),
		glm::vec3(0.0, 1.0, 0.0)
	);
	model = glm::rotate(
		model,
		glm::radians(entity.m_rotation.z),
		glm::vec3(0.0, 0.0, 1.0)
	);
	model = glm::translate(
		model,
		entity.m_position
	);
	return model;
}