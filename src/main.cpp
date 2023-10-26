#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../libs/AudioFile.h"

#include "window/window.hpp"
#include "input/input.hpp"
#include "shader/shader.hpp"
#include "texture/texture.hpp"
#include "vertex/vertex.hpp"
#include "scene/scene.hpp"
#include "object/karaoke/karaoke_line.hpp"
#include "object/basic/plane.hpp"
#include "karaoke/karaoke.hpp"
#include "common/audio_manager.hpp"
#include "common/fft_manager.hpp"

void initGlew();

void initGl();

void keyCallback(GLFWwindow *window_, int key_, int scancode_, int action_, int mods_);

int audioCallback(void *outputBuffer, void *inputBuffer, uint32_t nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData);

auto *fft_manager = new FftManager(128, 44100, 4096 * 2);
AudioFile<float> audio_file;

int main()
{
	Window *window = Window::getInstance();
	window->createWindow(1800, 1000, "Hello window", false);

	initGlew();
	initGl();

	auto *input = new Input(window->getWindow());
	input->enableRawInput();
	input->setKeyCallback(keyCallback);

	auto plane = new Plane(8, 2);
	plane->m_position = {0, 0, -1};
	plane->setColor(0, 0, 0, .2);

	auto *camera = new Camera(glm::vec3(0, 0, 5), 45, 1600.0f / 800.0f, 0.1f, 100.0f);

	auto *scene = new Scene(camera);

	scene->addObject(plane);

	auto *karaoke = new Karaoke("C:/Users/Kamih/source/repos/opengl_learn/jsons/test.json");
	karaoke->instantiate();

	for (const auto &mjr: karaoke->getObjects())
	{
		for (const auto &e: mjr)
		{
			scene->addObject(e);
		}

	}

	karaoke->start();
	std::thread thread([&]()
	                   { karaoke->mainLoop(); });

	auto *audio_manager = new AudioManager(44100, 128);

	for (const auto &e: audio_manager->getDeviceList())
	{
		std::cout << e << std::endl;
	}

	uint32_t i_id, o_id;
	std::cout << "output?\n";
	std::cin >> o_id;
	std::cout << "input?\n";
	std::cin >> i_id;

	StreamParameters out_stream;
	out_stream.deviceId = o_id;
	out_stream.nChannels = 2;
	StreamParameters in_stream;
	in_stream.deviceId = i_id;
	in_stream.nChannels = 1;

	size_t buff_num = 0;
	audio_manager->openStream(&out_stream, &in_stream, audioCallback, &buff_num);
	audio_manager->startStream();


	audio_file.load("C:/Users/Kamih/source/repos/opengl_learn/audio_files/Peak_test_A.wav");


	while (window->isWindowOpen())
	{
		window->clearBuffer();
		scene->draw();
		karaoke->flagUp();
		window->swapBuffer();
		input->pollEvents();
		usleep(200);
	}

	audio_manager->stopStream();
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

void initGl()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	float borderColor[] = {1.0f, 1.0f, 0.0f, 1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void keyCallback(GLFWwindow *window_, int key_, int scancode_, int action_, int mods_)
{
	if (key_ == GLFW_KEY_E && action_ == GLFW_PRESS)
	{
		std::cout << "exiting ..." << std::endl;
		exit(0);
	}
}

int audioCallback(void *outputBuffer, void *inputBuffer, uint32_t nBufferFrames, double streamTime,
                  RtAudioStreamStatus status, void *userData)
{
	fft_manager->pushBackBuffer((float *) inputBuffer);
	fft_manager->getFrequency();

	auto *data = (size_t *) userData;
	auto *buffer = (float *) outputBuffer;


	for (size_t i = 0; i < nBufferFrames; i++)
	{
		for (size_t j = 0; j < 2; j++)
		{
			*buffer++ = audio_file.samples[j][i + (*data)];
		}
	}

	*(size_t *) userData += nBufferFrames;

	return 0;
}
