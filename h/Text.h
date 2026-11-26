#pragma once
#include	"../h/Vector2Int.h"
#include	"../h/Color.h"
#include	"DxLib.h"

#include	<string>
#include	<vector>

class Text {
public:
	Text() : m_text(""), m_pos(0, 0), m_color(BLACK) {}
	Text(const char* text, Vector2Int pos, int color);
	Text(const char* text, Vector2Int pos, int color, int size);

	void SetText_All(const char* text, Vector2Int pos, int color) { SetPos(pos); SetColor(color); SetText(text); }
	void SetText_All(const char* text, Vector2Int pos, int color, int size) { SetPos(pos); SetColor(color); SetText(text); SetFontSize(size); }

	void SetPos(Vector2Int pos) { m_pos = pos; }
	void SetColor(int color) { m_color.color = color; }
	void SetText(const char* text);
	void AddText(const char* text) { m_text += text; }

	void NormalDrawText() { DrawFormatString(m_pos.x, m_pos.y, m_color.color, "%s", m_text.c_str()); }
	void NormalDrawText(int size) { SetFontSize(size); DrawFormatString(m_pos.x, m_pos.y, m_color.color, "%s", m_text.c_str()); }
	void OrderDrawText();
	void OrderDrawText(int size);

	bool ShowEnd() const { return m_show_index >= m_text.size(); }
	void ResetShow() { if (m_show != "\0") m_show.clear(); m_show_index = 0; }

private:
	Vector2Int m_pos;
	Color m_color;
	std::string m_text;

	int m_font_length = 0;
	int m_show_index = 0;
	std::string m_show = "";
};