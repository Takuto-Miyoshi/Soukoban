
#ifndef IMAGES_DEFINITION_H
#define IMAGES_DEFINITION_H

#include "DxLib.h"

struct ImageData{
	int width;
	int height;
	LPCTSTR path;
	int drawCenterX = WINDOW_WIDTH / 2 - width / 2;
	int drawCenterY = WINDOW_HEIGHT / 2 - height / 2;
};

namespace Images{

	namespace BackGround{
		const ImageData title = { 640, 480, "Images/Title.png" };

		const ImageData result = { 640, 480, "Images/Result.png" };
	}

	namespace UI{
		const ImageData titleGuide = { 466, 40, "Images/TitleGuide.png" };

		const ImageData clear = { 494,64, "Images/Clear.png" };

		const ImageData resultGuide = { 570, 36, "Images/ResultGuide.png" };
	}
}

#endif // !IMAGES_DEFINITION_H
