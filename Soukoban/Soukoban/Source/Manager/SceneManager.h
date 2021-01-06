
#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "../Definition.h"
#include "../Singleton.h"

class SceneManager : public Singleton<SceneManager>{
public:
	SceneManager();
	~SceneManager();

	void Exec();	// シーンの実行
	void Draw();	// シーンの描画

	// 次のシーンを設定
	void SetNextScene( SceneID next );

private:
	// 次のシーンを作成
	class SceneBase* CreateNextScene();

private:
	class SceneBase* pScene;		// 実行中のシーン
	static SceneID nextSceneID;		// 次に作るシーンのID
};

#if 0
//------------
// シングルトンデザイン
private:
	// 自分自身のポインタ変数(自分自身の唯一の実態)
	static SceneManager* pInstance;

public:
	// 実態を作る関数
	static void CreateInstance(){
		// 既に作られているなら新しく作らないことを保証する
		if( pInstance == nullptr )pInstance = new SceneManager();
	}

	static void DestroyInstance(){
		delete pInstance;
		pInstance = nullptr;
	}

	static SceneManager* GetInstance(){
		return pInstance;
	}

	static bool IsNull(){
		return ( pInstance == nullptr );
	}
};

// 初期化
SceneManager* Singleton<SceneManager>::pInstance = nullptr;
#endif

#endif // !scene_manager_h
