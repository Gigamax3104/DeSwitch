#include	"DxLib.h"
#include	"../h/Title.h"
#include	"../h/Game.h"

void TitleBase::Enter() {
	//
}

StateBase* TitleBase::Loop() {
	DrawString(0, 0, "Title", 0xffffff);

	if (m_player.GetKeyInput().WasPressed(KEY_INPUT_RETURN)) return new GameState;
	return this;
}

void TitleBase::Exit() {

}