#pragma once
#include	"StateBase.h"
#include	"Button.h"
#include	"Player.h"
#include	"Event.h"
#include	"Text.h"

class GameState : public StateBase{
public:
	GameState() : m_event({ "../Video/爆発素材meme.mp4",
		"C:/Users/gigam/Videos/画面録画/2代目閻魔_Short.mp4" }, 
		{ "C:/Users/gigam/Downloads/indie-cross-build/assets/songs/imminent-demise/Inst.ogg",
		"C:/Users/gigam/Downloads/indie-cross-build/assets/songs/imminent-demise/Voices.ogg" }) { Enter(); }
	virtual ~GameState() { Exit(); }

	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;

	void ChangeNumberStage(int stage) { m_stage = stage; } //ステージ数変更
	void ResetStage() { m_now_stage = 0; } //現在ステージからリセット


private:
	int test[2];

	int m_stage = 3; //全ステージ数(固定)
	int m_now_stage = 0; //現在ステージ

	int* m_now_stage_button; //ステージに応じたボタンの個数
	int m_button_create = 6; //仮で作成したボタンの数

	double m_time = 0;

	Box m_desk; //机
	Button** m_button; //1個目→ステージ、2個目→個数
	
	MainPlayer m_player; //プレイヤー
	Human m_player_friend; //相手

	Event m_event; //イベント

	std::vector<Text> m_text;

	Image m_image;
};