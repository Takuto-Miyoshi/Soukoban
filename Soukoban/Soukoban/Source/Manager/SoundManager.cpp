
#include "SoundManager.h"
#include "../Script/TitleScene.h"
#include "../SoundsDefinition.h"
#include "DxLib.h"

SoundManager::SoundManager() :
	BGM( 0 ),
	enter( 0 ),
	reset( 0 ),
	clear( 0 ),
	runToFloor( 0 ),
	runToWall( 0 ),
	crateToFloor( 0 ),
	crateToTarget( 0 ),
	dog( 0 ),
	cat( 0 )
{

}

SoundManager::~SoundManager(){

}


void SoundManager::LoadSoundHandle( SceneID scene ){

	InitSoundMem();

	switch( scene )
	{
	case ID_Title:
		BGM = LoadSoundMem( Sounds::BGM::title );
		enter = LoadSoundMem( Sounds::SE::enter );
		break;
	case ID_InGame:
		BGM = LoadSoundMem( Sounds::BGM::inGame );
		reset = LoadSoundMem( Sounds::SE::reset );
		clear = LoadSoundMem( Sounds::SE::clear );
		runToFloor = LoadSoundMem( Sounds::SE::runToFloor );
		runToWall = LoadSoundMem( Sounds::SE::runToWall );
		crateToFloor = LoadSoundMem( Sounds::SE::crateToFloor );
		ChangeVolumeSoundMem( 160, crateToFloor );
		crateToTarget = LoadSoundMem( Sounds::SE::crateToTarget );
		dog = LoadSoundMem( Sounds::SE::dog );
		cat = LoadSoundMem( Sounds::SE::cat );
		break;
	case ID_Result:
		BGM = LoadSoundMem( Sounds::BGM::result );
		enter = LoadSoundMem( Sounds::SE::enter );
		break;
	default: break;
	}

	ChangeVolumeSoundMem( 180, BGM );
}

int SoundManager::GetSoundHandle( SoundList sound ) const{

	switch( sound )
	{
	case SoundList::Enter:			return enter;
	case SoundList::Reset:			return reset;
	case SoundList::Clear:			return clear;
	case SoundList::RunToFloor:		return runToFloor;
	case SoundList::RunToWall:		return runToWall;
	case SoundList::CrateToFloor:	return crateToFloor;
	case SoundList::CrateToTarget:	return crateToTarget;
	case SoundList::Dog:			return dog;
	case SoundList::Cat:			return cat;
	default: return 0;
	}
}
