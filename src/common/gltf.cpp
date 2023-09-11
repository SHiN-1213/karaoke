#include "gltf.hpp"

#define TINYOBJLOADER_IMPLEMENTATION

#include "../../libs/tiny_obj_loader.h"

std::vector<Vertex> Gltf::loadObject(const std::string &path_)
{
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn, err;

	if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path_.c_str()))
	{
		std::cerr << "cant load object!" << std::endl;
	}

	std::vector<Vertex> vertices = {};

	for (const auto &shape: shapes)
	{
		for (const auto &index: shape.mesh.indices)
		{
			Vertex vertex{};

			vertex.pos = {//頂点座標
					attrib.vertices[3 * index.vertex_index + 0],
					attrib.vertices[3 * index.vertex_index + 1],
					attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {//UV座標
					attrib.texcoords[2 * index.texcoord_index + 0],
					1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = {1.0f, 1.0f, 1.0f};//頂点カラー

			vertices.push_back(vertex);
		}
	}
	return vertices;
}
