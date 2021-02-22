#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../entity/entity.h"

glm::mat4 makeModelMatrix(const Entity& entity);