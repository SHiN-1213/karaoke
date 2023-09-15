//
// Created by Kamih on 2023/09/14.
//

#include "transform.hpp"

glm::mat4 Transform::getSrtMatrix() const
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position);
	model = glm::rotate(model, m_angle, m_axis);
	model = glm::scale(model, m_scale);

	return model;
}
