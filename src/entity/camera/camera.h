#pragma once

#include "../entity.h"

class Camera: public Entity
{
private:
	const Entity* m_pEntity;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

public:
	Camera();
	void hookEntity(const Entity& entity);
	void update();
	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
};

