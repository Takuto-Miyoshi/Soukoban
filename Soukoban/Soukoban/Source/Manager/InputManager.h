
#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "../KeyDefinition.h"
#include "../Singleton.h"

class InputManager : public Singleton<InputManager>{
private:
	struct KeyState{
		bool old;	// 前回チェック時のフラグ状態

		bool push;	// 押された瞬間
		bool on;	// 押下されている
		bool pull;	// 離された瞬間

		KeyState() :old( false ), push( false ), on( false ), pull( false ){}
	};

public:
	InputManager();
	~InputManager();

	// キー入力状態
	void Update();

	// 押された瞬間
	bool IsPush( KeyType key ) const;

	// 押下されている
	bool IsOn( KeyType key ) const;

	// 離された瞬間
	bool IsPull( KeyType key ) const;

private:
	KeyState state[KeyType::Key_Max];
};

#endif // !INPUT_MANAGER_H
