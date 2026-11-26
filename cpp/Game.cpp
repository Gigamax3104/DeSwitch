#include	"../h/Title.h"
#include	"../h/Game.h"
#include	"../h/Variable.h"
#include	"../h/Time.h"

void GameState::Enter() {
	DeSwitch::File::Save("Test.txt", "あ");
	DeSwitch::File::Save_Add("Test.txt", "\n");
	DeSwitch::File::Save_Add("Test.txt", "あ");

	//for(int i = 0; i < 2; i++) DeSwitch::File::Load<int>("Test.txt", &test[i]);

	SetBackgroundColor(255, 255, 255);

	m_time = 0;

	Time::Init();

	m_text.push_back(Text("あなたは今、何をしていますか？", Vector2Int(GetFontSize() * 3, HEIGHT / 2 + GetFontSize() * 4 + 15), RED));

	m_button = new Button* [m_stage];
	m_now_stage_button = new int[m_stage];

	for (int i = 0; i < m_stage; i++) {
		m_now_stage_button[i] = i + 1;

		m_button[i] = new Button[m_now_stage_button[i]]
		{ Box(Vector2Int(1024 / 2, 720 / 2),Vector2(0.6, 0.6),Vector2(),0,{ "../Image/Switch1.png","../Image/Switch2.png" })};
	}

	m_image = m_button[m_now_stage][0].GetImage();
}

StateBase* GameState::Loop() {
	Time::Update();

	m_time += Time::deltatime;

	m_player.Operate();

	for (int i = 0; i < m_now_stage_button[m_now_stage]; i++) {
		if (m_player.Action(MOUSE_LEFT, "WAS_PRESSED", m_button[m_now_stage][i])) {
			m_button[m_now_stage][i].Press();

			m_button[m_now_stage][i].SetImageIndex(m_button[m_now_stage][i].GetFlag());
		}
	}

	m_desk.Display();
	for (int i = 0; i < m_now_stage_button[m_now_stage]; i++)
		 m_button[m_now_stage][i].Display();

	m_player.Display();
	m_player_friend.Display();

	for(int i = 0; i < 2; i++) DrawFormatString(0, i * 20, BLACK, "%d", test[i]);

	DrawBox(GetFontSize(), HEIGHT / 2 + GetFontSize() * 3, WIDTH - GetFontSize(), HEIGHT - 10, 0x000000, TRUE);
	DrawBox(GetFontSize() * 2, HEIGHT / 2 + GetFontSize() * 3 + 15, WIDTH - GetFontSize() * 2, HEIGHT - 25, 0xDDDDDD, TRUE);

	for (int i = 0; i < m_text.size(); i++) {
		m_text[i].OrderDrawText();
		if (!m_text[i].ShowEnd()) break;
	}

	SetFontSize(100);
	DrawFormatString(WIDTH / 2 - GetFontSize() / 2, 100 - GetFontSize() / 2, 0xff0000, "%d", COUNT - int(m_time));

	if (m_time >= COUNT) {
		int bit = 0;

		for (int i = 0; i < m_now_stage_button[m_now_stage]; i++) bit += m_button[m_now_stage][i].GetFlag();

		do {
			ClearDrawScreen();

			m_event.MovieAction(bit);

			if (m_player.GetKeyInput().WasPressed(ENTER)) break;
			else if (m_player.GetKeyInput().WasPressed(ESCAPE)) m_event.MovieStop_And_Play(bit);

			ScreenFlip();
			WaitTimer(FR);
		} while (m_event.MovieIsPlayFlag(bit));

		SetBackgroundColor(0, 0, 0);
		return new TitleBase;
	}

	return this;
}

void GameState::Exit() {
	m_event.AllStop();

	for (int i = 0; i < m_event.GetMovieSize(); i++) m_event.GetMovie(i).Get_MovieData().Destroy();
	for (int i = 0; i < m_event.GetSoundSize(); i++) m_event.GetSound(i).GetSoundFile().Destroy();

	for (int i = 0; i < m_stage; i++) { if (m_button[i] != nullptr) { delete[] m_button[i];  m_button[i] = nullptr; } }
	if (m_button != nullptr) { delete[] m_button; m_button = nullptr; }

	if (m_now_stage_button != nullptr) { delete[] m_now_stage_button; m_now_stage_button = nullptr; }
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
//		if (mouseFlag[STAGE_1][0])return EXPROSSIONFLAG; //押された
//		else return CLEAR; //押されていない
//		break;
//
//	case STAGE_2:
//		if (mouseFlag[STAGE_2][0] && mouseFlag[STAGE_2][1]) return DICEFLAG; //どちらも押されている
//		else if (!mouseFlag[STAGE_2][0] && !mouseFlag[STAGE_2][1]) return BOXINGFLAG; //どちらも押されていない
//		else if (mouseFlag[STAGE_2][0] && !mouseFlag[STAGE_2][1]) return EXPROSSIONFLAG; //1個目→押されている、2個目→押されている
//		else return CLEAR; //1個目→押されていない、2個目→押されている
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