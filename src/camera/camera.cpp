#include "camera.hpp"

Camera::Camera(glm::vec3 position_, float fov_, float aspect_, float near_, float far_):
	m_position(position_),
	m_fov(fov_),
	m_aspect(aspect_),
	m_near(near_),
	m_far(far_)
{

}

void Camera::setLookAt(glm::vec3 look_at_)
{
	m_look_at=look_at_;
}

void Camera::setUpside(glm::vec3 upside_)
{
	m_upside=upside_;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_position, m_look_at, m_upside);
}

glm::mat4 Camera::getProjectionMatrix() const
{
	return glm::perspective(glm::radians(m_fov), m_aspect, m_near, m_far);
}