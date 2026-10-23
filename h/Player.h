#pragma once
#include	"Box.h"
#include	"Human.h"
#include	"MousePointer.h"
#include	"KeyInput.h"

class MainPlayer : public Human {
public:
	MainPlayer() : Human(){}
	MainPlayer(const MainPlayer& other) : Human(other){}

	virtual ~MainPlayer(){}

	MousePointer& GetMousePointer() { return m_mouse; }
	KeyInput& GetKeyInput() { return m_key; }

	virtual void Operate() { m_mouse.ChangePointer(); m_mouse.GetCircle()->Display(); m_mouse.AllCheck(); m_key.AllCheck(); }
	bool Action(int button, std::string situation, const Box& target);

private:
	MousePointer m_mouse;
	KeyInput m_key;
};