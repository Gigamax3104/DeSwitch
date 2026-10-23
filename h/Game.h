#pragma once
#include	"StateBase.h"
#include	"Button.h"
#include	"Player.h"
#include	"Event.h"

class GameState : public StateBase{
public:
	GameState() { Enter(); }
	virtual ~GameState() { Exit(); }

	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;

private:
	const int m_stage = 3;
	int m_now_stage = 0;

	int* m_now_stage_button;
	int m_button_create = 6;

	std::vector<std::string> m_files;

	Box m_desk;
	Button** m_button; //1個目→ステージ、2個目→個数
	
	MainPlayer m_player;
	Human m_player_friend;

	Event m_event;
};