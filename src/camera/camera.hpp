#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//glm::ortho

class Camera
{
public:
	Camera(glm::vec3 position_, float fov_, float aspect_, float near_, float far_);
	void setLookAt(glm::vec3 look_at_);
	void setUpside(glm::vec3 upside_);

	[[nodiscard]] glm::mat4 getViewMatrix() const;
	[[nodiscard]] glm::mat4 getProjectionMatrix() const;
private:
private:
	glm::vec3 m_position;
	glm::vec3 m_look_at = {0,0,0};
	glm::vec3 m_upside = {0,1,0};

	float m_fov;

	float m_aspect;

	float m_near;
	float m_far;
};