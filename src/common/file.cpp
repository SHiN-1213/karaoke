#include "file.hpp"

bool File::loadFile(const char *path_, std::ios::openmode mode_, char **buff_)
{
	std::ifstream fs(path_, mode_);
	if (!fs)
	{
		std::cerr << "failed to open file" << path_ << std::endl;
		return false;
	}

	fs.seekg(0L, std::ios::end);
	std::streamsize length = fs.tellg();
	*buff_ = new char[length + 1];
	fs.seekg(0L, std::ios::beg);
	fs.read(*buff_, length);
	(*buff_)[length] = '\0';
	if (fs.fail())
	{
		// うまく読み込めなかった
		std::cerr << "Error: Could not read source file: " << path_ << std::endl;
		fs.close();
	}
	// 読み込み成功
	fs.close();

	return true;
}
