
#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "../Definition.h"
#include "../Singleton.h"

class TextureManager : public Singleton<TextureManager>{
public:
	TextureManager();
	~TextureManager();

	void LoadGraphHandle( SceneID scene);

	int GetBackGroundHandle() const { return backGround; }
	int GetGuideHandle() const { return guide; }
	int GetObjectHandle( int objectType ) const;

private:
	int backGround;

	int guide;

	int wall;
	int floor;
	int target;
	int crate;
	int setCrate;
	int player;
};

#endif // !texture_manager_h
