#pragma once
#include	"GameObject.h"
#include	"GraphicData.h"

class Event {
public:
	Event() : m_movie(new Movie[1]) { m_movie->SetMovie("Video/ƒtƒŠ[”š”­‘fŞmeme.mp4"); }
	Event(std::vector<std::string> file_names) { SetEvent(file_names); }

	virtual ~Event() { if (m_movie != nullptr) { delete[] m_movie; m_movie = nullptr; } }

	void SetEvent(std::vector<std::string> files);
	void Action(int index) { m_movie[index].Play(Vector2(0,0)); }
private:
	Movie* m_movie;
};