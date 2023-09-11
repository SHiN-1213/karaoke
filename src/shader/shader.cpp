#include "shader.hpp"

Shader::Shader(const char *vert_path_, const char *frag_path_)
{
	char *vert_buff = nullptr;
	char *frag_buff = nullptr;

	File::loadFile(vert_path_, std::ios::binary, &vert_buff);
	File::loadFile(frag_path_, std::ios::binary, &frag_buff);


	int success;
	char infoLog[512];

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert_buff, nullptr);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag_buff, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	};

	m_id = glCreateProgram();
	glAttachShader(m_id, vertexShader);
	glAttachShader(m_id, fragmentShader);
	glLinkProgram(m_id);

	glGetProgramiv(m_id, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_id, 512, nullptr, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use()
{
	glUseProgram(m_id);
}

void Shader::setUniform(const char *name_, int value_) const
{
	glUniform1i(glGetUniformLocation(m_id, name_), value_);
}

void Shader::setUniform(const char *name_, float value_) const
{
	glUniform1f(glGetUniformLocation(m_id, name_), value_);
}

void Shader::setUniform(const char *name_, double value_) const
{
	glUniform1d(glGetUniformLocation(m_id, name_), value_);
}

void Shader::setUniform(const char *name_, int value1_, int value2_) const
{
	glUniform2i(glGetUniformLocation(m_id, name_), value1_, value2_);
}

void Shader::setUniform(const char *name_, float value1_, float value2_) const
{
	glUniform2f(glGetUniformLocation(m_id, name_), value1_, value2_);

}

void Shader::setUniform(const char *name_, double value1_, double value2_) const
{
	glUniform2d(glGetUniformLocation(m_id, name_), value1_, value2_);
}

void Shader::setUniform(const char *name_, int value1_, int value2_, int value3_) const
{
	glUniform3i(glGetUniformLocation(m_id, name_), value1_, value2_, value3_);
}

void Shader::setUniform(const char *name_, float value1_, float value2_, float value3_) const
{
	glUniform3f(glGetUniformLocation(m_id, name_), value1_, value2_, value3_);
}

void Shader::setUniform(const char *name_, double value1_, double value2_, double value3_) const
{
	glUniform3d(glGetUniformLocation(m_id, name_), value1_, value2_, value3_);
}

void Shader::setUniform(const char *name_, int value1_, int value2_, int value3_, int value4_) const
{
	glUniform4i(glGetUniformLocation(m_id, name_), value1_, value2_, value3_, value4_);
}

void Shader::setUniform(const char *name_, float value1_, float value2_, float value3_, float value4_) const
{
	glUniform4f(glGetUniformLocation(m_id, name_), value1_, value2_, value3_, value4_);
}

void Shader::setUniform(const char *name_, double value1_, double value2_, double value3_, double value4_) const
{
	glUniform4d(glGetUniformLocation(m_id, name_), value1_, value2_, value3_, value4_);
}

void Shader::setUniformMatrix(const char *name_, int count_, bool transpose_, const float *value_)
{
	glUniformMatrix4fv(glGetUniformLocation(m_id, name_),count_,transpose_,value_);
}
