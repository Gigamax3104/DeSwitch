#include	"../h/Event.h"
#include	"../h/Variable.h"

Event::Event() : m_movie(new Movie[2]), m_sound(new Sound[2]), m_movie_size(2), m_sound_size(2){
	m_movie->SetMovie("../Video/爆発素材meme.mp4");
	m_movie->SetVolume(90);

	m_sound[0].SetSound("C:/Users/gigam/Downloads/indie-cross-build/assets/songs/imminent-demise/Inst.ogg");
	m_sound[1].SetSound("C:/Users/gigam/Downloads/indie-cross-build/assets/songs/imminent-demise/Voices.ogg");
}

Event::~Event() { if (m_movie != nullptr) { delete[] m_movie; m_movie = nullptr; } }

bool Event::MovieIsPlayFlag(int index)const {
	return TellMovieToGraphToFrame(m_movie[index].Get_MovieData().GetMovieFile())
		< m_movie[index].Get_MovieData().GetFrame();
}

void Event::SetEvent(int movie_index, std::string movie_file_name, int sound_index, std::string sound_file_name) {
	if (movie_index >= 0 && movie_index < m_movie_size) m_movie[movie_index].SetMovie(movie_file_name);

	if (sound_index >= 0 && sound_index < m_sound_size) m_sound[sound_index].SetSound(sound_file_name);
}

void Event::SetEvent_All(std::vector<std::string> movie_file_names, std::vector<std::string> sound_file_names) {
	m_movie_size = movie_file_names.size();
	m_sound_size = sound_file_names.size();

	if (m_movie != nullptr) delete[] m_movie;
	m_movie = new Movie[m_movie_size];

	if (m_sound != nullptr) delete[] m_sound;
	m_sound = new Sound[m_sound_size];

	for (int i = 0; i < m_movie_size; i++) m_movie[i].SetMovie(movie_file_names[i]);
	for (int i = 0; i < m_sound_size; i++) m_sound[i].SetSound(sound_file_names[i]);
}

void Event::SoundAction(int index, int type) { m_sound[index].Play(type); }

void Event::MovieAction(int index) {
	Vector2Int p1 = m_movie[index].Get_H_MovieGraphSize();

	m_movie[index].ExPlay_Limit(p1, Vector2Int(WIDTH - p1.x, HEIGHT - p1.y));
}

void Event::Action(int movie_index, int sound_index, int type, int first) {
	if (first == MOVIE || first == NONE) {
		Vector2Int p1 = m_movie[movie_index].Get_H_MovieGraphSize();

		m_movie[movie_index].ExPlay_Limit(p1, Vector2Int(WIDTH - p1.x, HEIGHT - p1.y));

		m_sound[sound_index].Play(type);
	}
	else if(first == SOUND){
		m_sound[sound_index].Play(type);

		Vector2Int p1 = m_movie[movie_index].Get_H_MovieGraphSize();

		m_movie[movie_index].ExPlay_Limit(p1, Vector2Int(WIDTH - p1.x, HEIGHT - p1.y));
	}
}

void Event::Action(std::vector<int> movie_indexes, std::vector<int> sound_indexes, std::vector<int> types, std::vector<int> order) {
	int movie = 0, sound = 0;

	for (int i = 0; i < order.size(); i++) {
		if (order[i] == MOVIE) {
			Vector2Int p = m_movie[movie_indexes[movie]].Get_H_MovieGraphSize();
			m_movie[movie_indexes[movie++]].ExPlay_Limit(p, Vector2Int(WIDTH - p.x, HEIGHT - p.y));
		}
		else if (order[i] == SOUND) m_sound[sound_indexes[sound]].Play(types[sound++]);
	}
}