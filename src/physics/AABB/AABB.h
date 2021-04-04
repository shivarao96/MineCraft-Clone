#pragma once

#include <glm/glm.hpp>

class AABB
{
public:
	const glm::vec3 m_dimension;
	glm::vec3 m_position;

	AABB(const glm::vec3& dim) : m_dimension(dim) {}
	void update(const glm::vec3& position);
};

