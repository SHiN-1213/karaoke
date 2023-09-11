#pragma once

#include <GL/glew.h>
#include "../common/image.hpp"

class Texture
{
public:
	explicit Texture(const char * path_);
	void use() const;
private:
private:
	unsigned int m_id{};
};
