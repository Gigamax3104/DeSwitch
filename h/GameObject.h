#pragma once
#include	<cmath>

#include	"GraphicData.h"
#include	"Position.h"

#define IMAGE 0
#define MOVIE 1

class GameObject {
public:
	Vector2Int m_pos;
	Vector2 m_scale;

	double m_angle;

	GameObject() : m_pos(0,0),m_scale(0.0,0.0),m_angle(0.0),m_image_size(1),m_movie_size(1),m_image(new Image[1]),m_movie(new Movie[1]) {}
	GameObject(int posX, int posY, double sizeX, double sizeY, double angle, std::vector<std::string> imageFile = {""}, std::vector<std::string> movieFile = {""});
	GameObject(Vector2Int pos, Vector2 scale, double angle, std::vector<std::string> imageFile = {""}, std::vector<std::string> movieFile = {""});
	GameObject(const GameObject& other);

	virtual ~GameObject();

	void operator=(const GameObject& other);

	void SetGraphFlag(bool flag) { m_graphFlag = flag; }

	void SetImageIndex(int index) { if (index < m_image_size) m_image_index = index; }
	int GetImageIndex() const { return m_image_index; }
	bool CheckImageIndex() const { return m_image_index < m_image_size; }

	size_t GetImageSize() const { return m_image_size; }
	Image& GetImage() { return m_image[m_image_index]; }
	Image& GetImage(int index) { return m_image[index]; }

	Vector2Int GetImageGraphSize() const { return m_image[m_image_index].Get_ImageGraphSize(); }

	void SetMovieIndex(int index) { if (index < m_movie_size) m_movie_index = index; }
	int GetMovieIndex() const { return m_movie_index; }
	bool CheckMovieIndex() const { return m_movie_index < m_movie_size; }

	size_t GetMovieSize() const { return m_movie_size; }
	Movie& GetMovie() { return m_movie[m_movie_index]; }
	Movie& GetMovie(int index) { return m_movie[index]; }

	Vector2Int GetMovieGraphSize() const { return m_movie[m_movie_index].Get_MovieGraphSize(); }

	void Move(Vector2Int move) { m_move.Forward(m_pos, move); }
	void Change(Vector2Int change) { m_change.Change(m_pos, change); }

	void ScaleChange(Vector2 size) { m_scale = size; }
	void ScaleChange(double size) { m_scale = size; }
	void ScaleChange_Rate(double rate) { m_scale *= rate; }

	const Vector2Int HalfImageSize() const;
	const Vector2Int HalfMovieSize() const;

	virtual void Display();

protected:
	bool m_graphFlag = IMAGE;

	int m_image_index = 0;
	Image* m_image = nullptr;

	int m_movie_index = 0;
	Movie* m_movie = nullptr;

	size_t m_image_size = 0;
	size_t m_movie_size = 0;

	IMovable m_move;
	IChangable m_change;
};