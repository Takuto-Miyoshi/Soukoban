
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"

enum{
	Step_LogoIn,
	Step_Input,
	Step_End
};

TitleScene::TitleScene(){
	step = Step_LogoIn;
}

TitleScene::~TitleScene(){

}

void TitleScene::Exec(){
	switch( step )
	{
	case Step_LogoIn: LogoIn(); break;
	case Step_Input: Input(); break;
	default:break;
	}
}

void TitleScene::Draw(){
	DrawString( 20, 20, "TitleScene", GetColor( 0, 0, 0 ) );
}

bool TitleScene::IsEnd() const{
	return ( step == Step_End );
}

void TitleScene::LogoIn(){
	step = Step_Input;
}

void TitleScene::Input(){
	if( InputManager::GetInstance()->IsPush( KeyType::Key_Enter ) ){
		step = Step_End;
		SceneManager::GetInstance()->SetNextScene( SceneID::ID_InGame );
	}
}

