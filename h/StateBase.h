#pragma once

class StateBase {
public:
	virtual void Enter() {}
	virtual StateBase* Loop() { return this; }
	virtual void Exit() {}
};