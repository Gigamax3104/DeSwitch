#include	"../h/Event.h"

void Event::SetEvent(std::vector<std::string> files) {
	size_t size = files.size();

	if (m_movie != nullptr) delete[] m_movie;
	m_movie = new Movie[size];

	for (int i = 0; i < size; i++) m_movie[i].SetMovie(files[i]);
}