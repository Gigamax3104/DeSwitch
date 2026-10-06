#include	"DxLib.h"
#include	"Color.h"
#include	"Variable.h"

void GameOver() {
	SetBackgroundColor(0, 0, 0);
	int time = GetNowCount();

	while (GetNowCount() - time < MS * 3) {
		ClearDrawScreen();

		SetFontSize(150);
		DrawString(WIDTH / 2 - 350, HEIGHT / 2 - 70, "GAME OVER", color[RED]);

		ScreenFlip();
	}

	exit(EXIT_FAILURE);
}