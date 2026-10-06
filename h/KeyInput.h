#pragma once
#include	"DxLib.h"
#include	"InputSystem.h"

#define ESCAPE 1
#define KEY_1 2
#define KEY_2 3
#define KEY_3 4
#define KEY_4 5
#define KEY_5 6
#define KEY_6 7
#define KEY_7 8
#define KEY_8 9
#define KEY_9 10
#define KEY_0 11
#define MINUS 12
#define BACK 14
#define TAB 15
#define KEY_Q 16
#define KEY_W 17
#define KEY_E 18
#define KEY_R 19
#define KEY_T 20
#define KEY_Y 21
#define KEY_U 22
#define KEY_I 23
#define KEY_O 24
#define KEY_P 25
#define L_BRACKET 26
#define R_BRACKET 27
#define RETURN 28
#define L_CONTROL 29
#define KEY_A 30
#define KEY_S 31
#define KEY_D 32
#define KEY_F 33
#define KEY_G 34
#define KEY_H 35
#define KEY_J 36
#define KEY_K 37
#define KEY_L 38
#define SEMICOLON 39
#define L_SHIFT 42
#define BACKSLASH 43
#define KEY_Z 44
#define KEY_X 45
#define KEY_C 46
#define KEY_V 47
#define KEY_B 48
#define KEY_N 49
#define KEY_M 50
#define COMMA 51
#define PERIOD 52
#define SLASH 53
#define R_SHIFT 54
#define MULTIPLY 55
#define L_ALT 56
#define SPACE 57
#define CAPSLOCK 58
#define F1 59
#define F2 60
#define F3 61
#define F4 62
#define F5 63
#define F6 64
#define F7 65
#define F8 66
#define F9 67
#define F10 68
#define SCROLL 70
#define NUMPAD_7 71
#define NUMPAD_8 72
#define NUMPAD_9 73
#define SUBTRACT 74
#define NUMPAD_4 75
#define NUMPAD_5 76
#define NUMPAD_6 77
#define KEY_ADD 78
#define NUMPAD_1 79
#define NUMPAD_2 80
#define NUMPAD_3 81
#define NUMPAD_0 82
#define DECIMALL 83
#define F11 87
#define F12 88
#define YEN 125
#define KEY_DIVIDE 133
#define KEY_PREVTRUCK 144
#define KEY_AT 145
#define COLON 146
#define NUMPAD_RETURN 156
#define R_CONTROL 157
#define R_ALT 184
#define ARROW_DOWN 192
#define KEY_PAUSE 195
#define KEY_HOME 199
#define ARROW_UP 200
#define KEY_PGUP 201
#define ARROW_LEFT 203
#define ARROW_RIGHT 205
#define KEY_END 207
#define KEY_PGDN 209
#define KEY_INSERT 210
#define KEY_DELETE 211

class KeyInput : public InputSystem {
public:
	KeyInput();
	virtual ~KeyInput();

	void Check(int button) override;
	void AllCheck() override;

	bool WasPressed(int button) override { return m_input[button] == 1; }
	bool IsPressing(int button) override { return m_input[button] >= 1; }
	bool WasReleased(int button) override { return m_relese_flag[button]; }
};