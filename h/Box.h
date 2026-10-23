#pragma once
#include	"GameObject.h"
#include	"BoxCollider.h"

class Box : public GameObject,public BoxCollider {
public:
	Box() : GameObject(),m_boxSize(0.0,0.0),m_color(){}
	Box(Vector2Int pos, Vector2 boxSize, Vector2 scale, int color, double angle = 0.0, bool transFlag = true, std::vector<std::string> imageFile = {""}, std::vector<std::string> movieFile = {""});
	Box(GameObject obj, Vector2 boxSize, int color, bool transFlag = true);
	Box(GameObject obj, Vector2 boxSize, Color color);

	Box(const Box& other) : GameObject(other),m_boxSize(other.m_boxSize),m_color(other.m_color){}

	void operator=(const Box& other);

	virtual ~Box(){}

	void Display() override;

	Vector2& GetSize() { return m_boxSize; }
	Color& GetColor() { return m_color; }

	bool CheckHit(int posX, int posY, double sizeX, double sizeY) override;
	bool CheckHit(Vector2Int pos, Vector2 size) override;
	bool CheckHit(const Box& other);

protected:
	Vector2 m_boxSize;
	Color m_color;
};