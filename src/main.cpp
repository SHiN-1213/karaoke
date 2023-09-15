#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <chrono>

#include "window/window.hpp"
#include "input/input.hpp"
#include "common/file.hpp"
#include "common/image.hpp"
#include "shader/shader.hpp"
#include "texture/texture.hpp"
#include "vertex/vertex.hpp"
#include "scene/scene.hpp"
#include "object/basic/tex_planes.hpp"
#include "object/karaoke/karaoke_line.hpp"
#include "object/basic/plane.hpp"

void initGlew();
void keyCallback(GLFWwindow *window_, int key_, int scancode_, int action_, int mods_);

int main()
{
	Window *window = Window::getInstance();
	window->createWindow(800, 800, "Hello window");

	initGlew();

	Vertex vertexxx [] = {
			{glm::vec3(0.0f, 0.5f, 0.0f),glm::vec3 (1.0f, 1.0f, 1.0f),glm::vec2( 0.5f, 1.0f)},
			{glm::vec3(0.5f, -0.5f, 0.0f),glm::vec3 (1.0f, 1.0f, 1.0f),glm::vec2( 1.0f, 0.0f)},
			{glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec3 (1.0f, 1.0f, 1.0f),glm::vec2( 0.0f, 0.0f)}
	};

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

//	auto shader = new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/default/shader.vert",
//	                         "C:/Users/Kamih/source/repos/opengl_learn/shaders/default/shader.frag");
//	auto tex_ball = new Texture("C:/Users/Kamih/source/repos/opengl_learn/images/images.jpg");
//
//	auto object = new TexPlanes(vertexxx, sizeof(vertexxx), shader,tex_ball);
	auto plane = new Plane(2,2);
	plane->m_position = {0,0,-1};
	plane->setColor(0,0,0,.2);

	auto oke_obj = new KaraokeLine(2);
	oke_obj->setColor({.6,.6,.6});

	auto *camera = new Camera(glm::vec3(0,0,5),45,800.0f/800.0f,0.1f,100.0f);

	auto *scene = new Scene(camera);

	auto start_time = std::chrono::high_resolution_clock::now();

	scene->addObject(oke_obj);
//	scene->addObject(object);
	scene->addObject(plane);

	while (window->isWindowOpen())
	{
		window->clearBuffer();
		std::chrono::duration<float> elapsed = std::chrono::high_resolution_clock::now() - start_time;
		oke_obj->setLength(5 - elapsed.count());

		scene->draw();
		window->swapBuffer();
		input->pollEvents();
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