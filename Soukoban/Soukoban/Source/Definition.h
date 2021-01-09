
#ifndef DEFINITION_H
#define DEFINITION_H

#include "DxLib.h"

// シーンID
enum SceneID{
	ID_Title,		// タイトル
	ID_InGame,		// インゲーム
	ID_Result,		// リザルト

	ID_Max,
	ID_Invalid		// 無効値
};

// ステージのサイズ
const int STAGE_WIDTH = 13;
const int STAGE_HEIGHT = 15;

// マップチップのサイズ
const int CHIP_WIDTH = 32;
const int CHIP_HEIGHT = 32;

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;
const int COLOR_BIT = 32;
const int FRAME_RATE = 60;

enum ObjectType{
	Obj_Ground,			// 地面
	Obj_Wall,			// 壁
	Obj_Player,			// プレイヤーの初期地点
	Obj_Target,			// クレート配置場所
	Obj_UnsetCrate,		// 未配置のクレート
	Obj_SetCrate = 7	// 設置済みのクレート(設置場所 + 未配置クレート = 7)
};

// 方向
enum DirType{
	Dir_Up,
	Dir_Down,
	Dir_Left,
	Dir_Right,

	Dir_Max
};

struct Position{
	int x;
	int y;
	DirType direction;

	bool operator == ( Position pos ){
		return ( x == pos.x && y == pos.y );
	}

	void operator = (Position pos){
		x = pos.x;
		y = pos.y;
	}
};

namespace Color{
	const int black = GetColor( 0, 0, 0 );
	const int brown = GetColor( 192, 72, 0 );
	const int white = GetColor( 0, 0, 0 );
}

#endif // !DEFINITION_H
