#include "texture.hpp"

Texture::Texture(const char *path_)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);
	unsigned char *data;
	int width, height,channel;
	Image::setFlipVertically(1);
	Image::loadImage(path_,&data,&width,&height, &channel);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Image::freeImage(data);
}

void Texture::use() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}
