#pragma once
#include	<cmath>

#include	"GraphicData.h"
#include	"Position.h"

class GameObject {
public:
	Vector2Int m_pos;
	Vector2 m_scale;

	double m_angle;

	GameObject() : m_pos(0,0),m_scale(0.0,0.0),m_angle(0.0),m_image_size(1),m_movie_size(1),m_image(new Image[1]),m_movie(new Movie[1]) {}
	GameObject(int posX, int posY, double sizeX, double sizeY, double angle, std::vector<std::string> imageFile = {""}, std::vector<std::string> movieFile = {""});
	GameObject(Vector2Int pos, Vector2 size, double angle, std::vector<std::string> imageFile = {""}, std::vector<std::string> movieFile = {""});
	GameObject(const GameObject& other);

	virtual ~GameObject();

	void operator=(const GameObject& other);

	Image& GetImage(int index) { return m_image[index]; }
	Movie& GetMovie(int index) { return m_movie[index]; }

	void Move(Vector2Int move) { m_move.Forward(m_pos, move); }
	void Change(Vector2Int change) { m_change.Change(m_pos, change); }

	void ScaleChange(Vector2 size) { m_scale = size; }
	void ScaleChange(double size) { m_scale = size; }
	void ScaleChange_Rate(double rate) { m_scale *= rate; }

	virtual void Display();

protected:
	Image* m_image = nullptr;
	Movie* m_movie = nullptr;

	size_t m_image_size = 0;
	size_t m_movie_size = 0;

	IMovable m_move;
	IChangable m_change;
};