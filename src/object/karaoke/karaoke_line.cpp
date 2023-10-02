#include "karaoke_line.hpp"

KaraokeLine::KaraokeLine(float length_) :
		m_length(length_),
		m_vertex{{glm::vec3(0, m_thickness / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},//左上
		         {glm::vec3(length_, m_thickness / 2, 0),   glm::vec3(1, 1, 1), glm::vec2(1, 1)},//右上
		         {glm::vec3(length_, -m_thickness / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(1, 0)},//右下

		         {glm::vec3(0, m_thickness / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},//左上
		         {glm::vec3(length_, -m_thickness / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(1, 0)},//右下
		         {glm::vec3(0, -m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(0, 0)}},//左下
		m_shader(new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke/karaoke_line/shader.vert",
		                    "C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke/karaoke_line/shader.frag"))
{
	glGenVertexArrays(1, &m_VAO);

	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex), m_vertex, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
	glEnableVertexAttribArray(0);//location 0

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void KaraokeLine::setLength(float length_)
{
	m_length = length_;
	m_vertex[0] = {glm::vec3(0, m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(0, 1)};//左上
	m_vertex[1] = {glm::vec3(length_, m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(1, 1)};//右上
	m_vertex[2] = {glm::vec3(length_, -m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(1, 0)};//右下

	m_vertex[3] = {glm::vec3(0, m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(0, 1)};//左上
	m_vertex[4] = {glm::vec3(length_, -m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(1, 0)};//右下
	m_vertex[5] = {glm::vec3(0, -m_thickness / 2, 0), glm::vec3(1, 1, 1), glm::vec2(0, 0)};//左下

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertex), m_vertex, GL_STATIC_DRAW);
}

void KaraokeLine::setColor(glm::vec3 color_)
{
	m_color = color_;
}

void KaraokeLine::draw(const Camera *camera_)
{
	m_shader->use();
	glBindVertexArray(m_VAO);

	glm::mat4 model = getSrtMatrix();


	m_shader->setUniformMatrix("model", 1, false, glm::value_ptr(model));

	m_shader->setUniformMatrix("view", 1, false, glm::value_ptr(camera_->getViewMatrix()));
	m_shader->setUniformMatrix("projection", 1, false, glm::value_ptr(camera_->getProjectionMatrix()));


	m_shader->setUniform("pointA", (float)  m_thickness / 2, (float) 0);
	m_shader->setUniform("pointB", (float) m_length - m_thickness / 2, (float) 0);
	m_shader->setUniform("lineWidth", m_thickness);
	m_shader->setUniform("lineProgress", m_progress);
	m_shader->setUniform("ourColor", m_color.r, m_color.g, m_color.b);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertex) / sizeof(Vertex));
}