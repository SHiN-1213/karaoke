#include "karaoke_judge.hpp"

KaraokeBackground::KaraokeBackground(float width_, float height_) :
		m_vertex{{glm::vec3(-width_/2, height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},
		         {glm::vec3(width_/2, height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},
		         {glm::vec3(width_/2, -height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},

		         {glm::vec3(-width_/2, height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},
		         {glm::vec3(width_/2, -height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},
		         {glm::vec3(-width_/2, -height_ / 2, 0),  glm::vec3(1, 1, 1), glm::vec2(0, 1)},
		},
		m_shader(new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke_judge/shader.vert",
		                    "C:/Users/Kamih/source/repos/opengl_learn/shaders/karaoke_judge/shader.frag")),
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

void KaraokeBackground::setProgress(float progress_)
{
	m_progress = progress_;
}

void KaraokeBackground::draw(const Camera *camera_)
{
	m_shader->use();
	m_texture->use();
	glBindVertexArray(m_VAO);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_position);
	model = glm::rotate(model, m_angle, m_axis);
	model = glm::scale(model, m_scale);

	m_shader->setUniformMatrix("model", 1, false, glm::value_ptr(model));

	m_shader->setUniformMatrix("view", 1, false, glm::value_ptr(camera_->getViewMatrix()));
	m_shader->setUniformMatrix("projection", 1, false, glm::value_ptr(camera_->getProjectionMatrix()));

	m_shader->setUniform("ourColor", m_color.r, m_color.g, m_color.b);

	glDrawArrays(GL_TRIANGLES, 0, sizeof(m_vertex) / sizeof(Vertex));
}

