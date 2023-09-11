#include "scene.hpp"

Scene::Scene(Camera *camera_):
		m_camera(camera_)
{

}

void Scene::setCamera(Camera *camera_)
{
	m_camera = camera_;
}

void Scene::addObject(Object *object_)
{
	m_objects.push_back(object_);
}

void Scene::draw()
{
	for (auto obj: m_objects)
	{
		obj->draw(m_camera);
	}
}


