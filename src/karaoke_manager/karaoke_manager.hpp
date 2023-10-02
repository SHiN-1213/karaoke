#pragma once

#include <iostream>
#include <fstream>
#include "../../libs/json.hpp"
#include "../object/karaoke/karaoke_line.hpp"


class KaraokeManager
{
public:

	//現在時刻から現在のノーツの取得．
	//スタート関数．ストップ関数
	//ロード関数，Jsonの読み込み
	//デストラクタ

	KaraokeManager(const char* path_);

	void start();
	void stop();

	std::vector<KaraokeLine*> getObjects(){return m_note_objects;};
private:
private:
	nlohmann::json m_json_object;
	/* -- **/
	int m_offset;
	int m_bpm;

	struct Notes{
		int note;//ex) 1,2,4,8,16...
		int pitch;//-1 is lest
	};

	std::vector<std::vector<Notes>> m_notes;//json data
	std::vector<KaraokeLine*> m_note_objects;//game object

	static constexpr float m_pitch_mlt = 1.0f/8.0f;
	static constexpr float m_length_mlt = 1/2.0f;
};
