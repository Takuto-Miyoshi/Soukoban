
#include "TitleScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../ImagesDefinition.h"
#include "../Manager/TextureManager.h"
#include "../Manager/SoundManager.h"

enum{
	Step_LogoIn,
	Step_Input,
	Step_End
};

TitleScene::TitleScene(){
	step = Step_LogoIn;

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
	static TextureManager* instance = TextureManager::GetInstance();

	// 背景描画
	DrawGraph( 0, 0, instance->GetBackGroundHandle(), false );

	// Enterキーを押すように誘導(0.5秒間隔で点滅)
	static int flashingCounter = 0;
	flashingCounter++;

	if( flashingCounter < FRAME_RATE / 2 )		DrawGraph( Images::UI::titleGuide.drawCenterX, 350, instance->GetGuideHandle(), true );
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
		PlaySoundMem( SoundManager::GetInstance()->GetSoundHandle( SoundList::Enter ), DX_PLAYTYPE_NORMAL );
		step = Step_End;
		SceneManager::GetInstance()->SetNextScene( SceneID::ID_InGame );
	}
}
