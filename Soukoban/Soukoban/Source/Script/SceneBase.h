
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

class SceneBase{
public:
	SceneBase();
	virtual ~SceneBase();

	// 処理
	virtual void Exec() = 0;

	// 描画
	virtual void Draw() = 0;

	// シーンが終了したかどうかを返す
	virtual bool IsEnd() const = 0;

protected:
	int step;	// 処理内容を管理する変数
};

#endif // !SCENE_BASE_H
