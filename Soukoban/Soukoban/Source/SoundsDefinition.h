
#ifndef SOUNDS_DEFINITION_H
#define SOUNDS_DEFINITION_H

#include "DxLib.h"

namespace Sounds{
	namespace BGM{
		const LPCTSTR title = "Sounds/TitleBGM.mp3";
		const LPCTSTR inGame = "Sounds/InGameBGM.mp3";
		const LPCTSTR result = "Sounds/ResultBGM.mp3";
	}

	namespace SE{
		const LPCTSTR enter = "Sounds/Enter.mp3";
		const LPCTSTR reset= "Sounds/Reset.mp3";
		const LPCTSTR clear = "Sounds/Clear.mp3";
		const LPCTSTR runToFloor = "Sounds/Run_Floor.mp3";
		const LPCTSTR runToWall = "Sounds/Run_Wall.mp3";
		const LPCTSTR crateToFloor = "Sounds/Crate_Floor.mp3";
		const LPCTSTR crateToTarget = "Sounds/Crate_Target.mp3";
		const LPCTSTR dog = "Sounds/D.mp3";
		const LPCTSTR cat = "Sounds/C.mp3";
	}
}

#endif // !SOUNDS_DEFINITION_H
