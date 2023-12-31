#include "karaoke.hpp"

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::nanoseconds;

Karaoke::Karaoke(const char *path_)
{
	readJson(path_);
}

void Karaoke::readJson(const char *path_)
{
	try
	{
		std::fstream file(path_);
		if (!file)
		{
			throw std::runtime_error("failed to read json file: " + std::string(path_));
		}
		m_json_object = nlohmann::json::parse(file);


		m_offset = m_json_object["offset"].get<int>();
		m_bpm = m_json_object["bpm"].get<int>();
		m_beat_length = 60.0 / (double) m_bpm;

		for (size_t i = 0; i < m_json_object["notes"].size(); i++)
		{
			m_notes.emplace_back();

			for (size_t j = 0; j < m_json_object["notes"][i].size(); j++)
			{
				Notes note{
						m_json_object["notes"][i][j]["note"],
						m_json_object["notes"][i][j]["pitch"]
				};

				m_notes[i].push_back(note);
			}
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	catch (...)
	{
		std::cerr << "unknown err in karaoke manager";
	}
}

void Karaoke::instantiate()
{
	double gen_pos = 0;
	for (const auto &mjr: m_notes)
	{
		m_note_objects.emplace_back();
		for (const auto &note: mjr)
		{
			std::cout << note.pitch << std::endl;
			if (note.pitch != -1)
			{
				m_note_objects.back().emplace_back(new KaraokeLine(m_length_mlt / (float) note.note));
				m_note_objects.back().back()->setColor({.6, .6, .6});
				m_note_objects.back().back()->m_position = {gen_pos - 0, (float) note.pitch * m_pitch_mlt, 1};
			}
			gen_pos += m_length_mlt / (double) note.note;
		}
	}
}

void Karaoke::start()
{
	m_start_time = system_clock::now();
	update_();
}

void Karaoke::stop()
{

}

void Karaoke::mainLoop()
{
	while (true)
	{
		waitNextFrame_();
		update_();

		auto nano_sec = static_cast<double>(duration_cast<nanoseconds>(system_clock::now() - m_delta_time_old).count());
		auto move_value = static_cast<float>(nano_sec * 0.000000001 / (4 * m_beat_length) * m_length_mlt);
		//main loop
		for (const auto &obs: m_note_objects)
		{
			for (const auto &e: obs)
			{
				e->m_position.x -= move_value;
			}
		}

	}

}

void Karaoke::flagUp()
{
	m_flag = true;
}

Karaoke::~Karaoke()
= default;

void Karaoke::update_()
{
	m_delta_time_old = m_delta_time;
	m_delta_time = system_clock::now();

	auto now = system_clock::now();
	m_mjr = static_cast<int>(floor(
			((static_cast<double>(duration_cast<milliseconds>(now - m_start_time).count()) / 1000.0) -
			 (m_offset / 1000.0)) / (60.0 / m_bpm) / 4));
}

void Karaoke::waitNextFrame_()
{
	while (!m_flag)
	{ usleep(10); }
	m_flag = false;
}
