#pragma once

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	static Window *getInstance();
	[[nodiscard]] GLFWwindow *getWindow() const {return m_window;}
	void createWindow(int width_, int height_, const char *title_, bool full_screen_);
	[[nodiscard]] bool isWindowOpen() const;
	void clearBuffer() ;
	void swapBuffer() const;
	void destroyWindow();
private:
	static void resize_callback_(GLFWwindow* window_, int width_, int height_);
	Window()= default;
	~Window()= default;
private:
	static Window *m_instance;
	GLFWwindow *m_window;
};