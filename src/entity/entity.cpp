#include "entity.h"

Entity::Entity()
	:m_aabb({0,0,0})
{}
Entity::Entity(const glm::vec3& pos, const glm::vec3& rot)
	:m_position(pos)
	,m_rotation(rot)
	,m_aabb({ 0,0,0 })
{}
Entity::Entity(const glm::vec3& pos, const glm::vec3& rot, const glm::vec3& box)
	: m_position(pos)
	, m_rotation(rot)
	, m_aabb(box)	
{}