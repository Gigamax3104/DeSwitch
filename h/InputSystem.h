#pragma once

class InputSystem {
protected:
	int m_input_size = 0;

	int* m_buttons = nullptr;

	int* m_input = nullptr;
	bool* m_relese_flag = nullptr;

	virtual void Check(int button) = 0;
	virtual void AllCheck() = 0;

	virtual bool WasPressed(int button) = 0;
	virtual bool IsPressing(int button) = 0;
	virtual bool WasReleased(int button) = 0;
};