#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transform
{
public:
	glm::vec3 m_position = {0, 0, 0};

	float m_angle = 0;
	glm::vec3 m_axis = {0, 1, 0};

	glm::vec3 m_scale = {1, 1, 1};
protected:
	[[nodiscard]] glm::mat4 getSrtMatrix() const;
};
