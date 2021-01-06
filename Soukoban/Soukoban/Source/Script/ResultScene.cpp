
#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GameManager.h"

enum{
	Step_Input,
	Step_End
};

ResultScene::ResultScene(){
	step = Step_Input;
}

ResultScene::~ResultScene(){

}

void ResultScene::Exec(){
	switch( step )
	{
	case Step_Input: Input(); break;
	default:	break;
	}
}

void ResultScene::Draw(){
	DrawString( 20, 20, "ResultScene", GetColor( 0, 0, 0 ) );

	DrawFormatString( WINDOW_WIDTH / 2 - 7 * GetFontSize() / 2, WINDOW_HEIGHT / 2, GetColor( 0, 0, 0 ), "%2d : %2d", GameManager::GetInstance()->GetMin(), GameManager::GetInstance()->GetSec() );
	DrawFormatString( WINDOW_WIDTH / 2 - 8 * GetFontSize() / 2, WINDOW_HEIGHT / 2 + 50, GetColor( 0, 0, 0 ), "%2dターン", GameManager::GetInstance()->GetTurn() );
}

bool ResultScene::IsEnd() const{

	return ( step == Step_End );
}

void ResultScene::Input(){
	if( InputManager::GetInstance()->IsPush( KeyType::Key_Enter ) ){
		step = Step_End;
		SceneManager::GetInstance()->SetNextScene( SceneID::ID_Title );
	}
}
