
#include "InGameScene.h"
#include "DxLib.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Manager/GameManager.h"
#include "../ImagesDefinition.h"

enum{
	Step_StartJingle,
	Step_Input,
	Step_ClearJingle,
	Step_End
};

const int SampleStage[STAGE_HEIGHT][STAGE_WIDTH] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,1,1,1,1,1,0,0,0,0,
	0,0,0,0,1,3,3,3,1,0,0,0,0,
	0,0,0,0,1,0,0,0,1,0,0,0,0,
	0,0,0,0,1,0,0,0,1,0,0,0,0,
	0,1,1,1,1,1,0,1,1,1,1,1,0,
	0,1,0,0,4,0,0,1,0,0,0,1,0,
	0,1,0,1,0,0,4,0,4,0,0,1,0,
	0,1,0,0,0,1,1,1,0,0,0,1,0,
	0,1,1,1,0,1,0,1,0,1,1,1,0,
	0,0,0,1,0,1,0,1,0,1,0,0,0,
	0,0,0,1,0,0,0,0,0,1,0,0,0,
	0,0,0,1,0,0,2,0,0,1,0,0,0,
	0,0,0,1,1,1,0,1,1,1,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,
};

int InGameScene::GraphHandle::clear = 0;

InGameScene::InGameScene():playerX( 0 ), playerY( 0 ){

	Reset();

	step = Step_StartJingle;
	LoadMem();
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

	for( int y = 0; y < STAGE_HEIGHT; y++ ){
		for( int x = 0; x < STAGE_WIDTH; x++ ){
			int colorTemp = 0;
			switch( stageData[y][x] ){
			case ObjectType::Obj_Wall:		 colorTemp = GetColor( 255, 255, 255 ); break;
			case ObjectType::Obj_Target:	 colorTemp = GetColor( 255, 0, 0 ); break;
			case ObjectType::Obj_UnsetCrate: colorTemp = GetColor( 255, 0, 255 ); break;
			case ObjectType::Obj_SetCrate:	 colorTemp = GetColor( 0, 255, 0 ); break;
			default: break;
			}
			DrawBox( x * CHIP_WIDTH, y * CHIP_HEIGHT, x * CHIP_WIDTH + CHIP_WIDTH, y * CHIP_HEIGHT + CHIP_HEIGHT, colorTemp, true );
		}
	}

	// プレイヤーの描画
	DrawBox( playerX * CHIP_WIDTH, playerY * CHIP_HEIGHT, playerX * CHIP_WIDTH + CHIP_WIDTH, playerY * CHIP_HEIGHT + CHIP_HEIGHT, GetColor( 255, 255, 0 ), true );

	if( IsClear() ){
		DrawGraph( Images::UI::clear.drawCenterX, Images::UI::clear.drawCenterY, GraphHandle::clear, true );
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

	if( pInputMng->IsPush( KeyType::Key_Reset ) )		Reset();
	else if( pInputMng->IsPush( KeyType::Key_Up ) )		Move( DirType::Dir_Up );
	else if( pInputMng->IsPush( KeyType::Key_Down ) )	Move( DirType::Dir_Down );
	else if( pInputMng->IsPush( KeyType::Key_Left ) )	Move( DirType::Dir_Left );
	else if( pInputMng->IsPush( KeyType::Key_Right ) )	Move( DirType::Dir_Right );

	if( IsClear() ){
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
			if( stageData[y][x] == ObjectType::Obj_UnsetCrate ){
				return false;
			}
		}
	}

	return true;
}

void InGameScene::Reset(){
	for( int y = 0; y < STAGE_HEIGHT; y++ ){
		for( int x = 0; x < STAGE_WIDTH; x++ ){
			stageData[y][x] = SampleStage[y][x];
			if( stageData[y][x] == ObjectType::Obj_Player ){
				playerX = x;
				playerY = y;
				stageData[y][x] = ObjectType::Obj_Ground;
			}
		}
	}

	GameManager::GetInstance()->SetMin( 0 );
	GameManager::GetInstance()->SetSec( 0 );
	GameManager::GetInstance()->SetTurn( 0 );
	frameCounter = 0;
}

void InGameScene::Move( DirType dir ){
	if( dir < DirType::Dir_Up && dir >= DirType::Dir_Max ){
		return;
	}

	int nextX = playerX;
	int nextY = playerY;
	int next2X = playerX;
	int next2Y = playerY;

	switch( dir )
	{
	case Dir_Up:
		nextY -= 1;
		next2Y -= 2;
		break;
	case Dir_Down:
		nextY += 1;
		next2Y += 2;
		break;
	case Dir_Left:
		nextX -= 1;
		next2X -= 2;
		break;
	case Dir_Right:
		nextX += 1;
		next2X += 2;
		break;
	}

	// 移動先が画面外ならreturn
	if( nextX < 0 || nextY < 0 || nextX > ( STAGE_WIDTH - 1 ) || nextY > ( STAGE_HEIGHT - 1 ) ){
		return;
	}

	if( stageData[nextY][nextX] == ObjectType::Obj_Ground || stageData[nextY][nextX] == ObjectType::Obj_Target ){
		playerX = nextX;
		playerY = nextY;
		GameManager::GetInstance()->SetTurn( GameManager::GetInstance()->GetTurn() + 1 );
	}
	// 移動先が箱の場合
	else if( stageData[nextY][nextX] == ObjectType::Obj_UnsetCrate || stageData[nextY][nextX] == ObjectType::Obj_SetCrate ){
		// 画面外チェック
		if( next2X < 0 || next2Y < 0 || next2X > ( STAGE_WIDTH - 1 ) || next2Y > ( STAGE_HEIGHT - 1 ) ){
			return;
		}

		// 移動できるマップチップでない場合はreturn
		if( stageData[next2Y][next2X] != ObjectType::Obj_Ground && stageData[next2Y][next2X] != ObjectType::Obj_Target ){
			return;
		}

		// となりの位置を変更する
		if( stageData[nextY][nextX] == ObjectType::Obj_UnsetCrate ){
			stageData[nextY][nextX] = ObjectType::Obj_Ground;
		}
		else{
			stageData[nextY][nextX] = ObjectType::Obj_Target;
		}

		// 箱を移動させる
		if( stageData[next2Y][next2X] == ObjectType::Obj_Ground ){
			stageData[next2Y][next2X] = ObjectType::Obj_UnsetCrate;
		}
		else{
			stageData[next2Y][next2X] = ObjectType::Obj_SetCrate;
		}

		// プレイヤーの移動
		playerX = nextX;
		playerY = nextY;
		GameManager::GetInstance()->SetTurn( GameManager::GetInstance()->GetTurn() + 1 );
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
	DrawBox( 416, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GetColor( 192, 72, 0 ), true );

	DrawString( 500, 30, "倉庫番", GetColor( 0, 0, 0 ) );
	DrawFormatString( 430, 80, GetColor( 0, 0, 0 ), "経過時間 : %02d分 %02d秒", GameManager::GetInstance()->GetMin(), GameManager::GetInstance()->GetSec() );
	DrawFormatString( 430, 110, GetColor( 0, 0, 0 ), "移動回数 : %d回", GameManager::GetInstance()->GetTurn() );

	DrawString( 430, 150, " ↑ : 上移動", GetColor( 0, 0, 0 ) );
	DrawString( 430, 170, " ↓ : 下移動", GetColor( 0, 0, 0 ) );
	DrawString( 430, 190, " → : 右移動", GetColor( 0, 0, 0 ) );
	DrawString( 430, 210, " ← : 左移動", GetColor( 0, 0, 0 ) );
	DrawString( 430, 230, "  R : リセット", GetColor( 0, 0, 0 ) );
	DrawString( 430, 250, "esc : 終了", GetColor( 0, 0, 0 ) );
}

void InGameScene::LoadMem(){
	GraphHandle::clear = LoadGraph( Images::UI::clear.path );
}
