#pragma once

#include <vector>

#include "../object/object.hpp"
#include "../camera/camera.hpp"

class Scene
{
public:
	explicit Scene(Camera *camera_);
	void setCamera(Camera * camera_);
	void addObject(Object *object_);
	void draw();
private:
private:
	Camera *m_camera;

	std::vector<Object*> m_objects = {};

};
