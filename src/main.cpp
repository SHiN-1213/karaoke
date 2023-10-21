#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window/window.hpp"
#include "input/input.hpp"
#include "shader/shader.hpp"
#include "texture/texture.hpp"
#include "vertex/vertex.hpp"
#include "scene/scene.hpp"
#include "object/karaoke/karaoke_line.hpp"
#include "object/basic/plane.hpp"
#include "karaoke/karaoke.hpp"

void initGlew();

void keyCallback(GLFWwindow *window_, int key_, int scancode_, int action_, int mods_);

int main()
{
	Window *window = Window::getInstance();
	window->createWindow(1600, 800, "Hello window");

	initGlew();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	auto *input = new Input(window->getWindow());
	input->enableRawInput();
	input->setKeyCallback(keyCallback);

	auto plane = new Plane(8, 2);
	plane->m_position = {0, 0, -1};
	plane->setColor(0, 0, 0, .2);

	auto *camera = new Camera(glm::vec3(0, 0, 5), 45, 1600.0f / 800.0f, 0.1f, 100.0f);

	auto *scene = new Scene(camera);

	scene->addObject(plane);

	auto* karaoke = new Karaoke("C:/Users/Kamih/source/repos/opengl_learn/jsons/test.json");
	karaoke->instantiate();

	for (const auto &mjr: karaoke->getObjects())
	{
		for (const auto &e: mjr)
		{
			scene->addObject(e);
		}

	}

	karaoke->start();
	std::thread thread([&](){karaoke->mainLoop();});

	while (window->isWindowOpen())
	{
		window->clearBuffer();
		scene->draw();
		karaoke->flagUp();
		window->swapBuffer();
		input->pollEvents();
		usleep(100);
	}

	window->destroyWindow();

	return 0;
}

void initGlew()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Can't initialize GLEW" << std::endl;
		exit(-1);
	}
}

void keyCallback(GLFWwindow *window_, int key_, int scancode_, int action_, int mods_)
{
	if (key_ == GLFW_KEY_E && action_ == GLFW_PRESS)
	{
		std::cout << "exiting ..." << std::endl;
		exit(0);
	}
}