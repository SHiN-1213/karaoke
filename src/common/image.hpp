#pragma once

#include <iostream>

class Image
{
public:
	static void setFlipVertically(int frag_);

	static bool loadImage(const char *path_, unsigned char **buff_, int *width_, int *height_, int *channels_);

	static void freeImage(unsigned char *buff_);
};
