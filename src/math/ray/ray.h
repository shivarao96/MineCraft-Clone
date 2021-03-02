#pragma once

#include <glm/glm.hpp>

class Ray
{
public:
	Ray(const glm::vec3& position, const glm::vec3& direction);

	void setStep(float scale);
	const glm::vec3& getEnd() const;
	float getLength() const;
private:
	glm::vec3 m_start;
	glm::vec3 m_end;
	glm::vec3 m_direction;
};

