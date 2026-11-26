#include	"../h/Game.h"
#include	"../h/ErrorMessage.h"
#include	"../h/Time.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("DeSwitch");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(255, 255, 255);
	SetDrawScreen(DX_SCREEN_BACK);
	
	MainPlayer player;

	try {
		StateBase* state = new GameState;

		while (1) {
			if (player.GetKeyInput().WasPressed(ESCAPE)) break;

			ClearDrawScreen();

			SetFontSize(20);

			StateBase* next = state->Loop();
			if (state != next) {
				state->Exit();
				delete state;

				state = next;
				state->Enter();
			}

			ScreenFlip();
			WaitTimer(FR);
			if (ProcessMessage() == -1) break;
		}
	}
	catch (ErrorMassage& massage) {
		ClearDrawScreen();

		massage.Show();

		ScreenFlip();
		while (!player.GetKeyInput().WasPressed(ESCAPE));
	}

	DxLib_End();
	return 0;
}