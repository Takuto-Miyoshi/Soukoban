
#ifndef KEY_DEFINITION
#define KEY_DEFINITION

#include "DxLib.h"

enum KeyType
{
	Key_Up,		// 上移動
	Key_Down,	// 下移動
	Key_Left,	// 左移動
	Key_Right,	// 右移動
	Key_Enter,	// 決定
	Key_Reset,	// リセット
	Key_Dog,	// わん
	Key_Cat,	// にゃー

	Key_Max		// キーの種類の数
};

const int KEY_ASSIGN[KeyType::Key_Max] = {
	KEY_INPUT_UP,		// KeyType	Up
	KEY_INPUT_DOWN,		//			Down
	KEY_INPUT_LEFT,		//			Left
	KEY_INPUT_RIGHT,	//			Right
	KEY_INPUT_RETURN,	//			Enter
	KEY_INPUT_R,		//			Reset
	KEY_INPUT_D,		//			Dog
	KEY_INPUT_C			//			Cat
};

#endif // !KEY_DEFINITION
