
#ifndef IMAGES_DEFINITION_H
#define IMAGES_DEFINITION_H

#include "DxLib.h"

struct ImageData{
	int width;		// 画像の横幅
	int height;		// 画像の縦幅
	LPCTSTR path;	// 画像のパス
	int drawCenterX = WINDOW_WIDTH / 2 - width / 2;		// X軸中心に描画する用
	int drawCenterY = WINDOW_HEIGHT / 2 - height / 2;	// Y軸中心に描画する用
};

namespace Images{

	namespace BackGround{
		const ImageData title = { 640, 480, "Images/Title.png" };
		const ImageData result = { 640, 480, "Images/Result.png" };
	}

	namespace UI{
		const ImageData titleGuide = { 466, 40, "Images/TitleGuide.png" };
		const ImageData clearGuide = { 492, 113, "Images/Clear.png" };
		const ImageData resultGuide = { 570, 36, "Images/ResultGuide.png" };
	}

	namespace Object {
		const ImageData wall = { 32, 32, "Images/Wall.png" };
		const ImageData floor = { 32, 32, "Images/Floor.png" };
		const ImageData target = { 32, 32, "Images/Target.png" };
		const ImageData crate = { 32, 32, "Images/Crate.png" };
		const ImageData setCrate = { 32, 32, "Images/SetCrate.png" };
		const ImageData player = { 32,32,"Images/Player.png" };
	}
}

#endif // !IMAGES_DEFINITION_H
