#include "ray.h"


Ray::Ray(const glm::vec3& position, const glm::vec3& direction)
	:m_start(position), m_end(position), m_direction(direction)
{}

void Ray::setStep(float scale) {
	float yaw   = glm::radians(m_direction.y + 90);
	float pitch = glm::radians(m_direction.x);

	auto& p = m_end;
	p.x -= glm::cos(yaw) * scale;
	p.z -= glm::sin(yaw) * scale;
	p.y -= glm::tan(pitch) * scale;
}
const glm::vec3& Ray::getEnd() const {
	return m_end;
}
float Ray::getLength() const {
	return glm::distance(m_start, m_end);
}