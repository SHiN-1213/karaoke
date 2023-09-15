#pragma once

#include "../../libs/json.hpp"

class KaraokeManager
{
public:

	//現在時刻から現在のノーツの取得．
	//スタート関数．ストップ関数
	//ロード関数，Jsonの読み込み
	//デストラクタ

	KaraokeManager(std::string json_path_);

	void start();
	void stop();

private:
private:
};
