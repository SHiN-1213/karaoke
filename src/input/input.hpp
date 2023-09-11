#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Input
{
public:
	Input(GLFWwindow* window_):m_window(window_){};

	void pollEvents();

	void setKeyCallback(GLFWkeyfun callback_);
	void setCharCallback(GLFWcharfun callback_);

	bool enableRawInput();
	void setCursorPosCallback(GLFWcursorposfun callback_);
	void setCursorEnterCallback(GLFWcursorenterfun callback_);

	void setMouseButtonCallback(GLFWmousebuttonfun callback_);
private:
private:
	GLFWwindow* m_window;
};
