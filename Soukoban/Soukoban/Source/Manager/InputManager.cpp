
#include "InputManager.h"

InputManager::InputManager(){

}

InputManager::~InputManager(){

}

void InputManager::Update(){
	for( int i = 0; i < KeyType::Key_Max; i++ ){
		// 前回のキーの入力状態を取得
		const bool now = ( CheckHitKey( KEY_ASSIGN[i] ) == 1 );

		// 前回の入力状態と比較をして現在の状態を更新
		state[i].on = now;
		state[i].push = (now == true)  && (state[i].old == false);
		state[i].pull = (now == false) && (state[i].old == true);

		// 現在の値を代入
		state[i].old = now;
	}
}

bool InputManager::IsPush( KeyType key ) const{
	if( key == KeyType::Key_Max )return false;

	return state[key].push;
}

bool InputManager::IsOn( KeyType key ) const{
	if( key == KeyType::Key_Max )return false;

	return state[key].on;
}

bool InputManager::IsPull( KeyType key ) const{
	if( key == KeyType::Key_Max )return false;

	return state[key].pull;
}
