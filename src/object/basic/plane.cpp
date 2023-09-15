#include "plane.hpp"

Plane::Plane(float width_, float height_) :
		m_vertex{{glm::vec3(-width_ / 2, height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},//左上
		         {glm::vec3(width_ / 2, height_ / 2, 0),   glm::vec3(1, 1, 1), glm::vec2(1, 1)},//右上
		         {glm::vec3(width_ / 2, -height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(1, 0)},//右下

		         {glm::vec3(-width_ / 2, height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},//左上
		         {glm::vec3(width_ / 2, -height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(1, 0)},//右下
		         {glm::vec3(-width_ / 2, -height_ / 2, 0), glm::vec3(1, 1, 1), glm::vec2(0, 0)}},//左下
		m_shader(new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/plane/shader.vert",
		                    "C:/Users/Kamih/source/repos/opengl_learn/shaders/plane/shader.frag")),
		m_texture(new Texture("C:/Users/Kamih/source/repos/opengl_learn/images/yellow_ball.jpg"))
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
void Plane::setColor(float r_, float g_, float b_, float a_)
{
	m_color = {r_,g_,b_,a_};
}
void Plane::draw(const Camera *camera_)
{
	m_shader->use();
	m_texture->use();
	glBindVertexArray(m_VAO);

	glm::mat4 model = getSrtMatrix();
	m_shader->setUniformMatrix("model", 1, false, glm::value_ptr(model));

	m_shader->setUniformMatrix("view", 1, false, glm::value_ptr(camera_->getViewMatrix()));
	m_shader->setUniformMatrix("projection", 1, false, glm::value_ptr(camera_->getProjectionMatrix()));

	m_shader->setUniform("ourColor", m_color.r, m_color.g, m_color.b, m_color.a);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertex) / sizeof(Vertex));
}


