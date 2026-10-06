#include	"../h/Circle.h"

Circle::Circle(Vector2Int pos, Vector2 scale, double radius, int color, double angle, bool transFlag)
: GameObject(pos,scale,angle),m_radius(radius),m_color(color,transFlag){}

Circle::Circle(GameObject obj, double radius, int color, bool transFlag)
: GameObject(obj),m_radius(radius),m_color(color,transFlag){}

Circle::Circle(GameObject obj, double radius, Color color) : GameObject(obj),m_radius(radius),m_color(color){}

void Circle::operator=(const Circle& other) {
	if (this != &other) {
		GameObject::operator=(other);
		m_radius = other.m_radius;
		m_color = other.m_color;
	}
}

void Circle::Display() {
	GameObject::Display();

	DrawCircle(m_pos.x, m_pos.y, (int)m_radius * (int)m_scale.x, m_color.color, m_color.transparent);
}

bool Circle::CheckHit(int x, int y, double radius) const{
	return
		pow(m_pos.x - x, 2) + pow(m_pos.y - y, 2) <= pow(m_radius + radius, 2);
}

bool Circle::CheckHit(Vector2Int pos, double radius) const {
	return
		pow(m_pos.x - pos.x, 2) + pow(m_pos.y - pos.y, 2) <= pow(m_radius + radius, 2);
}

bool Circle::CheckHit(const Circle& other) const {
	return
		pow(m_pos.x - other.m_pos.x, 2) + pow(m_pos.y - other.m_pos.y, 2) <= pow(m_radius + other.m_radius, 2);
}