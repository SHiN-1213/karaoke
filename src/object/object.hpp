#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../vertex/vertex.hpp"
#include "../shader/shader.hpp"
#include "../texture/texture.hpp"
#include "../camera/camera.hpp"

class Object
{
public:
	virtual void draw(const Camera *camera_) = 0;
	virtual ~Object() = default;

private:
private:
};
