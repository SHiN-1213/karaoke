#include "object.hpp"

bool Object::isActive()
{
	return m_is_active;
}

void Object::setActive(bool flag_)
{
	m_is_active = flag_;
}