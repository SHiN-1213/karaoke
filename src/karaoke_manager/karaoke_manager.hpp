#pragma once

#include <iostream>
#include <fstream>
#include <cmath>
#include "../../libs/json.hpp"
#include "../object/karaoke/karaoke_line.hpp"


class KaraokeManager
{
public:

	//現在時刻から現在のノーツの取得．
	//スタート関数．ストップ関数
	//ロード関数，Jsonの読み込み
	//デストラクタ

	explicit KaraokeManager(const char* path_);

	void start();
	void loop();
	void stop();

	std::vector<std::vector<KaraokeLine*>> getObjects(){return m_note_objects;};

private:
	int getMjr_();
	std::vector<KaraokeLine*> getLineFromMjr_(int mjr_);
	void moveLineFromMjr_(int mjr_);
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
	std::vector<std::vector<KaraokeLine*>> m_note_objects;//game object

	static constexpr float m_pitch_mlt = 1.0f/8.0f;
	static constexpr float m_length_mlt = 3/1.0f;

	//カラオケラインを0 ~ 1に設置，ParentObjectにおいて調整，マネージャー側でParentObjectの制御．

	std::chrono::system_clock::time_point m_start_time;
	std::chrono::system_clock::time_point m_delta_time;

	double m_chronos_offset = 0;
};
