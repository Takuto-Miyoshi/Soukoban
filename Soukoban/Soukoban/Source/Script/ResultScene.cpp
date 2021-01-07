
#include "ResultScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GameManager.h"
#include "../ImagesDefinition.h"
#include "../Manager/TextureManager.h"
#include "../Manager/SoundManager.h"

enum{
	Step_Input,
	Step_End
};

ResultScene::ResultScene(){
	step = Step_Input;

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
	static TextureManager* instance = TextureManager::GetInstance();

	// 背景描画
	DrawGraph( 0, 0, instance->GetBackGroundHandle(), false );

	// 結果表示
	DrawFormatString( 100, WINDOW_HEIGHT / 2, GetColor( 0, 0, 0 ), "経過時間 : %02d分 %02d秒", GameManager::GetInstance()->GetMin(), GameManager::GetInstance()->GetSec() );
	DrawFormatString( 100, WINDOW_HEIGHT / 2 + 50, GetColor( 0, 0, 0 ), "移動回数 : %d回", GameManager::GetInstance()->GetTurn() );

	// Enterキーを押すように誘導(0.5秒間隔で点滅)
	static int flashingCounter = 0;
	flashingCounter++;

	if( flashingCounter < FRAME_RATE / 2 )		DrawGraph( Images::UI::resultGuide.drawCenterX, 350, instance->GetGuideHandle(), true );
	else if( flashingCounter >= FRAME_RATE )	flashingCounter = 0;
}

bool ResultScene::IsEnd() const{
	return ( step == Step_End );
}

void ResultScene::Input(){
	if( InputManager::GetInstance()->IsPush( KeyType::Key_Enter ) ){
		PlaySoundMem( SoundManager::GetInstance()->GetSoundHandle( SoundList::Enter ), DX_PLAYTYPE_NORMAL );
		step = Step_End;
		SceneManager::GetInstance()->SetNextScene( SceneID::ID_Title );
	}
}
