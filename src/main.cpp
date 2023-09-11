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

#include "window/window.hpp"
#include "input/input.hpp"
#include "common/file.hpp"
#include "common/image.hpp"
#include "shader/shader.hpp"
#include "texture/texture.hpp"
#include "vertex/vertex.hpp"
#include "scene/scene.hpp"
#include "object/tex_planes.hpp"
#include "object/karaoke_line.hpp"

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

	auto *input = new Input(window->getWindow());
	input->enableRawInput();
	input->setKeyCallback(keyCallback);

	auto shader = new Shader("C:/Users/Kamih/source/repos/opengl_learn/shaders/default/shader.vert",
	                         "C:/Users/Kamih/source/repos/opengl_learn/shaders/default/shader.frag");
	auto tex_ball = new Texture("C:/Users/Kamih/source/repos/opengl_learn/images/images.jpg");

	auto object = new TexPlanes(vertexxx, sizeof(vertexxx), shader,tex_ball);

	auto oke_obj = new KaraokeLine(2);


	auto *camera = new Camera(glm::vec3(0,0,5),45,800.0f/800.0f,0.1f,100.0f);

	auto *scene = new Scene(camera);


	scene->addObject(oke_obj);
	scene->addObject(object);

	while (window->isWindowOpen())
	{
		window->clearBuffer();



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