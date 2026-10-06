#pragma once
#include	"StateBase.h"

class TitleBase : public StateBase {
public:
	void Enter() override;
	StateBase* Loop() override;
	void Exit() override;
};