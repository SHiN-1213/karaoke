#pragma once

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../common/file.hpp"

class Shader
{
public:
	Shader(const char *vert_path_, const char *frag_path_);

	void use();

	void setUniform(const char *name_, int value_) const;

	void setUniform(const char *name_, float value_) const;

	void setUniform(const char *name_, double value_) const;

	void setUniform(const char *name_, int value1_, int value2_) const;

	void setUniform(const char *name_, float value1_, float value2_) const;

	void setUniform(const char *name_, double value1_, double value2_) const;

	void setUniform(const char *name_, int value1_, int value2_, int value3_) const;

	void setUniform(const char *name_, float value1_, float value2_, float value3_) const;

	void setUniform(const char *name_, double value1_, double value2_, double value3_) const;

	void setUniform(const char *name_, int value1_, int value2_, int value3_, int value4_) const;

	void setUniform(const char *name_, float value1_, float value2_, float value3_, float value4_) const;

	void setUniform(const char *name_, double value1_, double value2_, double value3_, double value4_) const;

	void setUniformMatrix(const char *name_, int count_, bool transpose_, const float * value_);

private:
private:
	unsigned int m_id;
};
