#pragma once
#include	"GameObject.h"

class Circle : GameObject{
public:
	Circle() : GameObject(),m_radius(0.0),m_color(){}
	Circle(Vector2Int pos, Vector2 scale, double radius, int color, double angle = 0.0, bool transFlag = false);
	Circle(GameObject obj, double radius, int color, bool transFlag = false);
	Circle(GameObject obj, double radius, Color color);

	void operator=(const Circle& other);

	virtual ~Circle(){}

	void Display() override;

	bool CheckHit(int x, int y, double radius) const;
	bool CheckHit(Vector2Int pos, double radius) const;
	bool CheckHit(const Circle& other) const;

private:
	double m_radius;

	Color m_color;
};