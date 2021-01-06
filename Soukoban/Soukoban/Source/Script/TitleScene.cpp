
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../ImagesDefinition.h"

enum{
	Step_LogoIn,
	Step_Input,
	Step_End
};

int TitleScene::GraphHandle::backGround = 0;
int TitleScene::GraphHandle::guide = 0;

TitleScene::TitleScene(){
	step = Step_LogoIn;

	LoadMem();
	SetFontSize( 16 );
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
	// 背景描画
	DrawGraph( 0, 0, GraphHandle::backGround, false );

	// Enterキーを押すように誘導(0.5秒間隔で点滅)
	static int flashingCounter = 0;
	flashingCounter++;

	if( flashingCounter < FRAME_RATE / 2 )		DrawGraph( Images::UI::titleGuide.drawCenterX, 350, GraphHandle::guide, true );
	else if( flashingCounter >= FRAME_RATE )	flashingCounter = 0;
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

void TitleScene::LoadMem(){
	GraphHandle::backGround = LoadGraph( Images::BackGround::title.path );
	GraphHandle::guide = LoadGraph( Images::UI::titleGuide.path );
}
