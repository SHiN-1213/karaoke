#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <unistd.h>


#include "../../libs/json.hpp"
#include "../object/karaoke/karaoke_line.hpp"

class Karaoke
{
public:
	Karaoke() = default;

	Karaoke(const char *path_);

	void readJson(const char *path_);

	void instantiate();

	void start();

	void stop();

	std::vector<std::vector<KaraokeLine *>> getObjects()
	{ return m_note_objects; };

	void mainLoop();

	void flagUp();

	~Karaoke();

private:
	void update_();

	void waitNextFrame_();

private:
	nlohmann::json m_json_object;
	/* -- **/
	int m_offset = 0;
	int m_bpm = 0;

	static constexpr float m_pitch_mlt = 1.0f / 8.0f;
	static constexpr float m_length_mlt = 2 / 1.0f;

	struct Notes
	{
		int note;//ex) 1,2,4,8,16...
		int pitch;//-1 is lest
	};
	std::vector<std::vector<Notes>> m_notes;//json data

	std::vector<std::vector<KaraokeLine *>> m_note_objects;

	std::chrono::system_clock::time_point m_start_time;
	std::chrono::system_clock::time_point m_delta_time;
	int m_mjr = 0;
	bool m_flag = false;
};