#pragma once
#include	<string>

#include	"DxLib.h"
#include	"Vector2Int.h"

class ErrorMassage {
public:
	Vector2Int m_pos = Vector2Int(0, 0);

	ErrorMassage() : m_message("\0"){}
	ErrorMassage(std::string massage) : m_message(massage){}

	std::string GetMassage() const { return m_message; }
	void Show() {
		SetFontSize(30);
		DrawString(m_pos.x, m_pos.y, (const TCHAR*)m_message.c_str(), 0xff0000);
		/*m_pos.y += 20; */
	}

private:
	std::string m_message;
};