
#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GameManager.h"
#include "../ImagesDefinition.h"

enum{
	Step_Input,
	Step_End
};

int ResultScene::GraphHandle::backGround = 0;
int ResultScene::GraphHandle::guide = 0;

ResultScene::ResultScene(){
	step = Step_Input;

	LoadMem();
	SetFontSize( 48 );
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
	// 背景描画
	DrawGraph( 0, 0, GraphHandle::backGround, false );

	// 結果表示
	DrawFormatString( 100, WINDOW_HEIGHT / 2, GetColor( 0, 0, 0 ), "経過時間 : %02d分 %02d秒", GameManager::GetInstance()->GetMin(), GameManager::GetInstance()->GetSec() );
	DrawFormatString( 100, WINDOW_HEIGHT / 2 + 50, GetColor( 0, 0, 0 ), "移動回数 : %d回", GameManager::GetInstance()->GetTurn() );

	// Enterキーを押すように誘導(0.5秒間隔で点滅)
	static int flashingCounter = 0;
	flashingCounter++;

	if( flashingCounter < FRAME_RATE / 2 )		DrawGraph( Images::UI::resultGuide.drawCenterX, 350, GraphHandle::guide, true );
	else if( flashingCounter >= FRAME_RATE )	flashingCounter = 0;
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

void ResultScene::LoadMem(){
	GraphHandle::backGround = LoadGraph( Images::BackGround::result.path );
	GraphHandle::guide = LoadGraph( Images::UI::resultGuide.path );
}
