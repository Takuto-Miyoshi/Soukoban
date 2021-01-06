
#include "TextureManager.h"
#include "../Script/TitleScene.h"
#include "../Script/InGameScene.h"
#include "../ImagesDefinition.h"
#include "DxLib.h"

TextureManager::TextureManager() :
	backGround( 0 ),
	guide( 0 ),
	wall( 0 ),
	floor( 0 ),
	target( 0 ),
	crate( 0 ),
	setCrate( 0 ),
	player( 0 )
{

}

TextureManager::~TextureManager(){

}

void TextureManager::LoadGraphHandle( SceneID scene ){

	InitGraph();

	switch( scene )
	{
	case ID_Title:
		backGround = LoadGraph( Images::BackGround::title.path );
		guide = LoadGraph( Images::UI::titleGuide.path );
		break;
	case ID_InGame:
		guide = LoadGraph( Images::UI::clearGuide.path );
		wall = LoadGraph( Images::Object::wall.path );
		floor = LoadGraph( Images::Object::floor.path );
		target = LoadGraph( Images::Object::target.path );
		crate = LoadGraph( Images::Object::crate.path );
		setCrate = LoadGraph( Images::Object::setCrate.path );
		player = LoadGraph( Images::Object::player.path );
		break;
	case ID_Result:
		backGround = LoadGraph( Images::BackGround::result.path );
		guide = LoadGraph( Images::UI::resultGuide.path );
		break;
	default: break;
	}
}

int TextureManager::GetObjectHandle( int objectType ) const {

	switch( objectType )
	{
	case ObjectType::Obj_Ground:		return floor;
	case ObjectType::Obj_Wall:			return wall;
	case ObjectType::Obj_Player:		return player;
	case ObjectType::Obj_Target:		return target;
	case ObjectType::Obj_UnsetCrate:	return crate;
	case ObjectType::Obj_SetCrate:		return setCrate;
	default: return 0;
	}
}
