#include "scene.hpp"

Scene::Scene(Camera *camera_) :
		m_camera(camera_)
{

}

void Scene::setCamera(Camera *camera_)
{
	m_camera = camera_;
}

void Scene::addObject(Object *object_)
{
	for (size_t i = 0; i < m_objects.size(); i++)
	{
		if (m_objects[i]->m_position.z >= object_->m_position.z)
		{
			m_objects.insert(m_objects.begin()+i,object_);
			break;
		}
	}
	m_objects.insert(m_objects.end(),object_);
}

void Scene::draw()
{
	for (auto obj: m_objects)
	{
		if(!obj->isActive()) continue;
		obj->draw(m_camera);
	}
}


