#pragma once

#include "../interface/object.hpp"
#include "../interface/transform.hpp"

class Plane : public Object
{
public:
	Plane(float width_, float height_);

	void setColor(float r_, float g_, float b_,float a_);

	void draw(const Camera *camera_) override;

private:
private:

	glm::vec4 m_color = {1.0f, 1.0f, 1.0f, 1.0f};
	/* ----  ---- **/

	unsigned int m_VAO;
	unsigned int m_VBO;

	Vertex m_vertex[6];
	Shader *m_shader;
	Texture *m_texture;
};
