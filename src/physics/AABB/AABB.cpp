#include "AABB.h"


AABB::AABB(const glm::vec3& dim) : m_dimension(dim) {}

void AABB::update(const glm::vec3& position) {
	m_position = position;
}