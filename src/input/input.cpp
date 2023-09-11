#include "input.hpp"

void Input::pollEvents()
{
	glfwPollEvents();
}

void Input::setKeyCallback(GLFWkeyfun callback_)
{
	glfwSetKeyCallback(m_window, callback_);
}

void Input::setCharCallback(GLFWcharfun callback_)
{
	glfwSetCharCallback(m_window, callback_);
}

bool Input::enableRawInput()
{
	if (glfwRawMouseMotionSupported()){
		glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		return true;
	}
	std::cerr << "cant enable raw input" <<std::endl;
	return false;
}

void Input::setCursorPosCallback(GLFWcursorposfun callback_)
{
	glfwSetCursorPosCallback(m_window, callback_);
}

void Input::setCursorEnterCallback(GLFWcursorenterfun callback_)
{
	glfwSetCursorEnterCallback(m_window, callback_);
}

void Input::setMouseButtonCallback(GLFWmousebuttonfun callback_)
{
	glfwSetMouseButtonCallback(m_window, callback_);
}
