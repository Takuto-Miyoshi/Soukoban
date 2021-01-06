
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "SceneBase.h"

class TitleScene : public SceneBase{
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Exec();
	virtual void Draw();

	virtual bool IsEnd() const;

private:
	void LogoIn();

	void Input();

	void LoadMem();

private:
	struct GraphHandle
	{
		static int backGround;
		static int guide;
	};

};

#endif TITLE_SCENE_H
