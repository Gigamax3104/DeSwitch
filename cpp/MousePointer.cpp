#include	"DxLib.h"

#include	"../h/MousePointer.h"

MousePointer::MousePointer() {
	m_input_size = 3;
	
	m_buttons = new int[m_input_size] { MOUSE_LEFT, MOUSE_RIGHT, MOUSE_MIDDLE };
	m_input = new int[m_input_size] {0, 0, 0};
	m_relese_flag = new bool[m_input_size] {false, false, false};
}

MousePointer::~MousePointer() {
	if (m_input != nullptr) { delete[] m_input; m_input = nullptr; }
	if (m_relese_flag != nullptr) { delete[] m_relese_flag; m_relese_flag = nullptr; }
}

void MousePointer::Check(int button) {
	if ((GetMouseInput() & button) == 0) {
		m_input[button / 2] = 0;
		m_relese_flag[button / 2] = true;
	}
	
	m_input[button / 2] += (GetMouseInput() & button);
	if (m_input[button / 2] >= 1) m_relese_flag[button / 2] = false;
}

void MousePointer::AllCheck() {
	for (int i = 0; i < m_input_size; i++) {
		if ((GetMouseInput() & m_buttons[i]) == 0) {
			m_input[i] = 0;
			m_relese_flag[i] = true;
		}

		m_input[i] += (GetMouseInput() & m_buttons[i]);
		if (m_input[i] >= 1) m_relese_flag[i] = false;
	}
}