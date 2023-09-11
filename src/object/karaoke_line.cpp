#include "karaoke_line.hpp"

KaraokeLine::KaraokeLine(float max_length_):
	m_max_length(max_length_),
	m_vertex{{glm::vec3(-max_length_/2,m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(0,1)},//左上
			 {glm::vec3(max_length_/2,m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(1,1)},//右上
			 {glm::vec3(max_length_/2,-m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(1,0)},//右下

			 {glm::vec3(-max_length_/2,m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(0,1)},//左上
			 {glm::vec3(max_length_/2,-m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(1,0)},//右下
			 {glm::vec3(-max_length_/2,-m_thickness/2,0),glm::vec3(1,1,1),glm::vec2(0,0)}},//左下
	 m_shader(new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke_line/shader.vert",
			                     "C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke_line/shader.frag")),
								 m_texture(new Texture("C:/Users/Kamih/source/repos/opengl_learn/images/yellow_ball.jpg"))
{
	glGenVertexArrays(1, &m_VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
}

void KaraokeLine::draw(const Camera *camera_)
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


	m_shader->setUniform("pointA",(float)-m_max_length/2 + m_thickness/2,(float)0);
	m_shader->setUniform("pointB",(float)m_max_length/2 - m_thickness/2,(float)0);
	m_shader->setUniform("lineWidth",m_thickness);
	m_shader->setUniform("lineProgress",m_progress);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertex)/ sizeof(Vertex));
}