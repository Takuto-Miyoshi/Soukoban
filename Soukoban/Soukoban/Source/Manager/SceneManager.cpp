
#include "SceneManager.h"

#include "../Script/SceneBase.h"
#include "../Script/TitleScene.h"
#include "../Script/InGameScene.h"
#include "../Script/ResultScene.h"
#include "TextureManager.h"
#include "DxLib.h"

SceneID SceneManager::nextSceneID = SceneID::ID_Invalid;

SceneManager::SceneManager() :pScene( nullptr ){
	SetNextScene( SceneID::ID_Title );
	pScene = CreateNextScene();
}

SceneManager::~SceneManager(){
	delete pScene;
	pScene = nullptr;
}

void SceneManager::Exec(){
	if( pScene == nullptr )return;

	pScene->Exec();
	if( pScene->IsEnd() ){
		delete pScene;
		pScene = CreateNextScene();
	}
}

void SceneManager::Draw(){
	if( pScene == nullptr )return;

	pScene->Draw();
}

void SceneManager::SetNextScene( SceneID next ){
	nextSceneID = next;
}

SceneBase* SceneManager::CreateNextScene(){
	SceneBase* next = nullptr;
	switch( nextSceneID )
	{
	case SceneID::ID_Title:
		next = new TitleScene();
		TextureManager::GetInstance()->LoadGraphHandle( SceneID::ID_Title );
		break;
	case SceneID::ID_InGame:
		next = new InGameScene();
		TextureManager::GetInstance()->LoadGraphHandle( SceneID::ID_InGame );
		break;
	case SceneID::ID_Result:
		next = new ResultScene();
		TextureManager::GetInstance()->LoadGraphHandle( SceneID::ID_Result );
		break;
	default:		break;
	}

	return next;
}
