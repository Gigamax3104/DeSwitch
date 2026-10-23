#include	"../h/Player.h"

bool MainPlayer::Action(int button, std::string situation, const Box& target) {
	if (situation == "WAS_PRESSED")  return m_mouse.WasPressed(button) && m_mouse.GetBox()->CheckHit(target);
	else if (situation == "IS_PRESSING") return m_mouse.IsPressing(button) && m_mouse.GetBox()->CheckHit(target);
	else if (situation == "WAS_RELEASED") return m_mouse.WasReleased(button) && m_mouse.GetBox()->CheckHit(target);

	return NULL;
}