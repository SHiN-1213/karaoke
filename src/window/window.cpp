#include "window.hpp"

Window *Window::m_instance = nullptr;

Window *Window::getInstance()
{
	if (m_instance == nullptr) {
		m_instance = new Window();
	}
	return m_instance;
}

void Window::createWindow(int width_, int height_, const char *title_)
{
	if (glfwInit() == GL_FALSE) {
		std::cerr << "Can't initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	m_window = glfwCreateWindow(width_, height_, title_, nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cerr << "failed to create window" << std::endl;
	}
	glfwMakeContextCurrent(m_window);
	glViewport(0, 0, width_, height_);
	glfwSetFramebufferSizeCallback(m_window, resize_callback_);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
}

[[nodiscard]] bool Window::isWindowOpen() const
{
	return glfwWindowShouldClose(m_window) == GL_FALSE;
}

void Window::clearBuffer()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffer() const
{
	glfwSwapBuffers(m_window);
}

void Window::destroyWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

void Window::resize_callback_(GLFWwindow* window_, int width_, int height_)
{
	glViewport(0, 0, width_, height_);
}
