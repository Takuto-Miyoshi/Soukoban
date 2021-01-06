
#include "DxLib.h"
#include "Manager/SceneManager.h"
#include "Manager/InputManager.h"
#include "Manager/GameManager.h"

int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ){

	SetOutApplicationLogValidFlag( false );				// ログ出力
	ChangeWindowMode( true );							// ウィンドウモード
	SetGraphMode( WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT, FRAME_RATE );	// 画面モード変更
	SetBackgroundColor( 125, 125, 125 );				// 背景色変更
	SetMainWindowText( "My倉庫番" );					// メニューバーのタイトル変更

	if( DxLib_Init() == -1 )return -1;	// 初期化

	SetDrawScreen( DX_SCREEN_BACK );

	// 管理クラスの作成
	GameManager::CreateInstance();
	InputManager::CreateInstance();
	SceneManager::CreateInstance();

	// メインループ
	while( true )
	{
		ClearDrawScreen();
		clsDx();

		// 処理
		InputManager::GetInstance()->Update();
		SceneManager::GetInstance()->Exec();

		// 描画
		SceneManager::GetInstance()->Draw();

		// -1 が返ってきたらループを抜ける
		if( ProcessMessage() < 0 ) break;
		// もしＥＳＣキーが押されていたらループから抜ける
		if( CheckHitKey( KEY_INPUT_ESCAPE ) ) break;

		ScreenFlip();
	}

	SceneManager::DestroyInstance();
	InputManager::DestroyInstance();
	GameManager::DestroyInstance();

	DxLib_End();
	return 0;
}
