#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../../vertex/vertex.hpp"
#include "../../shader/shader.hpp"
#include "../../texture/texture.hpp"
#include "../../camera/camera.hpp"
#include "transform.hpp"

class Object : public Transform
{
public:
	virtual void draw(const Camera *camera_) = 0;
	bool isActive();
	void setActive(bool flag_);
	virtual ~Object() = default;

private:
private:
	bool m_is_active = true;
};
