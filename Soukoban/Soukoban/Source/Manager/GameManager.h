
#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <string>
#include <vector>

#include "../Singleton.h"

struct StageData{
	std::string fileName;
	std::vector<std::vector<int>> mapData;
	std::string stageTitle;
};


class GameManager : public Singleton<GameManager>{
public:
	GameManager();
	~GameManager();

	// Stageフォルダ内のテキストファイルを読み込み
	void GetTxtFileInFolder();

	// シーン間でやりとりしたいデータの設定、取得関数を適宜追加

	int GetTurn() const { return turn; }
	void SetTurn( int value ) { turn = value; }

	int GetSec() const { return timeSec; }
	void SetSec( int value ) { timeSec = value; }

	int GetMin() const { return timeMin; }
	void SetMin( int value ) { timeMin = value; }

	std::vector<StageData> GetFileVector() const { return fileList; }

	int GetSelectStageNum() const { return selectStageNum; }
	void SetSelectStageNum( unsigned int value ) { selectStageNum = value; }

private:
	// シーン間でやりとりするデータを保持しておく変数を適宜追加
	int turn;	// 移動回数
	int timeSec;	// プレイ時間 - 秒
	int timeMin;	// プレイ時間 - 分

	std::vector<StageData> fileList;
	int selectStageNum;
};

#endif // !GAME_MANAGER_H
