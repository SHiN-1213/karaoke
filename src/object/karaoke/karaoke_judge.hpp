#pragma once

#include "../interface/object.hpp"

class KaraokeBackground : public Object
{
public:
	KaraokeBackground(float width_,float height_);

	void setProgress(float progress_);

	void draw(const Camera *camera_) override;

private:
private:
	glm::vec3 m_position = {0, 0, 0};

	float m_angle = 0;
	glm::vec3 m_axis = {0, 1, 0};

	glm::vec3 m_scale = {1, 1, 1};

	glm::vec3 m_color = {1.0f, 1.0f, 1.0f};

	/* ----  ---- **/

	unsigned int m_VAO;
	unsigned int m_VBO;

	Vertex m_vertex[6];
	Shader *m_shader;
	Texture *m_texture;
};
