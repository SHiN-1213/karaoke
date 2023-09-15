#include "tex_planes.hpp"

TexPlanes::TexPlanes(Vertex *vertex_, size_t vertex_size_, Shader *shader_, Texture *texture_):
		m_vertex(vertex_),
		m_vertex_size_(vertex_size_),
		m_shader(shader_),
		m_texture(texture_)
{
	glGenVertexArrays(1, &m_VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertex_size_, m_vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);//location 0

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void TexPlanes::draw(const Camera *camera_)
{
	m_shader->use();
	m_texture->use();
	glBindVertexArray(m_VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model,m_position);
	model = glm::rotate(model, m_angle, m_axis);
	model = glm::scale(model,m_scale);

	m_shader->setUniformMatrix("model", 1, false, glm::value_ptr(model));

	m_shader->setUniformMatrix("view", 1, false, glm::value_ptr(camera_->getViewMatrix()));
	m_shader->setUniformMatrix("projection", 1, false, glm::value_ptr(camera_->getProjectionMatrix()));

	glDrawArrays(GL_TRIANGLES, 0, m_vertex_size_/ sizeof(Vertex));
}
