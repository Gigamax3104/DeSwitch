#include	"../h/KeyInput.h"

KeyInput::KeyInput() {
	m_input_size = 211;

	m_buttons = new int[m_input_size];
	m_input = new int[m_input_size];
	m_relese_flag = new bool[m_input_size];

	for (int i = 0; i < m_input_size; i++) {
		m_buttons[i] = i + 1;
		m_input[i] = 0;
		m_relese_flag[i] = 0;
	}
}

KeyInput::~KeyInput() {
	if (m_input != nullptr) { delete[] m_input; m_input = nullptr; }
	if (m_relese_flag != nullptr) { delete[] m_relese_flag; m_relese_flag = nullptr; }
}

void KeyInput::Check(int button) {
	if (CheckHitKey(button) == 0) {
		m_input[button] = 0;
		m_relese_flag[button] = true;
	}
	
	m_input[button] += CheckHitKey(button);
	if (m_input[button] >= 1) m_relese_flag[button] = false;
}

void KeyInput::AllCheck() {
	for (int i = 0; i < m_input_size; i++) {
		if (CheckHitKey(m_buttons[i]) == 0) {
			m_input[i] = 0;
			m_relese_flag[i] = true;
		}

		m_input[i] += CheckHitKey(m_buttons[i]);
		if (m_input[i] >= 1) m_relese_flag[i] = false;
	}
}