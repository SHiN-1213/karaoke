#include "karaoke_manager.hpp"

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
		m_bpm = m_json_object["bpm"].get<int>();

		for (size_t i = 0; i < m_json_object["notes"].size(); i++)
		{
			m_notes.push_back(std::vector<Notes>());

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
			for(const auto & note: mjr)
			{
				std::cout << note.pitch << std::endl;
				if(note.pitch != -1)
				{
					m_note_objects.push_back(new KaraokeLine(1/(float)note.note * m_length_mlt));
//					m_note_objects.back()->setLength(1/(float)note.note);
					m_note_objects.back()->setColor({.6,.6,.6});
					m_note_objects.back()->m_position = {gen_pos-2,(float)note.pitch * m_pitch_mlt,1};
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

}

void KaraokeManager::stop()
{

}
