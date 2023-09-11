#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../vertex/vertex.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "../camera/camera.hpp"
#include "object.hpp"

class TexPlanes : public Object
{
public:
	TexPlanes(Vertex *vertex_, size_t vertex_size_, Shader *shader_, Texture *texture_);

	void draw(const Camera *camera_) override;

private:
private:
	glm::vec3 m_position = {0, 0, 0};

	float m_angle = 0;
	glm::vec3 m_axis = {0, 1, 0};

	glm::vec3 m_scale = {1, 1, 1};

	/* ----  ---- **/

	unsigned int m_VAO;

	Vertex *m_vertex;
	const size_t m_vertex_size_;
	Shader *m_shader;
	Texture *m_texture;
};
