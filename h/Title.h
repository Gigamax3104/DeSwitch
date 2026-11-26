#pragma once
#include	"StateBase.h"
#include	"Player.h"

class TitleBase : public StateBase {
public:
	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;

private:
	MainPlayer m_player;
};