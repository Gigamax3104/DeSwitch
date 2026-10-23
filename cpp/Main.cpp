#include	"../h/Game.h"
#include	"../h/ErrorMessage.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("DeSwitch");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	
	try {
		GameState game;

		while (1) {
			ClearDrawScreen();

			game.Loop();

			ScreenFlip();
			WaitTimer(FR);
			if (ProcessMessage() == -1) break;
			if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		}
	}
	catch (ErrorMassage& massage) {
		while (1) {
			ClearDrawScreen();

			massage.Show();

			ScreenFlip();
			WaitTimer(FR);
			if (ProcessMessage() == -1) break;
			if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
		}
	}

	DxLib_End();
	return 0;
}