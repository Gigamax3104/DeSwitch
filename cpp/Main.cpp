#include	"../h/Game.h"
#include	"../h/Variable.h"
#include	"../h/ErrorMessage.h"

const char* imageFile[] = {
	"Image/Switch1.png","Image/Switch2.png"
};

const char* soundFile[] = {
	"Sound/ÉçÉäê_.mp3"
};

const char* videoFile[] = {
	"Video/ÉtÉäÅ[îöî≠ëfçﬁmeme.mp4"
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	SetWindowText("DeSwitch");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE);
	if (DxLib_Init() == -1) return -1;
	SetBackgroundColor(0, 0, 0);
	SetDrawScreen(DX_SCREEN_BACK);
	
	try {
		GameState game;
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
	//int save_massage_posY = 0;

	//MAIN:
	//try {
	//	while (1) {
	//		ClearDrawScreen();

	//		ScreenFlip();
	//		WaitTimer(FR);
	//		if (ProcessMessage() == -1) break;
	//		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;
	//	}
	//}
	//catch (ErrorMassage& massage) {
	//	massage.m_pos.y = save_massage_posY;

	//	massage.Show();

	//	save_massage_posY = massage.m_pos.y;

	//	goto MAIN;
	//}

	DxLib_End();
	return 0;
}