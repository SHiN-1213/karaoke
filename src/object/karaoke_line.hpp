#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../vertex/vertex.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "../camera/camera.hpp"
#include "object.hpp"

class KaraokeLine : public Object
{
public:
	explicit KaraokeLine(float max_length_);

	void setLength(float length_);

	void draw(const Camera *camera_) override;

private:
private:
	glm::vec3 m_position = {0, 0, 0};

	float m_angle = 0;
	glm::vec3 m_axis = {0, 1, 0};

	glm::vec3 m_scale = {1, 1, 1};

	static constexpr float m_thickness = 0.05;
	const float m_max_length;
	float m_length = 0;
	float m_progress = .0;

	/* ----  ---- **/

	unsigned int m_VAO;

	Vertex m_vertex[6];
	Shader *m_shader;
	Texture *m_texture;
};
