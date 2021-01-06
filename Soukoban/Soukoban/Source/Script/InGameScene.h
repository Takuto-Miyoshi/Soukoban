
#ifndef IN_GAME_SCENE_H
#define IN_GAME_SCENE_H

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

	// ファイルの読み込み
	void LoadMem();

private:
	int stageData[STAGE_HEIGHT][STAGE_WIDTH];
	int playerX;
	int playerY;
	int frameCounter;

	struct GraphHandle{
		static int clear;
	};
};

#endif IN_GAME_SCENE_H
