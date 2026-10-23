#pragma once
#include	"Vector2.h"
#include	"Color.h"
#include	"File.h"

#include	<fstream>

template<typename T> class Font {
public:
	Font() : m_font(CreateFontToHandle(NULL, 10, 3)){}
	Font(int size, int thick) : m_font(CreateFontToHandle(NULL, size, thick)){}
	Font(int size, int thick, char* font_name = NULL, int type = -1) : m_font(CreateFontToHandle(font_name, size, thick, type)){}
	Font(int size, int thick, const TCHAR* font_name = NULL, int type = -1) : m_font(CreateFontToHandle(font_name, size, thick, type)){}

	virtual ~Font() { DeleteFontToHandle(m_font); }

	void Draw(Vector2Int pos, const char* font, Color c);
	void Draw(Vector2Int pos, std::string font, Color c);

	void FDraw(Vector2Int pos, const char* font, Color c, const T data/* = nullptr*/);
	void FDraw(Vector2Int pos, std::string font, Color c, const T data/* = nullptr*/);

	void ExDraw(Vector2Int pos, Vector2 size, const char* font, Color c, const T data/* = nullptr*/);
	void ExDraw(Vector2Int pos, Vector2 size, std::string font, Color c, const T data/* = nullptr*/);

	void MFDraw(Vector2Int pos, const char* font, Color c) { DrawStringToHandle(pos.x, pos.y, font, c.color, m_font); }
	void MFDraw(Vector2Int pos, std::string font, Color c) { DrawStringToHandle(pos.x, pos.y, (const TCHAR*)&font, c.color, m_font); }

private:
	int m_font;
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

	void SetImage(const std::string& file_name) { m_image.Destroy(); m_image.LoadFile(file_name); }

	bool CheckImageData() const { return m_image.CheckSetImageFile(); }
	DeSwitch::ImageFile& Get_ImageData() { return m_image; }
	const DeSwitch::ImageFile& Get_ImageData() const { return m_image; }

	Vector2Int Get_ImageGraphSize();
	Vector2Int Get_H_ImageGraphSize() { return Get_ImageGraphSize() / 2; }

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

	void Play(const Vector2& pos);
	void Play(const Vector2Int& pos);

	void ExPlay(const Vector2& pos, const Vector2& scale);
	void ExPlay(const Vector2Int& pos, const Vector2& scale);

	void SetMovie(const std::string& file_name) { m_movie.LoadFile(file_name); }

	bool CheckMovieData() const { return m_movie.CheckSetMovieFile(); }
	DeSwitch::MovieFile& Get_MovieData() { return m_movie; }
	const DeSwitch::MovieFile& Get_MovieData() const { return m_movie; }

	Vector2Int Get_MovieGraphSize();
	Vector2Int Get_H_MovieGraphSize() { return Get_MovieGraphSize() / 2; }

private:
	Vector2Int m_movie_graphSize;

	DeSwitch::MovieFile m_movie;
};