
#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

#include <vector>
#include <string>

#include "SceneBase.h"
#include "../Definition.h"

class InGameScene : public SceneBase{
public:
	InGameScene();
	virtual ~InGameScene();

	virtual void Exec();
	virtual void Draw();

	virtual bool IsEnd() const;

private:
	void StartJingle();

	void Input();

	void ClearJingle();

// 倉庫番に関係する関数群
private:
	// ゲームのクリア判定
	bool IsClear() const;

	// 初期状態にリセット
	void Reset();

	// 移動処理
	void Move( DirType dir );

	// 時間の計測
	void AddTime();

	// UIの表示
	void DrawUI();

	// 一手戻す
	void BackOneStep();

	// ステージのロード
	void LoadStage();

	inline void EntryMapChip( int y, int x, std::string lineTemp );

private:
	Position playerPos;
	int frameCounter;

	std::vector<std::vector<int>> loadedStage;
	std::vector<std::vector<int>> stageData;
	std::vector<std::vector<std::vector<int>>> stageLog;
	std::vector<Position> playerLog;
};

#endif IN_GAME_SCENE_H
