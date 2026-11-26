#pragma once
#include	"Vector2.h"
#include	"Color.h"
#include	"File.h"

#include	<fstream>

class Font {
public:
	Font(const char* font_name, int size, int thick);
	Font(const char* font_name, int size, int thick, int type);

	virtual ~Font() { if(m_font_code != -1 && m_font_code != NULL) DeleteFontToHandle(m_font_code); }

	static void Draw(Vector2Int pos, const char* font, Color c);
	static void Draw(Vector2Int pos, std::string font, Color c);

	template<typename T> static void FDraw(Vector2Int pos, int color, const char* type, const T& data);
	template<typename T> static void FDraw(Vector2Int pos, int color, std::string type, const T& data);
	template<typename T> static void FDraw(Vector2Int pos, Color c, const char* type, const T& data);
	template<typename T> static void FDraw(Vector2Int pos, Color c, std::string type, const T& data);

	template<typename T> static void ExDraw(Vector2Int pos, Vector2 size, int color, const char* type, const T& data);
	template<typename T> static void ExDraw(Vector2Int pos, Vector2 size, int color, std::string type, const T& data);
	template<typename T> static void ExDraw(Vector2Int pos, Vector2 size, Color c, const char* type, const T& data);
	template<typename T> static void ExDraw(Vector2Int pos, Vector2 size, Color c, std::string type, const T& data);

	void MFDraw(Vector2Int pos, const char* font, Color c) { DrawStringToHandle(pos.x, pos.y, font, c.color, m_font_code); }
	void MFDraw(Vector2Int pos, std::string font, Color c) { DrawStringToHandle(pos.x, pos.y, font.c_str(), c.color, m_font_code); }

	void SetFont(const char* font_name, int size, int thick);
	void SetFont(const char* font_name, int size, int thick, int type);
private:
	int m_font_code = NULL;
};

template<typename T>void Font::FDraw(Vector2Int pos, int color, const char* type, const T& data) {
	DrawFormatString(pos.x, pos.y, color, type, data);
}

template<typename T>void Font::FDraw(Vector2Int pos, int color, std::string type, const T& data) {
	DrawFormatString(pos.x, pos.y, color, type, data);
}

template<typename T>void Font::FDraw(Vector2Int pos, Color c, const char* type, const T& data) {
	DrawFormatString(pos.x, pos.y, c.color, type, data);
}

template<typename T>void Font::FDraw(Vector2Int pos, Color c, std::string type, const T& data) {
	DrawFormatString(pos.x, pos.y, c.color, type, data);
}

template<typename T>void Font::ExDraw(Vector2Int pos, Vector2 size, int color, const char* type, const T& data) {
	DrawExtendFormatString(pos.x, pos.y, size.x, size.y, color, type, data);
}

template<typename T>void Font::ExDraw(Vector2Int pos, Vector2 size, int color, std::string type, const T& data) {
	DrawExtendFormatString(pos.x, pos.y, size.x, size.y, color, type, data);
}

template<typename T>void Font::ExDraw(Vector2Int pos, Vector2 size, Color c, const char* type, const T& data) {
	DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, type, data);
}

template<typename T>void Font::ExDraw(Vector2Int pos, Vector2 size, Color c, std::string type, const T& data) {
	DrawExtendFormatString(pos.x, pos.y, size.x, size.y, c.color, type, data);
}

class Sound {
public:
	Sound(){}
	Sound(const std::string& file_name) : m_sound(file_name){}
	Sound(Sound&& other) noexcept : m_sound(std::move(other.m_sound)){}

	virtual ~Sound(){}

	void operator=(const Sound& other);
	const Sound& operator=(const Sound&& other) noexcept;

	void SetSound(const std::string& file_name) { m_sound.LoadFile(file_name); }
	void SetVolume(double raito);

	DeSwitch::SoundFile& GetSoundFile() { return m_sound; }
	const DeSwitch::SoundFile& GetSoundFile() const { return m_sound; }

	void Play(int type) { if (!CheckSoundMem(m_sound.GetSoundFile())) PlaySoundMem(m_sound.GetSoundFile(), type); m_type = type; }
	void Stop() { if (CheckSoundMem(m_sound.GetSoundFile())) StopSoundMem(m_sound.GetSoundFile()); }

	void Stop_And_Play();
private:
	int m_type = NULL;

	DeSwitch::SoundFile m_sound;
};

class Image {
public:
	Image(){}
	Image(const std::string& file_name) : m_image(file_name) { GetGraphSize(m_image.GetImageFile(), &m_image_graphSize.x, &m_image_graphSize.y); }
	Image(Image&& other) noexcept : m_image(std::move(other.m_image)){ GetGraphSize(m_image.GetImageFile(), &m_image_graphSize.x, &m_image_graphSize.y);}

	virtual ~Image(){}

	void operator=(const Image& other);
	const Image& operator=(const Image&& other) noexcept;

	void Draw(const Vector2& pos);
	void Draw(const Vector2Int& pos);

	void ExDraw(const Vector2& pos, const Vector2 scale);
	void ExDraw(const Vector2Int& pos, const Vector2 scale);

	void SetImage(const std::string& file_name);

	bool CheckImageData() const { return m_image.CheckSetImageFile(); }
	DeSwitch::ImageFile& Get_ImageData() { return m_image; }
	const DeSwitch::ImageFile& Get_ImageData() const { return m_image; }

	Vector2Int Get_ImageGraphSize() const { return m_image_graphSize; }
	Vector2Int Get_H_ImageGraphSize() const { return Get_ImageGraphSize() / 2; }

private:
	Vector2Int m_image_graphSize;

	DeSwitch::ImageFile m_image;
};

class Movie {
public:
	Movie(){}
	Movie(const std::string& file_name) : m_movie(file_name){}
	Movie(Movie&& other) noexcept : m_movie(std::move(other.m_movie)){}

	virtual ~Movie(){}

	void operator=(const Movie& other);
	const Movie& operator=(const Movie&& other) noexcept;

	void SetVolume(double raito); //0%～100%設定

	void Play(const Vector2& pos);
	void Play(const Vector2Int& pos);

	void ExPlay_Scale(const Vector2& pos, const Vector2& scale); //倍率あり・拡縮なし(Vector2)
	void ExPlay_Scale(const Vector2Int& pos, const Vector2& scale); //倍率あり・拡縮なし(Vector2Int)

	void ExPlay_Limit(const Vector2& pos, const Vector2& limit_pos); //倍率なし・拡縮あり(Vector2)
	void ExPlay_Limit(const Vector2Int& pos, const Vector2Int& limit_pos); //倍率なし・拡縮あり(Vector2Int)

	void ExPlay(const Vector2& pos, const Vector2& limit_pos, const Vector2& scale); //倍率あり・拡縮あり(Vector2)
	void ExPlay(const Vector2Int& pos, const Vector2Int& limit_pos, const Vector2& scale); //倍率あり・拡縮あり(Vector2Int)

	void SetMovie(const std::string& file_name) { m_movie.LoadFile(file_name); GetGraphSize(m_movie.GetMovieFile(), &m_movie_graphSize.x, &m_movie_graphSize.y); }

	void Stop() { if(GetMovieStateToGraph(m_movie.GetMovieFile())) PauseMovieToGraph(m_movie.GetMovieFile()); }

	void Stop_And_Play();

	bool CheckMovieData() const { return m_movie.CheckSetMovieFile(); }
	DeSwitch::MovieFile& Get_MovieData() { return m_movie; }
	const DeSwitch::MovieFile& Get_MovieData() const { return m_movie; }

	Vector2Int Get_MovieGraphSize() const { return m_movie_graphSize; }
	Vector2Int Get_H_MovieGraphSize() const { return Get_MovieGraphSize() / 2; }

private:
	Vector2Int m_movie_graphSize;

	DeSwitch::MovieFile m_movie;
};