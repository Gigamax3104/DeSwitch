#include	"../h/Game.h"

void GameState::Enter() {
	m_button = new Button ** [m_stage];
	m_now_stage_button = new int[m_stage];
	m_files = new std::string[2]{ "Image/Switch1.png","Image/Switch2.png" };

	for (int i = 0; i < m_stage; i++) {
		m_now_stage_button[i] = i + 1;

		m_button[i] = new Button*[m_now_stage_button[i]];

		for (int j = 0; j < m_now_stage_button[i]; j++) {
			m_button[i][j] = new Button[2];

			for (int k = 0; k < 2; k++) {
				if (i != 0) m_button[i][j][k].GetImage().SetImage(m_files[k]);
				else m_button[i][j][k].GetImage().SetImage(m_files[k]);
			}
		}
	}
}

StateBase* GameState::Loop() {
	m_player.Operate();

	for (int i = 0; i < m_now_stage_button[m_now_stage]; i++) {
		for (int j = 0; j < 2; j++) {
			m_player.Action(MOUSE_LEFT, "WAS_PRESSED", m_button[m_now_stage][i][j]);
		}
	}
	
	m_desk.Display();
	for (int i = 0; i < m_now_stage_button[m_now_stage]; i++) {
		for(int j = 0; j < 2; j++) m_button[i][j]->Display();
	}

	m_player.Display();
	m_player_friend.Display();

	return this;
}

void GameState::Exit() {
	for (int i = 0; i < m_stage; i++) { if (m_button[i] != nullptr) { delete m_button[i];  m_button[i] = nullptr; } }
	if (m_button != nullptr) { delete m_button; m_button = nullptr; }

	if (m_files != nullptr) { delete m_files; m_files = nullptr; }
}

//GameState::Game(int stage, int button_create, const int* stage_button_create, std::string* files) : m_stage(stage), m_button_create(button_create),m_files(files) {
//	m_button = new Button * [m_stage];
//
//	for (int i = 0; i < m_stage; i++) {
//		int number = 0;
//
//		m_button[i] = new Button[stage_button_create[i]];
//
//		for (int j = 0; j < stage_button_create[i]; j++) m_button[i][j].GetImage().SetImage(m_files[number]);
//
//		number += stage_button_create[i];
//	}
//}


//#include	"DxLib.h"
//#include	"math.h"
//#include	"Class.h"
//#include	"Color.h"
//#include	"GameOver.h"
//#include	"Variable.h"
//
//static int IVENTFLAGSIZE = 1;
//
//Game::Game() {
//	stage = STAGE_1;
//
//	limit = new int[stage + 1];
//	limit[STAGE_1] = 3;
//	limit[STAGE_2] = 10;
//	limit[STAGE_3] = 15;
//	limit[STAGE_4] = 30;
//
//	mouseFlag = new bool* [stage + 1];
//	mouseFlag[stage] = new bool[IVENTFLAGSIZE];
//
//	iventFlag = new bool[IVENTFLAGSIZE];
//
//	start = GetNowCount();
//
//	mouse = 0;
//	for (int i = 0; i < IVENTFLAGSIZE; i++) mouseFlag[stage][i] = false;
//	for (int i = 0; i < IVENTFLAGSIZE; i++) iventFlag[i] = false;
//}
//
//void Game::Reassignment() {
//	switch (stage) {
//	case STAGE_2:
//		IVENTFLAGSIZE = 3; break;
//	case STAGE_3:
//		IVENTFLAGSIZE = 7; break;
//	case STAGE_4:
//		IVENTFLAGSIZE = 15; break;
//	}
//
//	mouseFlag[stage] = new bool[IVENTFLAGSIZE];
//
//	iventFlag = new bool[IVENTFLAGSIZE];
//
//	start = GetNowCount();
//
//	mouse = 0;
//	for (int i = 0; i < IVENTFLAGSIZE; i++) mouseFlag[stage][i] = false;
//	for (int i = 0; i < IVENTFLAGSIZE; i++) iventFlag[i] = false;
//}
//void Game::Start(const GraphicData& graphic) {
//	GetMousePoint(&mousePos.x, &mousePos.y);
//
//	if (GetNowCount() - start < MS * limit[stage]) {
//		GetMouseInput()& MOUSE_INPUT_LEFT ? mouse++ : mouse = 0;
//
//		for(int i = 0; i < stage + 1; i++)
//		if (pow(mousePos.x - graphic.imagePos[Switch2][i].x, 2)
//			<= pow(graphic.imageSize[Switch2][i].x * graphic.scale[Switch2][i].x / 2, 2)
//			&& pow(mousePos.y - graphic.imagePos[Switch2][i].y, 2)
//			<= pow(graphic.imageSize[Switch2][i].y * graphic.scale[Switch2][i].y / 2, 2) && mouse == 1)
//			if(!mouseFlag) mouseFlag[stage][i] = true;
//
//		SwitchDraw(graphic);
//	}
//	else {
//		FLAG f = Judge();
//		iventFlag[f] = true;
//
//		switch (f) {
//		case EXPROSSIONFLAG: Exprossion(graphic); break;
//		case DICEFLAG: Dice(); break;
//		case BOXINGFLAG: Boxing(); break;
//		case LEMONFLAG: Lemon(); break;
//		case WATERFLAG: Water(); break;
//		case ELECTRICITYFLAG: Electricity(); break;
//		case BOOSEFLAG: Boose(); break;
//		}
//	}
//}
//
//void Game::SwitchDraw(const GraphicData& graphic) {
//	mouseFlag ? DrawExtendGraph(graphic.imagePos[Switch2].x, graphic.imagePos[Switch2].y,
//		(int)(graphic.imagePos[Switch2].x + graphic.imageSize[Switch2].x * graphic.scale[IMAGE][Switch2].x),
//		(int)(graphic.imagePos[Switch2].y + graphic.imageSize[Switch2].y * graphic.scale[Switch2].y),
//		graphic.data[IMAGE][Switch2], TRUE) :
//		DrawExtendGraph(graphic.imagePos[IMAGE][Switch1].x, graphic.imagePos[Switch1].y,
//			(int)(graphic.imagePos[Switch1].x + graphic.imageSize[Switch1].x * graphic.scale[Switch1].x),
//			(int)(graphic.imagePos[Switch1].y + graphic.imageSize[Switch1].y * graphic.scale[Switch1].y),
//			graphic.data[IMAGE][Switch1], TRUE);
//}
//
//FLAG Game::Judge() {
//	switch (stage) {
//	case STAGE_1:
//		if (mouseFlag[STAGE_1][0])return EXPROSSIONFLAG; //‰Ÿ‚³‚ê‚½
//		else return CLEAR; //‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
//		break;
//
//	case STAGE_2:
//		if (mouseFlag[STAGE_2][0] && mouseFlag[STAGE_2][1]) return DICEFLAG; //‚Ç‚¿‚ç‚à‰Ÿ‚³‚ê‚Ä‚¢‚é
//		else if (!mouseFlag[STAGE_2][0] && !mouseFlag[STAGE_2][1]) return BOXINGFLAG; //‚Ç‚¿‚ç‚à‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢
//		else if (mouseFlag[STAGE_2][0] && !mouseFlag[STAGE_2][1]) return EXPROSSIONFLAG; //1ŒÂ–Ú¨‰Ÿ‚³‚ê‚Ä‚¢‚éA2ŒÂ–Ú¨‰Ÿ‚³‚ê‚Ä‚¢‚é
//		else return CLEAR; //1ŒÂ–Ú¨‰Ÿ‚³‚ê‚Ä‚¢‚È‚¢A2ŒÂ–Ú¨‰Ÿ‚³‚ê‚Ä‚¢‚é
//		break;
//
//	case STAGE_3:
//		if (mouseFlag[STAGE_3][0] && mouseFlag[STAGE_3][1] && mouseFlag[STAGE_3][2]) return WATERFLAG;
//		else if (!mouseFlag[STAGE_3][0] && mouseFlag[STAGE_3][1] && mouseFlag[STAGE_3][2]) return DICEFLAG;
//		else if (mouseFlag[STAGE_3][0] && !mouseFlag[STAGE_3][1] && mouseFlag[STAGE_3][2]) return EXPROSSIONFLAG;
//		else if (mouseFlag[STAGE_3][0] && mouseFlag[STAGE_3][1] && !mouseFlag[STAGE_3][2]) return CLEAR;
//		else if (!mouseFlag[STAGE_3][0] && !mouseFlag[STAGE_3][1] && mouseFlag[STAGE_3][2]) return BOXINGFLAG;
//		else if (!mouseFlag[STAGE_3][0] && mouseFlag[STAGE_3][1] && !mouseFlag[STAGE_3][2]) return LEMONFLAG;
//		else if (mouseFlag[STAGE_3][0] && !mouseFlag[STAGE_3][1] && !mouseFlag[STAGE_3][2]) return BOOSEFLAG;
//		else return ELECTRICITYFLAG;
//		break;
//	}
//}
//
//void Game::Exprossion(const GraphicData& graphic) {
//	SeekMovieToGraph(graphic.data[VIDEO][EXPROSSION], 0);
//	PlayMovieToGraph(graphic.data[VIDEO][EXPROSSION]);
//
//	if (iventFlag[EXPROSSIONFLAG]) ExprossionDraw(graphic);
//
//	switch (stage) {
//	case STAGE_1:
//		if (!mouseFlag[stage][0]) GameOver(); break;
//
//	case STAGE_2:
//		if (!mouseFlag[STAGE_2][0] && !mouseFlag[STAGE_2][1]) GameOver(); break;
//
//	case STAGE_3:
//		if (!mouseFlag[STAGE_3][0] && !mouseFlag[STAGE_3][1] && !mouseFlag[STAGE_3][2]) GameOver(); break;
//	}
//}
//
//void Game::ExprossionDraw(const GraphicData& graphic) {
//	DrawExtendGraph(graphic.pos[VIDEO][EXPROSSION].x, graphic.pos[VIDEO][EXPROSSION].y,
//		graphic.size[VIDEO][EXPROSSION].x, graphic.size[VIDEO][EXPROSSION].y, graphic.data[VIDEO][EXPROSSION], FALSE);
//
//	if (GetMovieStateToGraph(graphic.data[VIDEO][EXPROSSION]) == NULL) mouseFlag = false;
//
//}
//
//Game::~Game() {
//	delete[] limit;
//	limit = nullptr;
//
//	delete[] mouseFlag;
//	mouseFlag = nullptr;
//
//	delete[] iventFlag;
//	iventFlag = nullptr;
//}