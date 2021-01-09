
#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <vector>
#include <string>

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

	void SelectStage();

private:
	int currentSelect;
};

#endif TITLE_SCENE_H
