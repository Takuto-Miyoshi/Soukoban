
#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include "../Definition.h"
#include "../Singleton.h"

enum class SoundList{
	Enter,
	Reset,
	Clear,
	RunToFloor,
	RunToWall,
	CrateToFloor,
	CrateToTarget,
	Dog,
	Cat
};

class SoundManager : public Singleton<SoundManager>{
public:
	SoundManager();
	~SoundManager();

	void LoadSoundHandle( SceneID scene );

	int GetBGMHandle() const { return BGM; }
	int GetSoundHandle( SoundList sound ) const;

private:
	int BGM;

	int enter;
	int reset;
	int clear;
	int runToFloor;
	int runToWall;
	int crateToFloor;
	int crateToTarget;
	int dog;
	int cat;
};

#endif // !SOUND_MANAGER_H
