#pragma once
#include <glm/glm.hpp>
#include"../physics/AABB/AABB.h"

class Entity
{
public:
	glm::vec3 m_position = { 0,0,0 };
	glm::vec3 m_rotation = { 0,0,0 };
	glm::vec3 m_velocity = { 0,0,0 };
	AABB m_aabb;

	Entity();
	Entity(const glm::vec3& pos, const glm::vec3& rot);
	Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& box);
};	

