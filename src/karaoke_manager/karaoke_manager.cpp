#include "karaoke_manager.hpp"

using std::chrono::duration_cast;
using std::chrono::system_clock;
using std::chrono::milliseconds;

KaraokeManager::KaraokeManager(const char *path_)
{
	try
	{
		std::fstream file(path_);
		if (!file)
		{
			throw std::runtime_error("failed to read json file: " + std::string(path_));
		}
		m_json_object = nlohmann::json::parse(file);


		//get values from json object
		m_offset = m_json_object["offset"].get<int>();
		m_bpm = m_json_object["bpm"].get<int>();//TODO div by 60

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



		float gen_pos = 0;
		for(const auto & mjr: m_notes)
		{
			m_note_objects.emplace_back();
			for(const auto & note: mjr)
			{
				std::cout << note.pitch << std::endl;
				if(note.pitch != -1)
				{
					m_note_objects.back().emplace_back(new KaraokeLine(1/(float)note.note * m_length_mlt));
					m_note_objects.back().back()->setColor({.6,.6,.6});
					m_note_objects.back().back()->m_position = {gen_pos-2,(float)note.pitch * m_pitch_mlt,1};
				}
				gen_pos += 1/(float)note.note * m_length_mlt;

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

void KaraokeManager::start()
{
	//keisoku kaisi
	m_start_time = system_clock::now();
	m_delta_time = system_clock::now();
}

void KaraokeManager::loop()
{
	auto now = system_clock::now();
	size_t elapsed = duration_cast<milliseconds>(now-m_delta_time).count();
	std::cout << elapsed << std::endl;

	int i = 0;
	for(const auto &mjr:m_note_objects)
	{
		if (i++ >= 1) break;
		for(const auto &e: mjr)
		{
			e->m_position.x -= elapsed /10000.0;
		}
	}

	std::cout << "mjr : " << getMjr_() << std::endl;

	m_delta_time = system_clock::now();
}

void KaraokeManager::stop()
{

}

int KaraokeManager::getMjr_()
{	auto now = system_clock::now();
	return floor(((duration_cast<milliseconds>(now-m_start_time).count()/1000.0) - (m_offset/1000.0)) / (60.0/m_bpm));
}
