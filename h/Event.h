#pragma once
#include	"GameObject.h"
#include	"GraphicData.h"

#define NORMAL DX_PLAYTYPE_NORMAL
#define BACK DX_PLAYTYPE_BACK
#define LOOP DX_PLAYTYPE_LOOP

#define SOUND 0
#define NONE 2

class Event {
public:
	Event();
	Event(std::vector<std::string> movie_file_names, std::vector<std::string> sound_file_names)
	{ SetEvent_All(movie_file_names, sound_file_names); }

	virtual ~Event();

	void SetEvent_Movie(int index, std::string movie_file_name) { if (index < m_movie_size) m_movie[index].SetMovie(movie_file_name); }
	void SetEvent_Sound(int index, std::string sound_file_name) { if (index < m_sound_size) m_sound[index].SetSound(sound_file_name); }
	void SetEvent(int movie_index, std::string movie_file_name, int sound_index, std::string sound_file_name);

	void SetEvent_All(std::vector<std::string> movie_file_names, std::vector<std::string> sound_file_names);

	size_t GetSoundSize() const { return m_sound_size; }
	Sound& GetSound(int index) { if (index < m_sound_size) return m_sound[index]; }

	size_t GetMovieSize() const { return m_movie_size; }
	Movie& GetMovie(int index) { if (index < m_movie_size) return m_movie[index]; }

	void SoundAction(int index, int type);
	void AllSoundStop() { for (int i = 0; i < m_sound_size; i++) m_sound[i].Stop(); }

	void MovieAction(int index);
	void AllMovieStop() { for (int i = 0; i < m_movie_size; i++) m_movie[i].Stop(); }

	void MovieStop_And_Play(int index) { m_movie[index].Stop_And_Play(); }
	int MoviePlayFlag(int index) const { return GetMovieStateToGraph(m_movie[index].Get_MovieData().GetMovieFile()); }
	bool MovieIsPlayFlag(int index) const;

	void Action(int movie_index, int sound_index, int type, int first = NONE); //映像要素数、音楽要素数、音楽再生タイプ、どちらを先にするか(MOVIE or SOUND)
	void Action(std::vector<int> movie_indexes, std::vector<int> sound_indexes, std::vector<int> types, std::vector<int> order);
	void AllStop() { AllSoundStop(); AllMovieStop(); }
private:
	size_t m_sound_size;
	Sound* m_sound;

	size_t m_movie_size;
	Movie* m_movie;
};