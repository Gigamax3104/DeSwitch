#pragma once
#include	"GameObject.h"
#include	"BoxCollider.h"

class Box : public GameObject,public BoxCollider {
public:
	Box() : GameObject(),m_size(0.0,0.0),m_color(){}
	Box(Vector2Int pos, Vector2 size, Vector2 scale, int color, double angle = 0.0, bool transFlag = false, std::string imageFile = "", std::string movieFile = "");
	Box(GameObject obj, Vector2 size, int color, bool transFlag = false, std::string imageFile = "", std::string movieFile = "");
	Box(GameObject obj, Vector2 size, Color color, std::string imageFile = "", std::string movieFile = "");

	Box(const Box& other) : GameObject(other),m_size(other.m_size),m_color(other.m_color){}

	void operator=(const Box& other);

	virtual ~Box(){}

	void Display() override;

	Vector2& GetSize() { return m_size; }
	Color& GetColor() { return m_color; }

	bool CheckHit(int posX, int posY, double sizeX, double sizeY) override;
	bool CheckHit(Vector2Int pos, Vector2 size) override;
	bool CheckHit(const Box& other) /*override*/;

protected:
	Vector2 m_size;
	Color m_color;
};