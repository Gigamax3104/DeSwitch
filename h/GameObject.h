#pragma once
#include	<cmath>

#include	"GraphicData.h"
#include	"Position.h"

class GameObject : public IMovable, public IChangable {
public:
	Vector2Int m_pos;
	Vector2 m_scale;

	double m_angle;

	GameObject() : m_pos(0,0),m_scale(0.0,0.0),m_angle(0.0),m_image(""),m_movie("") {}
	GameObject(int posX, int posY, double sizeX, double sizeY, double angle, std::string imageFile = NULL, std::string movieFile = NULL);
	GameObject(Vector2Int pos, Vector2 size, double angle, std::string imageFile = NULL, std::string movieFile = NULL);
	GameObject(const GameObject& other);

	virtual ~GameObject(){}

	void operator=(const GameObject& other);

	Image& GetImage() { return m_image; }
	Movie& GetMovie() { return m_movie; }

	void Forward(Vector2Int pos) override { m_pos += pos; }
	void Forward(Vector2 pos) override { m_pos += Vector2Int((int)pos.x, (int)pos.y); }

	void Back(Vector2Int pos) override { m_pos -= pos; }
	void Back(Vector2 pos) override { m_pos -= Vector2Int((int)pos.x, (int)pos.y); }

	void Change(Vector2Int pos) override { m_pos = pos; }
	void Change(Vector2 pos) override { m_pos = Vector2Int((int)pos.x, (int)pos.y); }

	void ScaleChange(Vector2 size) { m_scale = size; }
	void ScaleChange(double size) { m_scale = size; }
	void ScaleChange_Rate(double rate) { m_scale *= rate; }

	virtual void Display();
protected:
	Image m_image;
	Movie m_movie;
};