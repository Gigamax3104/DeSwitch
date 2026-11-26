#include	"../h/Text.h"
#include	"../h/Time.h"
#include	"../h/Variable.h"

Text::Text(const char* text, Vector2Int pos, int color) : m_text(text), m_pos(pos), m_color(color), m_show("\0") {}

Text::Text(const char* text, Vector2Int pos, int color, int size) : m_text(text), m_pos(pos), m_color(color), m_show("\0") {
	SetFontSize(size);
}

void Text::SetText(const char* text) {
	ResetShow();
	m_text = text;
}

void Text::OrderDrawText() {
	if (m_text != "\0") {
		if (Time::frame % 3 == 0) {
			m_text[m_show_index] == '\n' ? m_font_length = 0 : m_font_length++;

			if (m_show_index < m_text.size()) {
				//GetUseCharCodeFormat関数は、文字列のエンコードの種類を調べる。
				//GetCharBytes関数は、第二引数に指定した文字をGetUseCharCodeFormatでバイト数を計算する。
				int byte = GetCharBytes(GetUseCharCodeFormat(), &m_text[m_show_index]);
				m_show_index += byte;

				m_show = m_text.substr(0, m_show_index);
			}
		}

		DrawFormatString(m_pos.x, m_pos.y, m_color.color, "%s", m_show.c_str());
	}
}

void Text::OrderDrawText(int size) {
	SetFontSize(size);

	if (m_text != "\0") {
		if (Time::frame % 3 == 0) {
			m_text[m_show_index] == '\n' ? m_font_length = 0 : m_font_length++;

			if (m_show_index < m_text.size()) {
				//GetUseCharCodeFormat関数は、文字列のエンコードの種類を調べる。
				//GetCharBytes関数は、第二引数に指定した文字をGetUseCharCodeFormatでバイト数を計算する。
				int byte = GetCharBytes(GetUseCharCodeFormat(), &m_text[m_show_index]);
				m_show_index += byte;

				m_show = m_text.substr(0, m_show_index);
			}
		}

		DrawFormatString(m_pos.x, m_pos.y, m_color.color, "%s", m_show.c_str());
	}
}