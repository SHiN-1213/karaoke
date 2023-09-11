#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../vertex/vertex.hpp"

class Gltf
{
public:
	static std::vector<Vertex> loadObject(const std::string& path_);
};
