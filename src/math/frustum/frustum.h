#pragma once
#include <array>
#include <glm/glm.hpp>
#include "../../physics/AABB/AABB.h"

struct Plane {
	float distanceToPoint(const glm::vec3& point) const;
	float distanceToOrigin;
	glm::vec3 normal;
};

enum Planes {
	LEFT,
	RIGHT,
	BOTTOM,
	TOP,
	NEAR,
	FAR
};

class Frustum
{
public:
	void update(const glm::mat4& projViewMatrix);
	bool isBoxInFrustum(const AABB& box) const noexcept;
private:
	std::array<Plane, 6> m_planes;
};

