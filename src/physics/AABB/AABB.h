#pragma once

#include <glm/glm.hpp>

class AABB
{
public:
	const glm::vec3 m_dimension;
	glm::vec3 m_position;

	AABB(const glm::vec3& dim) : m_dimension(dim) {}
	
	void update(const glm::vec3& position) {
		m_position = position;
	}

	glm::vec3 getVN(const glm::vec3& normal)const noexcept { // view normal
		glm::vec3 res = m_position;
		if (normal.x < 0) {
			res.x += m_dimension.x;
		}
		if (normal.y < 0) {
			res.y += m_dimension.y;
		}
		if (normal.z < 0) {
			res.z += m_dimension.z;
		}

		return res;
	}

	glm::vec3 getVP(const glm::vec3& normal)const noexcept { // view position
		glm::vec3 res = m_position;
		if (normal.x > 0) {
			res.x += m_dimension.x;
		}
		if (normal.y > 0) {
			res.y += m_dimension.y;
		}
		if (normal.z > 0) {
			res.z += m_dimension.z;
		}

		return res;
	}
};

