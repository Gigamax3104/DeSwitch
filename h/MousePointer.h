#pragma once
#include	"Box.h"
#include	"InputSystem.h"

#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2
#define	MOUSE_MIDDLE 4

class MousePointer : public Box, public InputSystem{
public:
	MousePointer();
	virtual~MousePointer();

	void ChangePointer() { GetMousePoint(&m_pos.x, &m_pos.y); }

	void Check(int button) override;
	void AllCheck() override;

	bool WasPressed(int button) override { return m_input[button / 2] == 1; }
	bool IsPressing(int button) override { return m_input[button / 2] >= 1; }
	bool WasReleased(int button) override { return m_relese_flag[button / 2]; }
};