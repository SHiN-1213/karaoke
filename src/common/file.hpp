#pragma once

#include <iostream>
#include <fstream>

class File
{
public:
	static bool loadFile(const char *path_, std::ios::openmode mode_, char **buff_);
};
