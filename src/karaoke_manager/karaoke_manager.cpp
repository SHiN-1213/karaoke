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
		bool gen_frag = false;
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
					m_note_objects.back().back()->m_position = {gen_pos-3,(float)note.pitch * m_pitch_mlt,1};
				}
				gen_pos += 1/(float)note.note * m_length_mlt;

			}
			if(!gen_frag){
				gen_frag = true;
			}
			else{
				gen_frag = false;
				gen_pos = 0;
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
	m_start_time = system_clock::now();
	m_delta_time = system_clock::now();
}

void KaraokeManager::loop()
{
	auto now = system_clock::now();
	size_t elapsed = duration_cast<milliseconds>(now-m_delta_time).count();

	for(const auto &obs:m_note_objects)
	{
		for(const auto &e:obs)
		{
			e->setActive(false);
		}
	}//set all to false

	auto mjr = getMjr_();
	if(mjr < 0) return;

	if(mjr % 2 == 0)
	{
		moveLineFromMjr_(mjr);
		moveLineFromMjr_(mjr+1);
	}
	else
	{
		moveLineFromMjr_(mjr-1);
		moveLineFromMjr_(mjr);
	}

	std::cout << "mjr : " << getMjr_() << std::endl;

	m_delta_time = system_clock::now();
}

void KaraokeManager::stop()
{

}

int KaraokeManager::getMjr_()
{	auto now = system_clock::now();
	return floor(((duration_cast<milliseconds>(now-m_start_time).count()/1000.0) - (m_offset/1000.0)) / (60.0/m_bpm) / 4);
}

std::vector<KaraokeLine *> KaraokeManager::getLineFromMjr_(int mjr_)
{
	return m_note_objects[mjr_];
}

void KaraokeManager::moveLineFromMjr_(int mjr_)
{
	auto obj = getLineFromMjr_(mjr_);
	for(const auto &e: obj)
	{
//		e->m_position.x += 10 /10000.0;
		e->setActive(true);
	}//move obj from mjr
}