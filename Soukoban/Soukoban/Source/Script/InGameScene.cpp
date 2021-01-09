
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GameManager.h"
#include "../ImagesDefinition.h"
#include "../Manager/TextureManager.h"
#include "../Manager/SoundManager.h"

enum{
	Step_StartJingle,
	Step_Input,
	Step_ClearJingle,
	Step_End
};

const std::vector<std::vector<int>> sampleStage = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,0,0,0,0},
	{0,0,0,0,1,3,3,3,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,0,0,1,0,0,0,0},
	{0,1,1,1,1,1,0,1,1,1,1,1,0},
	{0,1,0,0,4,0,0,1,0,0,0,1,0},
	{0,1,0,1,0,0,4,0,4,0,0,1,0},
	{0,1,0,0,0,1,1,1,0,0,0,1,0},
	{0,1,1,1,0,1,0,1,0,1,1,1,0},
	{0,0,0,1,0,1,0,1,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,2,0,0,1,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0},
};

InGameScene::InGameScene() :playerPos( { 0, 0 } ){

	Reset();

	step = Step_StartJingle;
}

InGameScene::~InGameScene(){

}

void InGameScene::Exec(){
	switch( step )
	{
	case Step_StartJingle:
		StartJingle();
		break;
	case Step_Input:
		Input();
		AddTime();
		break;
	case Step_ClearJingle:
		ClearJingle();
		break;
	default:
		break;
	}
}

void InGameScene::Draw(){

	DrawUI();

	// ステージの中身と、プレイヤーを描画(DXライブラリのDrawBoxを使用)
// 	int DrawBox( int x1 , int y1 , int x2 , int y2 , unsigned int Color , int FillFlag );

// 23日までには完成させておく
	// m_StageDataの配列の中身をみて、それぞれの四角形を描画する
	//	ObjectType_Ground,			// 0 なし
	//	ObjectType_Wall,			// 1 白(255, 255, 255)
	//	ObjectType_Target,			// 3 赤(255,   0,   0)
	//	ObjectType_UnsetCrate,		// 4 紫(255,   0, 255)
	//	ObjectType_SetCrate = 7,	// 7 緑(  0, 255,   0)

	static TextureManager* instance = TextureManager::GetInstance();

	for( int y = 0; y < STAGE_HEIGHT; y++ ){
		for( int x = 0; x < STAGE_WIDTH; x++ ){
			int handleTemp = instance->GetObjectHandle( stageData.at( y ).at( x ) );
			if( stageData.at( y ).at( x ) == ObjectType::Obj_Player ) handleTemp = instance->GetObjectHandle( ObjectType::Obj_Ground );

			DrawGraph( x * CHIP_WIDTH, y * CHIP_HEIGHT, handleTemp, false );
		}
	}

	// プレイヤーの描画
	switch( playerPos.direction ){
	case DirType::Dir_Right:
		DrawTurnGraph( playerPos.x * CHIP_WIDTH, playerPos.y * CHIP_HEIGHT, instance->GetObjectHandle( ObjectType::Obj_Player ), true );
		break;
	default:
		DrawGraph( playerPos.x * CHIP_WIDTH, playerPos.y * CHIP_HEIGHT, instance->GetObjectHandle( ObjectType::Obj_Player ), true );
		break;
	}

	// クリア表示 & Enterキーを押すように誘導(1秒間隔で点滅)
	static int flashingCounter = 0;
	if( IsClear() ){
		flashingCounter++;

		if( flashingCounter < FRAME_RATE )	DrawGraph( Images::UI::clearGuide.drawCenterX, Images::UI::clearGuide.drawCenterY, instance->GetGuideHandle(), true );
		else if( flashingCounter >= FRAME_RATE * 2 )	flashingCounter = 0;
	}
}

bool InGameScene::IsEnd() const{
	return ( step == Step_End );
}

void InGameScene::StartJingle(){
	step = Step_Input;
}

void InGameScene::Input(){

	InputManager* pInputMng = InputManager::GetInstance();
	SoundManager* soundMng = SoundManager::GetInstance();

	if( pInputMng->IsPush( KeyType::Key_Reset ) ){
		PlaySoundMem( soundMng->GetSoundHandle( SoundList::Reset ), DX_PLAYTYPE_BACK );
		Reset();
	}
	else if( pInputMng->IsPush( KeyType::Key_Up ) )		Move( DirType::Dir_Up );
	else if( pInputMng->IsPush( KeyType::Key_Down ) )	Move( DirType::Dir_Down );
	else if( pInputMng->IsPush( KeyType::Key_Left ) )	Move( DirType::Dir_Left );
	else if( pInputMng->IsPush( KeyType::Key_Right ) )	Move( DirType::Dir_Right );
	else if( pInputMng->IsPush( KeyType::Key_Dog ) )	PlaySoundMem( soundMng->GetSoundHandle( SoundList::Dog ), DX_PLAYTYPE_BACK );
	else if( pInputMng->IsPush( KeyType::Key_Cat ) )	PlaySoundMem( soundMng->GetSoundHandle( SoundList::Cat ), DX_PLAYTYPE_BACK );
	else if( pInputMng->IsPush( KeyType::Key_Back ) )	BackOneStep();

	if( IsClear() ){
		PlaySoundMem( soundMng->GetSoundHandle( SoundList::Clear ), DX_PLAYTYPE_BACK );
		step = Step_ClearJingle;
	}
}

void InGameScene::ClearJingle(){
	if( InputManager::GetInstance()->IsPush( KeyType::Key_Enter ) ){
		step = Step_End;
		SceneManager::GetInstance()->SetNextScene( SceneID::ID_Result );
	}
}

bool InGameScene::IsClear() const {
	for( int y = 0; y < STAGE_HEIGHT; y++ ){
		for( int x = 0; x < STAGE_WIDTH; x++ ){
			if( stageData.at( y ).at( x ) == ObjectType::Obj_UnsetCrate ){
				return false;
			}
		}
	}

	return true;
}

void InGameScene::Reset(){
	stageData = sampleStage;

	for( int y = 0; y < STAGE_HEIGHT; y++ ){
		for( int x = 0; x < STAGE_WIDTH; x++ ){
			if( stageData.at( y ).at( x ) == ObjectType::Obj_Player ){
				playerPos = { x, y };
				stageData.at( y ).at( x ) = ObjectType::Obj_Ground;
				break;
			}
		}
	}

	stageLog.resize( 0 );
	playerLog.resize( 0 );

	GameManager::GetInstance()->SetMin( 0 );
	GameManager::GetInstance()->SetSec( 0 );
	GameManager::GetInstance()->SetTurn( 0 );
	frameCounter = 0;
}

void InGameScene::Move( DirType dir ){
	if( dir < DirType::Dir_Up && dir >= DirType::Dir_Max ){
		return;
	}

	Position next = playerPos;
	Position next2 = playerPos;

	switch( dir )
	{
	case Dir_Up:
		next.y -= 1;
		next2.y -= 2;
		break;
	case Dir_Down:
		next.y += 1;
		next2.y += 2;
		break;
	case Dir_Left:
		next.x -= 1;
		next2.x -= 2;
		playerPos.direction = DirType::Dir_Left;
		break;
	case Dir_Right:
		next.x += 1;
		next2.x += 2;
		playerPos.direction = DirType::Dir_Right;
		break;
	}

	static SoundManager* sound = SoundManager::GetInstance();

	// 移動先が画面外ならreturn
	if( next.x < 0 || next.y < 0 || next.x > ( STAGE_WIDTH - 1 ) || next.y > ( STAGE_HEIGHT - 1 ) ){
		PlaySoundMem( sound->GetSoundHandle( SoundList::RunToWall ), DX_PLAYTYPE_BACK );
		return;
	}

	if( stageData.at(next.y).at(next.x) == ObjectType::Obj_Ground || stageData.at( next.y ).at( next.x ) == ObjectType::Obj_Target ){
		PlaySoundMem( sound->GetSoundHandle( SoundList::RunToFloor ), DX_PLAYTYPE_BACK );

		// この時点での配置を保存
		playerLog.push_back( playerPos );
		stageLog.push_back( stageData );

		playerPos = next;
		GameManager::GetInstance()->SetTurn( GameManager::GetInstance()->GetTurn() + 1 );
	}
	// 移動先が箱の場合
	else if( stageData.at( next.y ).at( next.x ) == ObjectType::Obj_UnsetCrate || stageData.at( next.y ).at( next.x ) == ObjectType::Obj_SetCrate ){
		// 画面外チェック
		if( next2.x < 0 || next2.y < 0 || next2.x >( STAGE_WIDTH - 1 ) || next2.y >( STAGE_HEIGHT - 1 ) ){
			PlaySoundMem( sound->GetSoundHandle( SoundList::RunToWall ), DX_PLAYTYPE_BACK );
			return;
		}

		// 移動できるマップチップでない場合はreturn
		if( stageData.at( next2.y ).at( next2.x ) != ObjectType::Obj_Ground && stageData.at( next2.y ).at( next2.x ) != ObjectType::Obj_Target ){
			PlaySoundMem( sound->GetSoundHandle( SoundList::RunToWall ), DX_PLAYTYPE_BACK );
			return;
		}

		// この時点での配置を保存
		playerLog.push_back( playerPos );
		stageLog.push_back( stageData );

		// となりの位置を変更する
		if( stageData.at( next.y ).at( next.x ) == ObjectType::Obj_UnsetCrate ){
			stageData.at( next.y ).at( next.x ) = ObjectType::Obj_Ground;
		}
		else{
			stageData.at( next.y ).at( next.x ) = ObjectType::Obj_Target;
		}

		// 箱を移動させる
		if( stageData.at( next2.y ).at( next2.x ) == ObjectType::Obj_Ground ){
			PlaySoundMem( sound->GetSoundHandle( SoundList::CrateToFloor ), DX_PLAYTYPE_BACK );
			stageData.at( next2.y ).at( next2.x ) = ObjectType::Obj_UnsetCrate;
		}
		else{
			PlaySoundMem( sound->GetSoundHandle( SoundList::CrateToTarget ), DX_PLAYTYPE_BACK );
			stageData.at( next2.y ).at( next2.x ) = ObjectType::Obj_SetCrate;
		}

		// プレイヤーの移動
		playerPos = next;
		GameManager::GetInstance()->SetTurn( GameManager::GetInstance()->GetTurn() + 1 );
	}
	else{
		PlaySoundMem( sound->GetSoundHandle( SoundList::RunToWall ), DX_PLAYTYPE_BACK );
	}
}

void InGameScene::AddTime(){

	static GameManager* instance = GameManager::GetInstance();

	frameCounter++;

	if( frameCounter >= FRAME_RATE ){
		instance->SetSec( instance->GetSec() + 1 );
		frameCounter = 0;

		if( instance->GetSec() >= 60 ){
			instance->SetMin( instance->GetMin() + 1 );
			instance->SetSec( 0 );
		}
	}
}

void InGameScene::DrawUI(){
	DrawBox( 416, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Color::brown, true );

	DrawString( 500, 30, "倉庫番", Color::black );
	DrawFormatString( 430, 80, Color::black, "経過時間 : %02d分 %02d秒", GameManager::GetInstance()->GetMin(), GameManager::GetInstance()->GetSec() );
	DrawFormatString( 430, 110, Color::black, "移動回数 : %d回", GameManager::GetInstance()->GetTurn() );

	DrawString( 430, 150, " ↑ : 上移動", Color::black );
	DrawString( 430, 170, " ↓ : 下移動", Color::black );
	DrawString( 430, 190, " → : 右移動", Color::black );
	DrawString( 430, 210, " ← : 左移動", Color::black );
	DrawString( 430, 230, "  B : 一手戻す", Color::black );
	DrawString( 430, 250, "  R : リセット", Color::black );
	DrawString( 430, 270, "esc : 終了", Color::black );
	DrawString( 430, 310, "  D : わん", Color::black );
	DrawString( 430, 330, "  C : にゃー", Color::black );
}

void InGameScene::BackOneStep(){

	if( GameManager::GetInstance()->GetTurn() == 0 ) return;

	stageData = stageLog.back();
	stageLog.pop_back();

	playerPos = playerLog.back();
	playerLog.pop_back();

	PlaySoundMem( SoundManager::GetInstance()->GetSoundHandle( SoundList::Back ), DX_PLAYTYPE_BACK );

	GameManager::GetInstance()->SetTurn( GameManager::GetInstance()->GetTurn() - 1 );
}
