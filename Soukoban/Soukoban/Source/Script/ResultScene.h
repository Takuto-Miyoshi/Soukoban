﻿
#ifndef RESULT_SCENE_H
#define RESULT_SCENE_H

#include "SceneBase.h"

class ResultScene : public SceneBase{
public:
	ResultScene();
	virtual ~ResultScene();

	virtual void Exec();
	virtual void Draw();

	virtual bool IsEnd() const;

private:
	void Input();

	void LoadMem();

private:
	struct GraphHandle{
		static int backGround;
		static int guide;
	};

};

#endif RESULT_SCENE_H
