
#include "SceneManager.h"

#include "../Script/SceneBase.h"
#include "../Script/TitleScene.h"
#include "../Script/InGameScene.h"
#include "../Script/ResultScene.h"
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
		InitGraph();
		InitSoundMem();
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
	case SceneID::ID_Title:	next = new TitleScene();	break;
	case SceneID::ID_InGame:	next = new InGameScene();	break;
	case SceneID::ID_Result:	next = new ResultScene();	break;
	default:		break;
	}

	return next;
}
