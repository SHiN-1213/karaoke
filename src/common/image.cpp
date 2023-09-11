#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../libs/stb_image.h"

void Image::setFlipVertically(int frag_)
{
	stbi_set_flip_vertically_on_load(frag_);
}

bool Image::loadImage(const char *path_, unsigned char **buff_, int *width_, int *height_, int *channels_)
{
	*buff_ = stbi_load(path_,width_,height_,channels_,0);
	if(*buff_== nullptr)
	{
		std::cerr << "failed to load texture: " << path_ << std::endl;
		return false;
	}
	return true;
}

void Image::freeImage(unsigned char *buff_)
{
	stbi_image_free(buff_);
}